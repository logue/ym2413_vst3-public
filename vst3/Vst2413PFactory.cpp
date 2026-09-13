#include "Vst2413P.h"
#include "Vst2413PController.h"
#include "Vst2413PIds.h"
#include "public.sdk/source/main/pluginfactory.h"

using namespace Steinberg;
using namespace Steinberg::Vst;
using namespace Steinberg::Vst::Vst2413P;

BEGIN_FACTORY_DEF ("VST2413 VST3 Port", "https://github.com/ruliciamisaki/ym2413_vst3-public", "")
    DEF_CLASS2 (INLINE_UID_FROM_FUID (ProcessorUID), PClassInfo::kManyInstances, kVstAudioEffectClass,
                "VST2413P", Vst::kDistributable, "Instrument|Synth", "1.0.0", kVstVersionString,
                Vst2413PProcessor::createInstance)
    DEF_CLASS2 (INLINE_UID_FROM_FUID (ControllerUID), PClassInfo::kManyInstances, kVstComponentControllerClass,
                "VST2413P Controller", 0, "", "1.0.0", kVstVersionString,
                Vst2413PController::createInstance)
END_FACTORY
