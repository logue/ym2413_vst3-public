#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "SynthDriver.h"

namespace Steinberg::Vst {

class Vst2413PProcessor final : public AudioEffect {
public:
    Vst2413PProcessor ();
    static FUnknown* createInstance (void*) { return static_cast<IAudioProcessor*> (new Vst2413PProcessor); }

    tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API setupProcessing (ProcessSetup& setup) SMTG_OVERRIDE;
    tresult PLUGIN_API setActive (TBool state) SMTG_OVERRIDE;
    tresult PLUGIN_API process (ProcessData& data) SMTG_OVERRIDE;
    tresult PLUGIN_API canProcessSampleSize (int32 sampleSize) SMTG_OVERRIDE;
    tresult PLUGIN_API setState (IBStream* state) SMTG_OVERRIDE;
    tresult PLUGIN_API getState (IBStream* state) SMTG_OVERRIDE;

private:
    void applyParameter (ParamID id, ParamValue value);
    void applyEvents (IEventList* events);
    void render (Sample32* output, int32 frames);

    SynthDriver driver_ {44100};
    ParamValue instrument_ {0.};
    ParamValue wheelRange_ {0.25};
    ParamValue fineTune_ {0.5};
};
}
