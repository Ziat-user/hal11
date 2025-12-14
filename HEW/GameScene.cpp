#include <iostream>

#define CONIOEX
#include "conioex.h"

#include "GameScene.h"
#include "gamepad.h"
#include "Game.h"

void GameScene::Initialize() {
	clrscr();
}

SceneName GameScene::Update() {
	if (ziat::IsButtonTriggered(PadButton::PAD_LEFT))return SceneName::Exit;
	else return SceneName::None;
}

void GameScene::Draw() {
	gotoxy(1, 1); // •`‰æˆÊ’u‚ğæ“ª‚É
	clrscr();
	std::cout << "ƒQ[ƒ€‰æ–Ê‚¾‚æ";
}