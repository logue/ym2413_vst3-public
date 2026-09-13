#include "Vst2413S.h"
#include "Vst2413SController.h"
#include "Vst2413SIds.h"
#include "public.sdk/source/main/pluginfactory.h"

using namespace Steinberg;
using namespace Steinberg::Vst;
using namespace Steinberg::Vst::Vst2413S;

BEGIN_FACTORY_DEF ("VST2413 VST3 Port", "https://github.com/ruliciamisaki/ym2413_vst3-public", "")
    DEF_CLASS2 (INLINE_UID_FROM_FUID (ProcessorUID), PClassInfo::kManyInstances, kVstAudioEffectClass,
                "VST2413S", Vst::kDistributable, "Instrument|Synth", "1.0.0", kVstVersionString,
                Vst2413SProcessor::createInstance)
    DEF_CLASS2 (INLINE_UID_FROM_FUID (ControllerUID), PClassInfo::kManyInstances, kVstComponentControllerClass,
                "VST2413S Controller", 0, "", "1.0.0", kVstVersionString,
                Vst2413SController::createInstance)
END_FACTORY
