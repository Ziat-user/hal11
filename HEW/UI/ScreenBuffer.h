#pragma once
#include <string>
#include <string_view>

class ScreenBuffer {
public:
	static void Initialize();
	static void Clear();

	static void Print(int x, int y, const std::string& text, int frames = 0);
	static void Print(int x, int y, std::u8string_view text, int frames = 0); // ’Ç‰Á

	static void Show();

private:
	static const int WIDTH = 80;
	static const int HEIGHT = 25;

	static wchar_t base[HEIGHT][WIDTH + 1];
	static wchar_t overlay[HEIGHT][WIDTH + 1];
	static unsigned short ttl[HEIGHT][WIDTH];
};