#pragma once
#include <string>

class ScreenBuffer {
public:
	static void Initialize();
	static void Clear();
	static void Print(int x, int y, const std::string& text, int frames = 0);
	static void Show();

private:
	static const int WIDTH = 80;
	static const int HEIGHT = 25;

	// 毎フレーム描き直すレイヤー（従来通り Clear で全面消去）
	static char base[HEIGHT][WIDTH + 1];

	// 寿命付きレイヤー（frames>0 のみ。Clearでttlを減らして消す）
	static char overlay[HEIGHT][WIDTH + 1];
	static unsigned short ttl[HEIGHT][WIDTH];
};