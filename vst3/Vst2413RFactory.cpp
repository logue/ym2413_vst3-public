#include "Vst2413R.h"
#include "Vst2413RController.h"
#include "Vst2413RIds.h"
#include "public.sdk/source/main/pluginfactory.h"

using namespace Steinberg;
using namespace Steinberg::Vst;
using namespace Steinberg::Vst::Vst2413R;

BEGIN_FACTORY_DEF ("VST2413 VST3 Port", "https://github.com/ruliciamisaki/ym2413_vst3-public", "")
    DEF_CLASS2 (INLINE_UID_FROM_FUID (ProcessorUID), PClassInfo::kManyInstances, kVstAudioEffectClass,
                "VST2413R", Vst::kDistributable, "Instrument|Drum", "1.0.0", kVstVersionString,
                Vst2413RProcessor::createInstance)
    DEF_CLASS2 (INLINE_UID_FROM_FUID (ControllerUID), PClassInfo::kManyInstances, kVstComponentControllerClass,
                "VST2413R Controller", 0, "", "1.0.0", kVstVersionString,
                Vst2413RController::createInstance)
END_FACTORY
