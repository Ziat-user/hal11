#pragma once
#include <string>

class ScreenBuffer {
public:
	static void Initialize();
	static void Clear();
	static void Print(int x, int y, const std::string& text);
	static void Show();

private:
	static const int WIDTH = 80;
	static const int HEIGHT = 25;
	static char buffer[HEIGHT][WIDTH + 1];
};