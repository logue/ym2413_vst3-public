#include "Vst2413R.h"
#include "Vst2413RIds.h"
#include "pluginterfaces/vst/ivstevents.h"

namespace Steinberg::Vst {
Vst2413RProcessor::Vst2413RProcessor () { setControllerClass (Vst2413R::ControllerUID); }

tresult PLUGIN_API Vst2413RProcessor::initialize (FUnknown* context) {
    const auto result = AudioEffect::initialize (context);
    if (result != kResultOk) return result;
    addAudioOutput (STR16 ("Mono Out"), SpeakerArr::kMono);
    addEventInput (STR16 ("MIDI In"), 1);
    return kResultOk;
}

tresult PLUGIN_API Vst2413RProcessor::setupProcessing (ProcessSetup& setup) {
    driver_.SetSampleRate (static_cast<unsigned int> (setup.sampleRate));
    return AudioEffect::setupProcessing (setup);
}

tresult PLUGIN_API Vst2413RProcessor::setActive (TBool state) {
    if (!state) driver_.KeyOffAll ();
    return AudioEffect::setActive (state);
}

tresult PLUGIN_API Vst2413RProcessor::canProcessSampleSize (int32 sampleSize) {
    return sampleSize == kSample32 ? kResultOk : kResultFalse;
}

tresult PLUGIN_API Vst2413RProcessor::process (ProcessData& data) {
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
}
