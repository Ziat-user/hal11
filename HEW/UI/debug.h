#pragma once
namespace ziat {
	bool getDebugkey();

	void showFPS(int x, int y); //xで横、yで縦を指定

	void showGamepadstick(int x, int y); //xで横、yで縦を指定 4行使う
	void showGamepadbtns(int x, int y);

	void showDebugBox(int x, int y);
}