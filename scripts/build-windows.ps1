[CmdletBinding()]
param(
    [ValidateSet('Release', 'Debug')]
    [string]$Configuration = 'Release',
    [string]$SdkRoot = (Join-Path $PSScriptRoot '..\third_party\vst3sdk'),
    [string]$BuildDir = (Join-Path $PSScriptRoot '..\build'),
    [switch]$BootstrapSdk
)

$ErrorActionPreference = 'Stop'
$projectRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$SdkRoot = [IO.Path]::GetFullPath($SdkRoot)
$BuildDir = [IO.Path]::GetFullPath($BuildDir)

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    throw 'CMake 3.25 or newer is required. Install it, then run this script from a VS 2022 Developer PowerShell.'
}

if (-not (Test-Path (Join-Path $SdkRoot 'CMakeLists.txt'))) {
    if (-not $BootstrapSdk) {
        throw "VST3 SDK was not found at '$SdkRoot'. Re-run with -BootstrapSdk, or pass -SdkRoot."
    }
    if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
        throw 'Git is required to fetch the VST3 SDK.'
    }
    New-Item -ItemType Directory -Force -Path (Split-Path $SdkRoot -Parent) | Out-Null
    & git clone --recursive https://github.com/steinbergmedia/vst3sdk.git $SdkRoot
    & git -C $SdkRoot checkout 3cdf9ca4e1044ddc036393c50a3930cffcd8c694
    & git -C $SdkRoot submodule update --init --recursive
}

& cmake -S $projectRoot -B $BuildDir -G 'Visual Studio 17 2022' -A x64 "-DVST3_SDK_ROOT=$SdkRoot"
& cmake --build $BuildDir --config $Configuration --target vst2413p vst2413r vst2413s

Write-Host "Built bundles: $(Join-Path $BuildDir "VST3\\$Configuration")"
