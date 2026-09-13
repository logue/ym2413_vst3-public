#include "Vst2413PController.h"
#include "Vst2413PIds.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ustring.h"
#include <algorithm>
#include <cstring>

namespace Steinberg::Vst {
using namespace Vst2413P;

tresult PLUGIN_API Vst2413PController::initialize (FUnknown* context) {
    const auto result = EditController::initialize (context);
    if (result != kResultOk) return result;
    auto* instrument = new StringListParameter (STR16 ("Instrument"), kInstrument, nullptr);
    instrument->appendString (STR16 ("Violin"));
    instrument->appendString (STR16 ("Guitar"));
    instrument->appendString (STR16 ("Piano"));
    instrument->appendString (STR16 ("Flute"));
    instrument->appendString (STR16 ("Clarinet"));
    instrument->appendString (STR16 ("Oboe"));
    instrument->appendString (STR16 ("Trumpet"));
    instrument->appendString (STR16 ("Organ"));
    instrument->appendString (STR16 ("Horn"));
    instrument->appendString (STR16 ("Synthesizer"));
    instrument->appendString (STR16 ("Harpsichord"));
    instrument->appendString (STR16 ("Vibraphone"));
    instrument->appendString (STR16 ("S.Bass"));
    instrument->appendString (STR16 ("A.Bass"));
    instrument->appendString (STR16 ("E.Guitar"));
    parameters.addParameter (instrument);
    parameters.addParameter (STR16 ("Pitch Wheel Range"), STR16 ("st"), 0, .25, ParameterInfo::kCanAutomate, kPitchWheelRange);
    parameters.addParameter (STR16 ("Fine Tune"), STR16 ("cent"), 0, .5, ParameterInfo::kCanAutomate, kFineTune);
    return kResultOk;
}

tresult PLUGIN_API Vst2413PController::setComponentState (IBStream* state) {
    IBStreamer stream (state, kLittleEndian);
    float instrument = 0, wheel = .25f, tune = .5f;
    if (!stream.readFloat (instrument) || !stream.readFloat (wheel) || !stream.readFloat (tune)) return kResultFalse;
    setParamNormalized (kInstrument, instrument); setParamNormalized (kPitchWheelRange, wheel); setParamNormalized (kFineTune, tune);
    return kResultOk;
}

tresult PLUGIN_API Vst2413PController::getParamStringByValue (
    ParamID tag, ParamValue value, String128 string) {
    UString128 text;
    if (tag == kPitchWheelRange)
        text.printFloat (value * 12.0, 0);
    else if (tag == kFineTune)
        text.printFloat ((value - 0.5) * 100.0, 1);
    else
        return EditController::getParamStringByValue (tag, value, string);
    text.copyTo (string, 128);
    return kResultTrue;
}

tresult PLUGIN_API Vst2413PController::getParamValueByString (
    ParamID tag, TChar* string, ParamValue& value) {
    if (tag != kPitchWheelRange && tag != kFineTune)
        return EditController::getParamValueByString (tag, string, value);
    UString text (string, -1);
    double parsed = 0.0;
    if (!text.scanFloat (parsed)) return kResultFalse;
    value = tag == kPitchWheelRange ? parsed / 12.0 : parsed / 100.0 + 0.5;
    value = std::clamp (value, 0.0, 1.0);
    return kResultTrue;
}

IPlugView* PLUGIN_API Vst2413PController::createView (const char* name) {
    if (name && std::strcmp (name, ViewType::kEditor) == 0)
        return new VSTGUI::VST3Editor (this, "view", "VST2413P.uidesc");
    return nullptr;
}
}
