#include "GameScene.h"
#include "gamepad.h"
#include "Input.h"
#include "Setting.h"
#include "ScreenBuffer.h" 
#include "debug.h"

#define CONIOEX
#include "conioex.h"

void GameScene::Initialize() {
    debug = false;
    st_trigger = 0;
    bt_trigger = 0;
	comment_l_timer = 0;
    comment_r_timer = 0;
    kb_trigger_enter = false;
}

SceneName GameScene::Update() {
    bt_trigger = ziat::IsButtonTriggered();
    st_trigger = ziat::IsStickFrickTriggered();
    kb_trigger_enter = ziat::IsKeybordTrigger(PK_ENTER);
	if (((bt_trigger & static_cast<int>(PadButton::PAD_LEFT)) != 0) || kb_trigger_enter)return SceneName::Exit;
    if (ziat::getDebugkey()) debug = !debug;
	return SceneName::None;
}

void GameScene::Draw() {
    ScreenBuffer::Print(1, 1, "ゲーム画面だよ");
    if (st_trigger & 0b10) ScreenBuffer::Print(1, 2, "左スティックが反応しました！",60);
    if (st_trigger & 0b01) ScreenBuffer::Print(1, 3, "右スティックが反応しました！",60);
    if (debug)ziat::showDebugBox(60, 19);
}