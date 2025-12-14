#include "GameScene.h"
#include "gamepad.h"
#include "Game.h"
#include "Setting.h"
#include "ScreenBuffer.h" 

void GameScene::Initialize() {
	comment_timer = 0;
}

SceneName GameScene::Update() {
	if (ziat::IsButtonTriggered(PadButton::PAD_LEFT))return SceneName::Exit;
    // 右スティックのトリガー判定 (ビット0が立っているか確認)
    // IsStickTriggeredは呼び出すたびに内部状態(prev_dis)を更新するため、
    // 1フレームに1回だけ呼び出すのが適切です。
    if (ziat::IsStickTriggered() & 0b01) {
        // 1秒間表示するためのタイマーを設定
        // TARGET_FPSが未設定(0)の場合は安全策として60フレームを設定
        comment_timer = (TARGET_FPS > 0) ? TARGET_FPS : 60;
    }

    // タイマーが残っていれば減らす
    if (comment_timer > 0) {
        comment_timer--;
    }
	return SceneName::None;
}

void GameScene::Draw() {
    ScreenBuffer::Print(1, 1, "ゲーム画面だよ");

    if (comment_timer > 0) {
        ScreenBuffer::Print(1, 2, "右スティックが反応しました！");
    }
}