# インストール / Installation

![VST Compatible](assets/VST_Compatible_Logo_Steinberg_with_TM.png)

## 日本語

### Windows（検証済み）

1. `VST2413-*-windows-x86_64.zip` を展開します。
2. `vst2413p.vst3`、`vst2413r.vst3`、`vst2413s.vst3` を、**フォルダーのまま**次のいずれかへコピーします。
   - 全ユーザー: `C:\Program Files\Common Files\VST3\`
   - 現在のユーザーのみ: `%LOCALAPPDATA%\Programs\Common\VST3\`
3. Cubase Pro 13 の **Studio > VST Plug-in Manager** を開き、再スキャンします。
4. インストゥルメントトラックへ VST2413P / R / S を追加します。

管理者権限の PowerShell なら、ビルド済みの状態で次のコマンドでも入れられます。

```powershell
.\scripts\install-windows.ps1
```

ユーザー専用ディレクトリへ入れる例はこれです。

```powershell
.\scripts\install-windows.ps1 -Destination "$env:LOCALAPPDATA\Programs\Common\VST3"
```

プラグインを削除する場合は、インストール先の対応する `.vst3` フォルダーを閉じた Cubase の状態で削除します。Cubase が読み込み中の DLL だけを削除しないでください。

### macOS（未検証）

ソースは Intel / Apple Silicon の universal binary を意図してビルド設定していますが、macOS 実機でのビルド、署名、DAW での読み込みをまだ検証していません。そのため、このリリースには macOS バイナリを同梱しません。

検証済みの macOS ビルドを将来配布する場合、通常のユーザー別配置先は `~/Library/Audio/Plug-Ins/VST3/` です。全ユーザー用の `/Library/Audio/Plug-Ins/VST3/` は管理者権限が必要です。未署名・未公証バイナリは macOS のセキュリティ設定により読み込みを拒否される場合があります。

## English

### Windows (verified)

1. Extract `VST2413-*-windows-x86_64.zip`.
2. Copy `vst2413p.vst3`, `vst2413r.vst3`, and `vst2413s.vst3` as complete **folders** to one of these locations.
   - All users: `C:\Program Files\Common Files\VST3\`
   - Current user: `%LOCALAPPDATA%\Programs\Common\VST3\`
3. Open **Studio > VST Plug-in Manager** in Cubase Pro 13 and rescan.
4. Add VST2413P / R / S to an instrument track.

From an elevated PowerShell, after building, installation can also be performed with:

```powershell
.\scripts\install-windows.ps1
```

For a per-user installation:

```powershell
.\scripts\install-windows.ps1 -Destination "$env:LOCALAPPDATA\Programs\Common\VST3"
```

To uninstall, close Cubase and remove the corresponding `.vst3` directory from the chosen location. Do not remove only a DLL while Cubase has loaded it.

### macOS (not verified)

The sources are configured to build a universal Intel / Apple Silicon binary, but no macOS machine build, signing, or DAW load has been verified. Therefore no macOS binary is included in this release.

For a future verified macOS build, the usual per-user location is `~/Library/Audio/Plug-Ins/VST3/`. `/Library/Audio/Plug-Ins/VST3/` is a system-wide location requiring administrator privileges. An unsigned and non-notarized binary can be rejected by macOS security controls.
