#pragma once
#include <string>
namespace ziat {
	struct Character {
		int posx,posy;
		bool nowjump;

	};

	ziat::Character characterJump(int strong, int gravity = 1);
}
