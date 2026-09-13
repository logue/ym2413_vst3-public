#include "Vst2413S.h"
#include "Vst2413SIds.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

namespace Steinberg::Vst {
using namespace Vst2413S;

Vst2413SProcessor::Vst2413SProcessor () {
    setControllerClass (ControllerUID);
    values_[kSL0] = values_[kSL1] = 1.0;
    values_[kMUL0] = values_[kMUL1] = 1.0 / 15.0;
    values_[kWheelRange] = 0.25;
    values_[kFineTune] = 0.5;
    values_[kEG0] = values_[kEG1] = 1.0;
}

tresult PLUGIN_API Vst2413SProcessor::initialize (FUnknown* context) {
    const auto result = AudioEffect::initialize (context);
    if (result != kResultOk) return result;
    addAudioOutput (STR16 ("Mono Out"), SpeakerArr::kMono);
    addEventInput (STR16 ("MIDI In"), 1);
    for (ParamID id = 0; id < kParameterCount; ++id) setParameter (id, values_[id]);
    return kResultOk;
}

tresult PLUGIN_API Vst2413SProcessor::setupProcessing (ProcessSetup& setup) {
    driver_.SetSampleRate (static_cast<unsigned int> (setup.sampleRate));
    return AudioEffect::setupProcessing (setup);
}

tresult PLUGIN_API Vst2413SProcessor::setActive (TBool state) {
    if (!state) driver_.KeyOffAll ();
    return AudioEffect::setActive (state);
}

tresult PLUGIN_API Vst2413SProcessor::canProcessSampleSize (int32 sampleSize) {
    return sampleSize == kSample32 ? kResultOk : kResultFalse;
}

void Vst2413SProcessor::setParameter (ParamID id, ParamValue value) {
    if (id >= kParameterCount) return;
    values_[id] = value;
    driver_.SetParameter (static_cast<SynthDriver::ParameterID> (id), static_cast<float> (value));
}

tresult PLUGIN_API Vst2413SProcessor::process (ProcessData& data) {
    if (data.inputParameterChanges) {
        for (int32 i = 0; i < data.inputParameterChanges->getParameterCount (); ++i) {
            if (auto* queue = data.inputParameterChanges->getParameterData (i)) {
                int32 offset = 0; ParamValue value = 0.;
                if (queue->getPointCount () > 0 &&
                    queue->getPoint (queue->getPointCount () - 1, offset, value) == kResultTrue)
                    setParameter (queue->getParameterId (), value);
            }
        }
    }
    if (data.inputEvents) {
        for (int32 i = 0; i < data.inputEvents->getEventCount (); ++i) {
            Event event {};
            if (data.inputEvents->getEvent (i, event) != kResultOk) continue;
            if (event.type == Event::kNoteOnEvent && event.noteOn.velocity > 0.f)
                driver_.KeyOn (event.noteOn.pitch, event.noteOn.velocity);
            else if (event.type == Event::kNoteOffEvent ||
                     (event.type == Event::kNoteOnEvent && event.noteOn.velocity == 0.f))
                driver_.KeyOff (event.type == Event::kNoteOffEvent ? event.noteOff.pitch : event.noteOn.pitch);
        }
    }
    if (data.numOutputs < 1 || !data.outputs[0].channelBuffers32) return kResultOk;
    auto* output = data.outputs[0].channelBuffers32[0];
    for (int32 i = 0; i < data.numSamples; ++i) output[i] = driver_.Step ();
    data.outputs[0].silenceFlags = 0;
    return kResultOk;
}

tresult PLUGIN_API Vst2413SProcessor::setState (IBStream* state) {
    IBStreamer stream (state, kLittleEndian);
    for (ParamID id = 0; id <= kFineTune; ++id) {
        float value = 0.f;
        if (!stream.readFloat (value)) return kResultFalse;
        setParameter (id, value);
    }
    for (ParamID id = kEG0; id < kParameterCount; ++id) {
        float value = static_cast<float> (values_[id]);
        if (!stream.readFloat (value)) break;
        setParameter (id, value);
    }
    return kResultOk;
}

tresult PLUGIN_API Vst2413SProcessor::getState (IBStream* state) {
    IBStreamer stream (state, kLittleEndian);
    for (const auto value : values_)
        if (!stream.writeFloat (static_cast<float> (value))) return kResultFalse;
    return kResultOk;
}
}
