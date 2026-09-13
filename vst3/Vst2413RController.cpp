#include "Vst2413RController.h"
#include <cstring>

namespace Steinberg::Vst {
IPlugView* PLUGIN_API Vst2413RController::createView (const char* name) {
    if (name && std::strcmp (name, ViewType::kEditor) == 0)
        return new VSTGUI::VST3Editor (this, "view", "VST2413R.uidesc");
    return nullptr;
}
}
