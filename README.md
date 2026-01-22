# HEW（Console Game Framework / C++20）

Windows コンソール上で動作する、シーン管理＋入力＋描画をまとめた小規模ゲームフレームワークです。  
描画は `ScreenBuffer` を介して行い、チラつきを抑えつつ「一定フレームだけ表示するテキスト」も扱えます。

## 動作環境

- OS: Windows 10 / 11
- IDE: Visual Studio 2022
- 言語標準: C++20（最低でも C++17）
  - `Core/Setting.h` で `inline` 変数を使っているため、`/std:c++17` 以上が必要

## ビルド

1. `HEW.sln` を Visual Studio 2022 で開く
2. プロジェクトの __C++ 言語標準__ を **ISO C++20 (/std:c++20)** に設定  
   （__プロパティ > 構成プロパティ > C/C++ > 言語 > C++ 言語標準__）
3. __ビルド > ソリューションのビルド__
4. __デバッグ > デバッグの開始__

## 実行ループ（概要）

`Main.cpp` のメインループは概ね以下です。

- 60FPS 固定で `Update()` / `Draw()` を回す
- 毎フレーム `ScreenBuffer::Clear()` → `Draw()` → `ScreenBuffer::Show()`

## シーン

`IScene` を基底にして `Initialize / Update / Draw` を実装します。

### TitleScene
- タイトル表示 + 流れ星アニメーション（`Starfield`）
- Enter / PAD_RIGHT で Setting へ
- ESC / PAD_LEFT で終了
- デバッグ表示は `Ctrl+Shift+Alt`（`debug.cpp` の `getDebugkey()`）で切替

### SettingScene
- 描画FPS（`TARGET_RENDER_FPS`）のプルダウンUI
- Tab / ↑↓ でフォーカス移動、Enter / → で決定

### GameScene
- テスト用の画面
- スティック「はじき」検出でメッセージを一定時間表示

## 描画（ScreenBuffer）

`std::cout` へ直接出さず、`ScreenBuffer` を使って描画します。座標は **(1,1) が左上**。

### レイヤー構成
`ScreenBuffer` は2レイヤーです。

- **base**: 毎フレーム `Clear()` で全面消去される（通常描画はこちら）
- **overlay**: 指定フレームだけ残る描画用（`frames > 0` のときだけ使用）

`Show()` では **overlay が base より優先**されます（overlay が空白以外なら overlay が表示される）。

### Print の仕様


- `frames == 0`（省略）: base に描画（毎フレーム再描画する前提）
- `frames > 0` : overlay に描画し、指定フレーム経過で自動的に消える

例:
- 常時表示（毎フレーム描く用途）
  - `ScreenBuffer::Print(10, 5, "HELLO");`
- 60フレームだけ表示（Drawで1回描くだけでも残る）
  - `ScreenBuffer::Print(10, 6, "TEMP", 60);`

注意:
- overlay は base より前面に出るため、同じ座標付近にデバッグUI等があると見えづらくなる場合があります。

## アニメーション（Starfield）

`Core/Animation.*` の `Starfield` は、毎フレーム `ScreenBuffer::Print(..., frames=0)`（=base）で星と尾を描きます。  
base が毎フレームクリアされる設計のため、残像が汚くならずに表示されます。

## 入力

`IO/Input.*`

- ゲームパッド接続確認: `ziat::IsGamepadConnect()`
- ボタンのトリガー（押した瞬間）: `ziat::IsButtonTriggered()`
- キーボードのトリガー: `ziat::IsKeybordTrigger(VK_...)`
- スティック状態（ビットフラグ）: `ziat::getInportStick(...)`
- スティックの「はじき」: `ziat::IsStickFrickTriggered()`

`enum class STICKVECTOR` のフラグで方向を判定します。

## 主なファイル構成

- `Main.cpp` : エントリーポイント / 固定FPSループ / シーン遷移
- `IScene.h` : シーンインターフェース
- `Scenes/TitleScene.*` : タイトル + 流れ星表示
- `Scenes/SettingScene.*` : FPS設定UI（プルダウン）
- `Scenes/GameScene.*` : テスト画面
- `UI/ScreenBuffer.*` : base + overlay の2レイヤー描画、フレーム保持表示
- `UI/UI.*` : 枠/プルダウン等のUI描画
- `Core/Animation.*` : `Starfield`（流れ星）
- `IO/Input.*` : ゲームパッド/キーボード入力
- `UI/debug.*` : デバッグ表示（FPS/パッド状態など）
- `IO/conioex*` : コンソール操作（gotoxy 等）
- `Core/Setting.h` : グローバル設定値（`inline` 変数）

## ライセンス

Copyright 2025 Shiuta.


