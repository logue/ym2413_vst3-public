#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace Steinberg::Vst::Vst2413P {
static const FUID ProcessorUID (0xD67D29A1, 0x4D774C07, 0xA6AB01D5, 0xCF7AB024);
static const FUID ControllerUID (0xAA6E26EF, 0x502F4F50, 0xB71F7B8F, 0xA9B23C34);

enum ParamIds : ParamID {
    kInstrument = 0,
    kPitchWheelRange = 1,
    kFineTune = 2,
};
}
