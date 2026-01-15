#include "gamepad.h"
#include "Input.h"
#include "Game.h"
#include "Map.h"

namespace ziat {
	//キャラクターのビジュアルとか？
	void characterInitialize() {

	}
	
	//とりあえずy方向が二次関数的に動く
	ziat::Character characterJump(int strong) {
		using namespace ziat;
		static Character character_state;
		character_state.nowjump = false;
		static int high;
		static int prev_x_pos, prev_y_pos;
		if (!character_state.nowjump) {
			character_state.nowjump = true;
			high = strong;
		}
		else if (character_state.nowjump) {

		}

	}
}