#pragma once
#include "gamepad.h"

namespace ziat {
	// ボタンが押された瞬間かを判定する関数
	bool IsButtonTriggered(PadButton button);
	// スティックはじきを判定する関数
	int IsStickTriggered();
}