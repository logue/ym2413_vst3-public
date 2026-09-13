#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"
#include "vstgui/plugin-bindings/vst3editor.h"

namespace Steinberg::Vst {
class Vst2413SController final : public EditController {
public:
    static FUnknown* createInstance (void*) { return static_cast<IEditController*> (new Vst2413SController); }
    tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API setComponentState (IBStream* state) SMTG_OVERRIDE;
    tresult PLUGIN_API getParamStringByValue (ParamID tag, ParamValue value, String128 string) SMTG_OVERRIDE;
    tresult PLUGIN_API getParamValueByString (ParamID tag, TChar* string, ParamValue& value) SMTG_OVERRIDE;
    IPlugView* PLUGIN_API createView (const char* name) SMTG_OVERRIDE;
};
}
