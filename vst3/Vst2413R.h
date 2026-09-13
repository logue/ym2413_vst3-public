#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "RhythmDriver.h"

namespace Steinberg::Vst {
class Vst2413RProcessor final : public AudioEffect {
public:
    Vst2413RProcessor ();
    static FUnknown* createInstance (void*) { return static_cast<IAudioProcessor*> (new Vst2413RProcessor); }
    tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API setupProcessing (ProcessSetup& setup) SMTG_OVERRIDE;
    tresult PLUGIN_API setActive (TBool state) SMTG_OVERRIDE;
    tresult PLUGIN_API process (ProcessData& data) SMTG_OVERRIDE;
    tresult PLUGIN_API canProcessSampleSize (int32 sampleSize) SMTG_OVERRIDE;
    tresult PLUGIN_API setState (IBStream*) SMTG_OVERRIDE { return kResultOk; }
    tresult PLUGIN_API getState (IBStream*) SMTG_OVERRIDE { return kResultOk; }
private:
    RhythmDriver driver_ {44100};
};
}
