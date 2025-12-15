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
    if (ziat::IsStickTriggered() & 0b01) {
        comment_timer = (TARGET_FPS > 0) ? TARGET_FPS : 60;
    }
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