#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace Steinberg::Vst::Vst2413S {
static const FUID ProcessorUID (0x2CA72C6B, 0xFC404D12, 0xB52F8D48, 0x2B1FB8D3);
static const FUID ControllerUID (0x9B91F63A, 0xD87E4BF5, 0xA7D81A37, 0x98C150E4);
enum ParamIds : ParamID {
    kAR0, kAR1, kDR0, kDR1, kSL0, kSL1, kRR0, kRR1,
    kMUL0, kMUL1, kFB, kTL, kDM, kDC, kAM0, kAM1, kVIB0, kVIB1,
    kWheelRange, kFineTune, kEG0, kEG1, kKSR0, kKSR1, kKSL0, kKSL1,
    kParameterCount
};
}
