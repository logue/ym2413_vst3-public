# ビルド / Build

## 日本語

VST3 SDK はリポジトリへコミットしていません。ライセンスと更新を明確にするため、ビルド時に別途取得します。固定対象は VST3 SDK 3.8.1、コミット `3cdf9ca4e1044ddc036393c50a3930cffcd8c694` です。

### Windows（検証済み）

必要なもの:

- Visual Studio 2022 または Build Tools の「Desktop development with C++」
- CMake 3.25 以上
- Git（`-BootstrapSdk` を使う場合）

**Developer PowerShell for VS 2022** から、SDK の取得・CMake 構成・3 プラグインの Release ビルドを一度に行えます。

```powershell
.\scripts\build-windows.ps1 -BootstrapSdk
```

SDK を別の場所へ置く場合:

```powershell
.\scripts\build-windows.ps1 -SdkRoot D:\SDK\vst3sdk
```

生成物は `build\VST3\Release\vst2413p.vst3`、`vst2413r.vst3`、`vst2413s.vst3` です。各 `.vst3` はフォルダー単位で扱ってください。SDK を含めない ZIP を作るには:

```powershell
.\scripts\package-release.ps1 -Version 1.0.0
```

### macOS（未検証）

必要なものは Xcode Command Line Tools、CMake 3.25 以上、Git です。スクリプトは universal binary を指定します。

```bash
BOOTSTRAP_SDK=1 bash scripts/build-macos.sh
bash scripts/install-macos.sh
```

これは macOS で実行・検証していません。実際に配布する前に、Intel と Apple Silicon、対象 DAW、コード署名、公証、Gatekeeper の動作を実機で確認してください。

## English

The VST3 SDK is deliberately not committed to this repository. It is obtained separately at build time to make licensing and updates explicit. The pinned target is VST3 SDK 3.8.1, commit `3cdf9ca4e1044ddc036393c50a3930cffcd8c694`.

### Windows (verified)

Requirements:

- Visual Studio 2022 or Build Tools with “Desktop development with C++”
- CMake 3.25 or newer
- Git (when using `-BootstrapSdk`)

From **Developer PowerShell for VS 2022**, fetch the SDK, configure CMake, and build all three Release plug-ins in one step:

```powershell
.\scripts\build-windows.ps1 -BootstrapSdk
```

To use an SDK in another location:

```powershell
.\scripts\build-windows.ps1 -SdkRoot D:\SDK\vst3sdk
```

The generated bundles are `build\VST3\Release\vst2413p.vst3`, `vst2413r.vst3`, and `vst2413s.vst3`. Treat every `.vst3` as a complete directory. To create a ZIP that does not contain the SDK:

```powershell
.\scripts\package-release.ps1 -Version 1.0.0
```

### macOS (not verified)

Requirements are Xcode Command Line Tools, CMake 3.25 or newer, and Git. The helper requests a universal binary.

```bash
BOOTSTRAP_SDK=1 bash scripts/build-macos.sh
bash scripts/install-macos.sh
```

This has not been executed or verified on macOS. Before distributing a macOS build, test Intel and Apple Silicon hardware, the target DAW, code signing, notarization, and Gatekeeper behavior on real machines.
