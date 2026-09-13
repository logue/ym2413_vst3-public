#include "Vst2413P.h"
#include "Vst2413PIds.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

namespace Steinberg::Vst {
using namespace Vst2413P;

Vst2413PProcessor::Vst2413PProcessor () { setControllerClass (ControllerUID); }

tresult PLUGIN_API Vst2413PProcessor::initialize (FUnknown* context) {
    const auto result = AudioEffect::initialize (context);
    if (result != kResultOk) return result;
    addAudioOutput (STR16 ("Mono Out"), SpeakerArr::kMono);
    addEventInput (STR16 ("MIDI In"), 1);
    applyParameter (kInstrument, instrument_);
    applyParameter (kPitchWheelRange, wheelRange_);
    applyParameter (kFineTune, fineTune_);
    return kResultOk;
}

tresult PLUGIN_API Vst2413PProcessor::setupProcessing (ProcessSetup& setup) {
    driver_.SetSampleRate (static_cast<unsigned int> (setup.sampleRate));
    return AudioEffect::setupProcessing (setup);
}

tresult PLUGIN_API Vst2413PProcessor::setActive (TBool state) {
    if (!state) driver_.KeyOffAll ();
    return AudioEffect::setActive (state);
}

tresult PLUGIN_API Vst2413PProcessor::canProcessSampleSize (int32 sampleSize) {
    return sampleSize == kSample32 ? kResultOk : kResultFalse;
}

void Vst2413PProcessor::applyParameter (ParamID id, ParamValue value) {
    switch (id) {
        case kInstrument:
            instrument_ = value;
            driver_.SetProgram (static_cast<SynthDriver::ProgramID> (1 + static_cast<int> (value * 14.0)));
            break;
        case kPitchWheelRange:
            wheelRange_ = value;
            driver_.SetParameter (SynthDriver::kParameterWheelRange, static_cast<float> (value));
            break;
        case kFineTune:
            fineTune_ = value;
            driver_.SetParameter (SynthDriver::kParameterFineTune, static_cast<float> (value));
            break;
    }
}

void Vst2413PProcessor::applyEvents (IEventList* events) {
    if (!events) return;
    for (int32 i = 0; i < events->getEventCount (); ++i) {
        Event event {};
        if (events->getEvent (i, event) != kResultOk) continue;
        if (event.type == Event::kNoteOnEvent)
            driver_.KeyOn (event.noteOn.pitch, event.noteOn.velocity);
        else if (event.type == Event::kNoteOffEvent)
            driver_.KeyOff (event.noteOff.pitch);
    }
}

void Vst2413PProcessor::render (Sample32* output, int32 frames) {
    for (int32 i = 0; i < frames; ++i) output[i] = driver_.Step ();
}

tresult PLUGIN_API Vst2413PProcessor::process (ProcessData& data) {
    if (auto* changes = data.inputParameterChanges) {
        for (int32 i = 0; i < changes->getParameterCount (); ++i) {
            if (auto* queue = changes->getParameterData (i)) {
                int32 offset = 0; ParamValue value = 0.;
                if (queue->getPoint (queue->getPointCount () - 1, offset, value) == kResultTrue)
                    applyParameter (queue->getParameterId (), value);
            }
        }
    }
    applyEvents (data.inputEvents);
    if (data.numOutputs < 1 || !data.outputs[0].channelBuffers32) return kResultOk;
    render (data.outputs[0].channelBuffers32[0], data.numSamples);
    data.outputs[0].silenceFlags = 0;
    return kResultOk;
}

tresult PLUGIN_API Vst2413PProcessor::setState (IBStream* state) {
    IBStreamer stream (state, kLittleEndian);
    float instrument = 0, wheel = .25f, tune = .5f;
    if (!stream.readFloat (instrument) || !stream.readFloat (wheel) || !stream.readFloat (tune)) return kResultFalse;
    applyParameter (kInstrument, instrument); applyParameter (kPitchWheelRange, wheel); applyParameter (kFineTune, tune);
    return kResultOk;
}

tresult PLUGIN_API Vst2413PProcessor::getState (IBStream* state) {
    IBStreamer stream (state, kLittleEndian);
    return stream.writeFloat (static_cast<float> (instrument_)) && stream.writeFloat (static_cast<float> (wheelRange_)) && stream.writeFloat (static_cast<float> (fineTune_)) ? kResultOk : kResultFalse;
}
}
