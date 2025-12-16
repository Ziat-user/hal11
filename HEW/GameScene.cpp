#include "GameScene.h"
#include "gamepad.h"
#include "Game.h"
#include "Setting.h"
#include "ScreenBuffer.h" 

void GameScene::Initialize() {
	comment_l_timer = 0;
    comment_r_timer = 0;
}

SceneName GameScene::Update() {
	if (ziat::IsButtonTriggered(PadButton::PAD_LEFT))return SceneName::Exit;
    short int trigger = ziat::IsStickTriggered();
    if (trigger & 0b10) comment_l_timer = (TARGET_FPS > 0) ? TARGET_FPS : 60;
    if (trigger & 0b01) comment_r_timer = (TARGET_FPS > 0) ? TARGET_FPS : 60;
    if (comment_l_timer > 0) comment_l_timer--;
    if (comment_r_timer > 0) comment_r_timer--;
	return SceneName::None;
}

void GameScene::Draw() {
    ScreenBuffer::Print(1, 1, "ゲーム画面だよ");
    if (comment_l_timer > 0) ScreenBuffer::Print(1, 2, "左スティックが反応しました！");
    if (comment_r_timer > 0) ScreenBuffer::Print(1, 3, "右スティックが反応しました！");
}