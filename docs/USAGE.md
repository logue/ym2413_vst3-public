# VST2413 ユーザーガイド / User guide

## 日本語

### 1. 最初に

VST2413 は YM2413（OPLL）を再現するモノラル出力の VST3 インストゥルメントです。Cubase ではインストゥルメントトラックを追加し、目的に応じて次のいずれかを選びます。

| プラグイン | 使いどころ |
| --- | --- |
| VST2413P | 内蔵音色を選んですぐ演奏したいとき |
| VST2413R | YM2413 のドラム音を MIDI ノートで鳴らしたいとき |
| VST2413S | MSX-MUSIC のユーザー音色 0 を自分で作りたいとき |

鍵盤、MIDI キーボード、または MIDI パートからノートを送れば発音します。P と S は最大 9 音です。10 音以上を同時に鳴らす使い方は避けてください。出力はモノラルなので、ステレオ上の位置や空間処理は Cubase 側のパン、コーラス、ディレイ、リバーブなどで行います。

### 2. YM2413 を理解するための最小知識

YM2413 は、1つの音を2つのオペレータで作る FM 音源です。

- **MODULATOR（M）**は、主に倍音の量や音の硬さを作ります。
- **CARRIER（C）**は、最終的に聞こえる音量と音量変化の骨格を作ります。

基本的には、CARRIER で音の立ち上がりと長さを作り、MODULATOR の LEVEL、MUL、エンベロープ、FEEDBACK で音色を変えます。VST2413P はチップ内蔵の15音色を使い、VST2413S はユーザー音色 0 の8バイト相当を編集します。

YM2413 のユーザー音色はチップ全体で1つだけです。VST2413S でも、同時に鳴っている9音はすべて同じパッチを共有します。これは不具合ではなく YM2413 の構造です。

### 3. VST2413P — 内蔵音色

`INSTRUMENT PROGRAM` から次の15音色を選びます。

`Violin / Guitar / Piano / Flute / Clarinet / Oboe / Trumpet / Organ / Horn / Synthesizer / Harpsichord / Vibraphone / S.Bass / A.Bass / E.Guitar`

- **Instrument**: 内蔵音色を選択します。演奏中のオートメーションも可能です。
- **Fine Tune**: 全体の音程を -50 ～ +50 cent の範囲で調整します。`0` が基準です。
- **Pitch Wheel Range**: ピッチベンド幅を 0 ～ 12 semitone で設定する項目です。ただし現在の VST3 版では MIDI pitch bend 入力が音源へ接続されていないため、単独では音程を変えません。

ベロシティは発音音量に反映されます。まずは `Piano`、`Organ`、`S.Bass` を選ぶと、それぞれの性格を比較しやすいです。

### 4. VST2413R — リズム音源

R には音色パラメータがありません。次の MIDI ノートを送って演奏します。

| MIDI note | GM 名の目安 | YM2413 の音 |
| ---: | --- | --- |
| 36 | Bass Drum 1 | KICK |
| 38 | Acoustic Snare | SNARE |
| 42 / 44 | Closed / Pedal Hi-Hat | HAT |
| 43 / 47 / 50 | Floor / Mid / High Tom | TOM |
| 49 / 51 | Crash / Ride Cymbal | CYMBAL |

同じ欄に複数ノートがあるものは、YM2413 上では同じドラム音を鳴らします。ノート番号による音程差はありません。ベロシティは各ドラムの音量に反映されます。Cubase の Drum Editor か、上記ノートへ割り当てたパッドを使うと扱いやすくなります。

### 5. VST2413S — ユーザー音色

画面の数値は 0.0 ～ 1.0 の正規化値ではなく、原則として YM2413 のレジスタ値で表示されます。数値欄へ直接入力することもできます。

#### 共通パッチパラメータ

| パラメータ | 範囲 | 効果 |
| --- | ---: | --- |
| Total Level (TL) | 0 ～ 63 | MODULATOR のレベル。`0` で変調が最も強く、`63` で最も弱くなります。小さいほど明るく複雑、大きいほど丸く正弦波に近い音になります。 |
| Feedback (FB) | 0 ～ 7 | MODULATOR の自己フィードバック。大きくすると倍音やざらつきが増えます。 |

TL は画面上では共通欄にありますが、レジスタ上は MODULATOR の Total Level です。プラグイン全体の出力ボリュームではありません。

#### MODULATOR / CARRIER 共通パラメータ

| パラメータ | 範囲 | 効果 |
| --- | ---: | --- |
| Envelope Type (EG) | 0 / 1 | `0` は減衰音向け、`1` は鍵盤を押している間の持続音向けです。 |
| Multiple (MUL) | 0 ～ 15 | オペレータの周波数倍率。MUL の組み合わせが倍音構成を大きく変えます。 |
| Attack (AR) | 0 ～ 15 | 立ち上がり速度。`15` が最速です。小さすぎると発音が非常に遅くなります。 |
| Decay (DR) | 0 ～ 15 | アタック後に SL まで下がる速度。大きいほど速く減衰します。 |
| Sustain Level (SL) | 0 ～ 15 | ディケイ後の減衰量。`0` が最も大きな音量、`15` が最も小さな音量です。 |
| Release (RR) | 0 ～ 15 | ノートオフ後の減衰速度。大きいほど速く消えます。 |
| Key Rate Scaling (KSR) | OFF / ON | ON にすると音域によってエンベロープ速度が変化します。高音側を速くしたいときに使います。 |
| Key Level Scaling (KSL) | 0 ～ 3 | 高音域ほどレベルを減衰させます。大きいほど効果が強くなります。 |
| Tremolo (AM) | OFF / ON | チップ内蔵 LFO による音量の揺れを有効にします。 |
| Vibrato (VIB) | OFF / ON | チップ内蔵 LFO による音程の揺れを有効にします。 |
| Distortion | OFF / ON | DM / DC ビットによる半波整流波形を選びます。一般的な distortion エフェクトではありません。M と C で別々に設定できます。 |

MUL のレジスタ値と実際の倍率は、順に `1/2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 12, 12, 15, 15` です。

#### その他

- **Fine Tune**: 全体の音程を -50 ～ +50 cent で調整します。
- **Pitch Wheel Range**: 0 ～ 12 semitone の設定値です。ただし現在の VST3 版では MIDI pitch bend 入力が未接続です。

### 6. 最初の音を作る

まず次の値から始めると、音が出る状態で各パラメータの効果を確認できます。これは YM2413 の公式プリセットではなく、調整用の出発点です。

| 区分 | 設定 |
| --- | --- |
| COMMON | TL `32`、FB `2` |
| MODULATOR | EG `1`、MUL `1`、AR `15`、DR `4`、SL `8`、RR `5` |
| CARRIER | EG `1`、MUL `1`、AR `15`、DR `4`、SL `4`、RR `5` |
| DETAIL | KSR OFF、KSL `0`、AM OFF、VIB OFF、DISTORTION OFF |
| OTHER | Fine Tune `0` |

そこから次の順で触ると変化を理解しやすくなります。

1. CARRIER の AR / DR / SL / RR で音量の形を決めます。
2. TL を下げ、MODULATOR の変調量を増やします。
3. MODULATOR の MUL を変えて倍音の位置を動かします。
4. FB を上げて硬さを加えます。
5. AM / VIB、必要なら DISTORTION を加えます。

音が出ないときは、まず CARRIER の AR を `15`、SL を `0` ～ `8`、MUL を `1` に戻してください。高い TL は変調を弱めますが、CARRIER 自体を消音する値ではありません。

### 7. オートメーションと保存

P と S のパラメータは Cubase のオートメーション対象です。トラックのオートメーションレーンから対象パラメータを選び、書き込みまたは描画します。プラグインの状態は Cubase プロジェクトおよびホストのプリセットへ保存されます。

ユーザー音色を切り替えるオートメーションでは、その時点で鳴っている VST2413S の全ボイスが同じパッチ変更を受けます。音色ごとに別インスタンスを用意すると管理しやすくなります。

### 8. 参考資料について

本ガイドの説明文と表は、このプラグインの実装および YM2413 の動作を基に独自に記述しています。外部資料の文章・図・表は転載していません。

- Yamaha, *YM2413 OPLL Applications Manual*
- Mitsutaka Okazaki, `emu2413`（本リポジトリの `source/emu2413/`）

---

## English

### 1. Getting started

VST2413 is a mono-output VST3 instrument that emulates the YM2413 (OPLL). Create an instrument track in Cubase and select the plug-in that matches the job.

| Plug-in | Use |
| --- | --- |
| VST2413P | Play the chip's built-in instrument patches |
| VST2413R | Trigger YM2413 drums with MIDI notes |
| VST2413S | Design MSX-MUSIC user patch 0 |

Play it from a keyboard, MIDI controller, or MIDI part. P and S provide up to nine voices; avoid sending more than nine simultaneous notes. The output is mono, so use Cubase panning, chorus, delay, or reverb for stereo placement and space.

### 2. The minimum YM2413 model

The YM2413 is a two-operator FM synthesizer.

- The **MODULATOR (M)** mainly creates harmonic content and hardness.
- The **CARRIER (C)** mainly creates the audible level and amplitude contour.

Start by shaping the volume contour with the CARRIER, then change timbre with MODULATOR LEVEL, MUL, envelope, and FEEDBACK. VST2413P uses the 15 chip presets. VST2413S edits the equivalent of the eight-byte user patch 0.

The YM2413 has only one user patch for the entire chip. Accordingly, all nine simultaneous VST2413S voices share the same patch. This is part of the hardware model, not a plug-in fault.

### 3. VST2413P — preset instrument

Select one of these 15 voices from `INSTRUMENT PROGRAM`:

`Violin / Guitar / Piano / Flute / Clarinet / Oboe / Trumpet / Organ / Horn / Synthesizer / Harpsichord / Vibraphone / S.Bass / A.Bass / E.Guitar`

- **Instrument** selects the chip preset and can be automated.
- **Fine Tune** adjusts global tuning from -50 to +50 cents. `0` is neutral.
- **Pitch Wheel Range** specifies 0 to 12 semitones. In the current VST3 port, incoming MIDI pitch bend is not connected to the engine, so this control does not change pitch by itself.

Velocity controls note level. `Piano`, `Organ`, and `S.Bass` are useful starting points for comparing the preset characters.

### 4. VST2413R — rhythm instrument

R has no sound parameters. Trigger it with these MIDI notes:

| MIDI note | Approximate GM name | YM2413 sound |
| ---: | --- | --- |
| 36 | Bass Drum 1 | KICK |
| 38 | Acoustic Snare | SNARE |
| 42 / 44 | Closed / Pedal Hi-Hat | HAT |
| 43 / 47 / 50 | Floor / Mid / High Tom | TOM |
| 49 / 51 | Crash / Ride Cymbal | CYMBAL |

Multiple notes in one row trigger the same YM2413 drum and do not transpose it. Velocity controls the corresponding drum level. Cubase Drum Editor or pads assigned to the listed notes are the easiest way to play it.

### 5. VST2413S — user patch

Displayed values are generally YM2413 register values, not normalized 0.0-to-1.0 values. Values can also be typed into the text fields.

#### Common patch parameters

| Parameter | Range | Effect |
| --- | ---: | --- |
| Total Level (TL) | 0–63 | MODULATOR level. `0` gives the strongest modulation; `63` gives the weakest. Lower values are brighter and more complex, while higher values approach a rounder sine-like sound. |
| Feedback (FB) | 0–7 | MODULATOR self-feedback. Higher values add harmonics and roughness. |

Although TL appears in the common section, the register controls MODULATOR Total Level. It is not the plug-in output volume.

#### MODULATOR / CARRIER parameters

| Parameter | Range | Effect |
| --- | ---: | --- |
| Envelope Type (EG) | 0 / 1 | `0` suits decaying sounds; `1` suits sounds sustained while a key is held. |
| Multiple (MUL) | 0–15 | Operator frequency multiplier. The M/C combination strongly changes harmonic content. |
| Attack (AR) | 0–15 | Attack rate. `15` is fastest; very low values can make a note rise extremely slowly. |
| Decay (DR) | 0–15 | Rate from the attack peak toward SL. Higher values decay faster. |
| Sustain Level (SL) | 0–15 | Attenuation after decay. `0` is loudest and `15` is quietest. |
| Release (RR) | 0–15 | Rate after note-off. Higher values release faster. |
| Key Rate Scaling (KSR) | OFF / ON | Makes envelope rate depend on keyboard range. Use it for faster high notes. |
| Key Level Scaling (KSL) | 0–3 | Attenuates higher notes; larger values give a stronger effect. |
| Tremolo (AM) | OFF / ON | Enables amplitude movement from the chip LFO. |
| Vibrato (VIB) | OFF / ON | Enables pitch movement from the chip LFO. |
| Distortion | OFF / ON | Selects half-wave rectification through the DM/DC bits. It is not a conventional distortion effect. M and C are independent. |

MUL register values correspond to `1/2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 12, 12, 15, 15`.

#### Other controls

- **Fine Tune** adjusts global tuning from -50 to +50 cents.
- **Pitch Wheel Range** stores a range from 0 to 12 semitones, but MIDI pitch bend is not connected in the current VST3 port.

### 6. Creating a first sound

These values provide an audible starting point for exploring the controls. They are not an official YM2413 preset.

| Section | Settings |
| --- | --- |
| COMMON | TL `32`, FB `2` |
| MODULATOR | EG `1`, MUL `1`, AR `15`, DR `4`, SL `8`, RR `5` |
| CARRIER | EG `1`, MUL `1`, AR `15`, DR `4`, SL `4`, RR `5` |
| DETAIL | KSR OFF, KSL `0`, AM OFF, VIB OFF, DISTORTION OFF |
| OTHER | Fine Tune `0` |

Then work in this order:

1. Shape level with CARRIER AR / DR / SL / RR.
2. Lower TL to increase MODULATOR strength.
3. Change MODULATOR MUL to move the harmonics.
4. Raise FB to add hardness.
5. Add AM / VIB and, if desired, DISTORTION.

If no sound is produced, restore CARRIER AR to `15`, SL to `0`–`8`, and MUL to `1`. A high TL reduces modulation but does not mute the CARRIER itself.

### 7. Automation and saving

P and S parameters are available to Cubase automation. Select a parameter on a track automation lane, then write or draw its movement. Plug-in state is stored in the Cubase project and host presets.

Automating user-patch parameters changes every currently sounding VST2413S voice. Use separate plug-in instances when you need independent patches.

### 8. References

The explanations and tables in this guide were independently written from the plug-in implementation and YM2413 behavior. No third-party prose, diagram, or table is reproduced.

- Yamaha, *YM2413 OPLL Applications Manual*
- Mitsutaka Okazaki, `emu2413` (`source/emu2413/` in this repository)
