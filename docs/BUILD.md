# ビルド / Build

## 日本語

VST3 SDK（MIT ライセンス）は [vcpkg](https://vcpkg.io/) のマニフェストモードで取得します。公式ポートは VSTGUI と CMake ヘルパーを含まないため、SDK ソース一式（VSTGUI 込み）を導入するオーバーレイポート [`ports/vst3sdk-source`](../ports/vst3sdk-source) を使います。固定対象は VST3 SDK `v3.8.1_build_84` です。CMake 構成時に vcpkg が自動で取得するため、手動の SDK チェックアウトは不要です（`-DVST3_SDK_ROOT=...` で任意の SDK を指定することもできます）。

共通の準備: vcpkg をインストールし、環境変数 `VCPKG_ROOT` を設定してください。

### Windows（検証済み）

必要なもの:

- Visual Studio 2022 または Build Tools の「Desktop development with C++」
- CMake 3.25 以上
- vcpkg（`VCPKG_ROOT`）

**Developer PowerShell for VS 2022** から:

```powershell
.\scripts\build-windows.ps1
```

生成物は `build\VST3\Release\vst2413p.vst3`、`vst2413r.vst3`、`vst2413s.vst3` です。各 `.vst3` はフォルダー単位で扱ってください。SDK を含めない ZIP を作るには:

```powershell
.\scripts\package-release.ps1 -Version 1.0.0
```

### macOS

必要なものは Xcode または Xcode Command Line Tools、CMake 3.25 以上、vcpkg（`VCPKG_ROOT`）です。スクリプトは universal binary を指定します。Command Line Tools のみの場合は、SDK の Xcode バージョン検査を通すため `XCODE_VERSION` を自動設定します。

```bash
bash scripts/build-macos.sh
bash scripts/install-macos.sh
```

Apple Silicon (Command Line Tools) でビルドと SDK validator の通過を確認済みですが、DAW での動作は未検証です。実際に配布する前に、Intel と Apple Silicon、対象 DAW、コード署名、公証、Gatekeeper の動作を実機で確認してください。

## English

The VST3 SDK (MIT licensed) is obtained through [vcpkg](https://vcpkg.io/) manifest mode. The official port omits VSTGUI and the CMake helpers, so the overlay port [`ports/vst3sdk-source`](../ports/vst3sdk-source) installs the full SDK source tree including VSTGUI. The pinned target is VST3 SDK `v3.8.1_build_84`. vcpkg fetches it automatically during CMake configure, so no manual SDK checkout is needed (`-DVST3_SDK_ROOT=...` still overrides it).

Common setup: install vcpkg and set the `VCPKG_ROOT` environment variable.

### Windows (verified)

Requirements:

- Visual Studio 2022 or Build Tools with “Desktop development with C++”
- CMake 3.25 or newer
- vcpkg (`VCPKG_ROOT`)

From **Developer PowerShell for VS 2022**:

```powershell
.\scripts\build-windows.ps1
```

The generated bundles are `build\VST3\Release\vst2413p.vst3`, `vst2413r.vst3`, and `vst2413s.vst3`. Treat every `.vst3` as a complete directory. To create a ZIP that does not contain the SDK:

```powershell
.\scripts\package-release.ps1 -Version 1.0.0
```

### macOS

Requirements are Xcode or the Xcode Command Line Tools, CMake 3.25 or newer, and vcpkg (`VCPKG_ROOT`). The helper requests a universal binary. With Command Line Tools only, it sets `XCODE_VERSION` automatically so the SDK's Xcode version check passes.

```bash
bash scripts/build-macos.sh
bash scripts/install-macos.sh
```

The build and the SDK validator have been confirmed on Apple Silicon (Command Line Tools), but DAW behavior is not verified. Before distributing a macOS build, test Intel and Apple Silicon hardware, the target DAW, code signing, notarization, and Gatekeeper behavior on real machines.
