#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"
#include "vstgui/plugin-bindings/vst3editor.h"

namespace Steinberg::Vst {
class Vst2413RController final : public EditController {
public:
    static FUnknown* createInstance (void*) { return static_cast<IEditController*> (new Vst2413RController); }
    tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE { return EditController::initialize (context); }
    tresult PLUGIN_API setComponentState (IBStream*) SMTG_OVERRIDE { return kResultOk; }
    IPlugView* PLUGIN_API createView (const char* name) SMTG_OVERRIDE;
};
}
