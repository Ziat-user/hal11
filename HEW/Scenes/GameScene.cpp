#include "GameScene.h"
#include "gamepad.h"
#include "Input.h"
#include "Setting.h"
#include "ScreenBuffer.h" 
#include "debug.h"
#include "Map.h"

#define CONIOEX
#include "conioex.h"

void GameScene::Initialize() {
    ziat::InitializeMap();
    debug = false;
    kb_trigger_enter = false;
}

SceneName GameScene::Update() {
    kb_trigger_enter = ziat::IsKeybordTrigger(PK_ENTER);
	if ( kb_trigger_enter)return SceneName::Exit;
    if (ziat::getDebugkey()) debug = !debug;
	return SceneName::None;
}

void GameScene::Draw() {
    ScreenBuffer::Print(1, 1, u8"ÉQÅ[ÉÄâÊñ ÇæÇÊ");
    if (debug)ziat::showDebugBox(60, 19);
}

