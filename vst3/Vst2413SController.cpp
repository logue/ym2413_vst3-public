#include "Vst2413SController.h"
#include "Vst2413SIds.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ustring.h"
#include <algorithm>
#include <cmath>
#include <cstring>

namespace Steinberg::Vst {
using namespace Vst2413S;

tresult PLUGIN_API Vst2413SController::initialize (FUnknown* context) {
    const auto result = EditController::initialize (context);
    if (result != kResultOk) return result;
    const auto autoFlag = ParameterInfo::kCanAutomate;
    // Common patch parameters.
    parameters.addParameter (STR16 ("Total Level (TL)"), nullptr, 63, 0, autoFlag, kTL);
    parameters.addParameter (STR16 ("Feedback (FB)"), nullptr, 7, 0, autoFlag, kFB);

    // Modulator: primary envelope controls, then secondary shaping controls.
    parameters.addParameter (STR16 ("Modulator Envelope Type (EG)"), nullptr, 1, 1, autoFlag, kEG0);
    parameters.addParameter (STR16 ("Modulator Multiple (MUL)"), nullptr, 15, 1.0 / 15.0, autoFlag, kMUL0);
    parameters.addParameter (STR16 ("Modulator Attack (AR)"), nullptr, 15, 0, autoFlag, kAR0);
    parameters.addParameter (STR16 ("Modulator Decay (DR)"), nullptr, 15, 0, autoFlag, kDR0);
    parameters.addParameter (STR16 ("Modulator Sustain Level (SL)"), nullptr, 15, 1, autoFlag, kSL0);
    parameters.addParameter (STR16 ("Modulator Release (RR)"), nullptr, 15, 0, autoFlag, kRR0);
    parameters.addParameter (STR16 ("Modulator Key Rate Scaling (KSR)"), nullptr, 1, 0, autoFlag, kKSR0);
    parameters.addParameter (STR16 ("Modulator Key Level Scaling (KSL)"), nullptr, 3, 0, autoFlag, kKSL0);
    parameters.addParameter (STR16 ("Modulator Tremolo (AM)"), nullptr, 1, 0, autoFlag, kAM0);
    parameters.addParameter (STR16 ("Modulator Vibrato (VIB)"), nullptr, 1, 0, autoFlag, kVIB0);
    parameters.addParameter (STR16 ("Modulator Distortion"), nullptr, 1, 0, autoFlag, kDM);

    // Carrier: same order as the modulator.
    parameters.addParameter (STR16 ("Carrier Envelope Type (EG)"), nullptr, 1, 1, autoFlag, kEG1);
    parameters.addParameter (STR16 ("Carrier Multiple (MUL)"), nullptr, 15, 1.0 / 15.0, autoFlag, kMUL1);
    parameters.addParameter (STR16 ("Carrier Attack (AR)"), nullptr, 15, 0, autoFlag, kAR1);
    parameters.addParameter (STR16 ("Carrier Decay (DR)"), nullptr, 15, 0, autoFlag, kDR1);
    parameters.addParameter (STR16 ("Carrier Sustain Level (SL)"), nullptr, 15, 1, autoFlag, kSL1);
    parameters.addParameter (STR16 ("Carrier Release (RR)"), nullptr, 15, 0, autoFlag, kRR1);
    parameters.addParameter (STR16 ("Carrier Key Rate Scaling (KSR)"), nullptr, 1, 0, autoFlag, kKSR1);
    parameters.addParameter (STR16 ("Carrier Key Level Scaling (KSL)"), nullptr, 3, 0, autoFlag, kKSL1);
    parameters.addParameter (STR16 ("Carrier Tremolo (AM)"), nullptr, 1, 0, autoFlag, kAM1);
    parameters.addParameter (STR16 ("Carrier Vibrato (VIB)"), nullptr, 1, 0, autoFlag, kVIB1);
    parameters.addParameter (STR16 ("Carrier Distortion"), nullptr, 1, 0, autoFlag, kDC);

    // Performance controls are not part of the eight-byte user patch.
    parameters.addParameter (STR16 ("Pitch Wheel Range"), STR16 ("st"), 12, .25, autoFlag, kWheelRange);
    parameters.addParameter (STR16 ("Fine Tune"), STR16 ("cent"), 0, .5, autoFlag, kFineTune);
    return kResultOk;
}

tresult PLUGIN_API Vst2413SController::setComponentState (IBStream* state) {
    IBStreamer stream (state, kLittleEndian);
    for (ParamID id = 0; id <= kFineTune; ++id) {
        float value = 0.f;
        if (!stream.readFloat (value)) return kResultFalse;
        setParamNormalized (id, value);
    }
    for (ParamID id = kEG0; id < kParameterCount; ++id) {
        float value = static_cast<float> (getParamNormalized (id));
        if (!stream.readFloat (value)) break;
        setParamNormalized (id, value);
    }
    return kResultOk;
}

tresult PLUGIN_API Vst2413SController::getParamStringByValue (
    ParamID tag, ParamValue value, String128 string) {
    UString128 text;
    const bool inverted15 = tag <= kRR1;
    const bool direct15 = tag == kMUL0 || tag == kMUL1;
    if (inverted15) text.printInt (static_cast<int64> (std::lround ((1.0 - value) * 15.0)));
    else if (direct15) text.printInt (static_cast<int64> (std::lround (value * 15.0)));
    else if (tag == kFB) text.printInt (static_cast<int64> (std::lround (value * 7.0)));
    else if (tag == kTL) text.printInt (static_cast<int64> (std::lround ((1.0 - value) * 63.0)));
    else if (tag == kKSL0 || tag == kKSL1) text.printInt (static_cast<int64> (std::lround (value * 3.0)));
    else if (tag == kWheelRange) text.printFloat (value * 12.0, 0);
    else if (tag == kFineTune) text.printFloat ((value - .5) * 100.0, 1);
    else if (tag == kEG0 || tag == kEG1)
        text.printInt (static_cast<int64> (value < .5 ? 0 : 1));
    else if ((tag >= kDM && tag <= kVIB1) || tag == kKSR0 || tag == kKSR1)
        text.fromAscii (value < .5 ? "OFF" : "ON");
    else return EditController::getParamStringByValue (tag, value, string);
    text.copyTo (string, 128);
    return kResultTrue;
}

tresult PLUGIN_API Vst2413SController::getParamValueByString (
    ParamID tag, TChar* string, ParamValue& value) {
    const bool inverted15 = tag <= kRR1;
    const bool direct15 = tag == kMUL0 || tag == kMUL1;
    const bool numericToggle = tag == kEG0 || tag == kEG1;
    const bool toggle = (tag >= kDM && tag <= kVIB1) || tag == kKSR0 || tag == kKSR1;
    const bool rawNumber = inverted15 || direct15 || tag == kFB || tag == kTL ||
                           tag == kKSL0 || tag == kKSL1;
    if (numericToggle) {
        UString text (string, -1);
        double parsed = 0.0;
        if (!text.scanFloat (parsed)) return kResultFalse;
        value = parsed < 0.5 ? 0.0 : 1.0;
        return kResultTrue;
    }
    if (toggle) {
        if (!string) return kResultFalse;
        const auto first = string[0] >= u'a' && string[0] <= u'z' ? string[0] - 32 : string[0];
        const auto second = string[1] >= u'a' && string[1] <= u'z' ? string[1] - 32 : string[1];
        if (first == u'O' && second == u'N') value = 1.0;
        else if (first == u'O' && second == u'F') value = 0.0;
        else return EditController::getParamValueByString (tag, string, value);
        return kResultTrue;
    }
    if (!rawNumber && tag != kWheelRange && tag != kFineTune)
        return EditController::getParamValueByString (tag, string, value);

    UString text (string, -1);
    double parsed = 0.0;
    if (!text.scanFloat (parsed)) return kResultFalse;

    if (inverted15) value = 1.0 - parsed / 15.0;
    else if (direct15) value = parsed / 15.0;
    else if (tag == kFB) value = parsed / 7.0;
    else if (tag == kTL) value = 1.0 - parsed / 63.0;
    else if (tag == kKSL0 || tag == kKSL1) value = parsed / 3.0;
    else if (tag == kWheelRange) value = parsed / 12.0;
    else value = parsed / 100.0 + 0.5;
    value = std::clamp (value, 0.0, 1.0);
    return kResultTrue;
}

IPlugView* PLUGIN_API Vst2413SController::createView (const char* name) {
    if (name && std::strcmp (name, ViewType::kEditor) == 0)
        return new VSTGUI::VST3Editor (this, "view", "VST2413S.uidesc");
    return nullptr;
}
}
