cmake_minimum_required(VERSION 3.25)
project(vst2413_vst3 VERSION 1.0.0 LANGUAGES C CXX)

# The SDK is intentionally not tracked in this repository.  Point this cache
# variable at a VST 3 SDK checkout, or let the helper scripts create the
# documented local checkout under third_party/vst3sdk.
set(VST3_SDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/vst3sdk" CACHE PATH
    "Path to a Steinberg VST 3 SDK checkout")
if (NOT EXISTS "${VST3_SDK_ROOT}/CMakeLists.txt")
    message(FATAL_ERROR
        "VST 3 SDK was not found at '${VST3_SDK_ROOT}'. See docs/BUILD.md or run scripts/build-windows.ps1 -BootstrapSdk.")
endif()

# Keep SDK examples out of the product build.
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VSTGUI_SUPPORT ON CACHE BOOL "" FORCE)
set(SMTG_CREATE_PLUGIN_LINK OFF CACHE BOOL "" FORCE)
add_subdirectory("${VST3_SDK_ROOT}" "${CMAKE_BINARY_DIR}/vst3sdk")
add_subdirectory(vst3)
