#pragma once
#include "gamepad.h"

namespace ziat {
	// ボタンが押された瞬間かを判定する関数
	int IsButtonTriggered();
	// スティックはじきを判定する関数
	int IsStickFrickTriggered();
	//キーボード入力判定
	bool IsKeybordTrigger(int key);
	//ゲームパッド接続判定
	bool IsGamepadConnect();
}