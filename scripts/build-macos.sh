#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd "$(dirname "$0")/.." && pwd)"
sdk_root="${VST3_SDK_ROOT:-$project_root/third_party/vst3sdk}"
build_dir="${BUILD_DIR:-$project_root/build}"
configuration="${CONFIGURATION:-Release}"

if ! command -v cmake >/dev/null; then
  echo "CMake 3.25 or newer is required." >&2
  exit 1
fi

if [[ ! -f "$sdk_root/CMakeLists.txt" ]]; then
  if [[ "${BOOTSTRAP_SDK:-0}" != "1" ]]; then
    echo "VST3 SDK was not found at '$sdk_root'. Set BOOTSTRAP_SDK=1 or VST3_SDK_ROOT." >&2
    exit 1
  fi
  command -v git >/dev/null || { echo "Git is required to fetch the VST3 SDK." >&2; exit 1; }
  mkdir -p "$(dirname "$sdk_root")"
  git clone --recursive https://github.com/steinbergmedia/vst3sdk.git "$sdk_root"
  git -C "$sdk_root" checkout 3cdf9ca4e1044ddc036393c50a3930cffcd8c694
  git -C "$sdk_root" submodule update --init --recursive
fi

cmake -S "$project_root" -B "$build_dir" \
  -DCMAKE_BUILD_TYPE="$configuration" \
  -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
  -DVST3_SDK_ROOT="$sdk_root"
cmake --build "$build_dir" --config "$configuration" --target vst2413p vst2413r vst2413s

echo "Built bundles: $build_dir/VST3/$configuration"
