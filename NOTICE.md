# 由来と変更の通知 / Provenance and modification notice

## 日本語

このリポジトリは [keijiro/vst2413](https://github.com/keijiro/vst2413) を出発点に、64-bit VST3 としてビルドできるよう整備した派生版です。原版を作者自身が変更・公開したものではありません。

`source/emu2413/emu2413.c` は Mitsutaka Okazaki 氏の emu2413 を含みます。Windows ヘッダーと列挙子が衝突しないよう、エンベロープ状態の列挙子へ `EG_` 接頭辞を付けるだけの変更を加えました。音源アルゴリズムや音色テーブルは変更していません。この変更済みソースには、ファイル先頭にも改変版である旨を明記しています。

`source/SynthDriver.cpp` と `source/SynthDriver.h` には、VST2413S で YM2413 の EG / KSR / KSL ビットをレジスタへ転送するための拡張があります。

VST3 SDK 3.8.1（コミット `3cdf9ca4e1044ddc036393c50a3930cffcd8c694`）はビルド時の依存関係です。SDK 本体は本リポジトリに含めず、MIT ライセンスに従って取得します。

## English

This repository is a derived buildable 64-bit VST3 port of [keijiro/vst2413](https://github.com/keijiro/vst2413). It is not presented as an author-maintained release of the original project.

`source/emu2413/emu2413.c` includes Mitsutaka Okazaki's emu2413. Its envelope-state enumerators have been prefixed with `EG_` solely to avoid collisions with Windows headers. The sound algorithm and tone tables were not changed. The file itself is plainly marked as an altered source version.

`source/SynthDriver.cpp` and `source/SynthDriver.h` extend VST2413S so its EG / KSR / KSL controls are written to the corresponding YM2413 registers.

VST3 SDK 3.8.1 (commit `3cdf9ca4e1044ddc036393c50a3930cffcd8c694`) is a build-time dependency. The SDK is not bundled in this repository and is obtained under its MIT license.
