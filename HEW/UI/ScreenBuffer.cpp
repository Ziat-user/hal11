#define NOMINMAX
#include "ScreenBuffer.h"
#include <iostream>
#include <cstring>
#include <cstddef>

#define CONIOEX
#include "conioex.h"

char ScreenBuffer::base[ScreenBuffer::HEIGHT][ScreenBuffer::WIDTH + 1];
char ScreenBuffer::overlay[ScreenBuffer::HEIGHT][ScreenBuffer::WIDTH + 1];
unsigned short ScreenBuffer::ttl[ScreenBuffer::HEIGHT][ScreenBuffer::WIDTH];

void ScreenBuffer::Initialize() {
	for (int y = 0; y < HEIGHT; ++y) {
		std::memset(base[y], ' ', WIDTH);
		base[y][WIDTH] = '\0';

		std::memset(overlay[y], ' ', WIDTH);
		overlay[y][WIDTH] = '\0';

		for (int x = 0; x < WIDTH; ++x) {
			ttl[y][x] = 0;
		}
	}
}

void ScreenBuffer::Clear() {
	// base は従来通り毎フレーム全面消去（流れ星などが綺麗に描ける）
	for (int y = 0; y < HEIGHT; ++y) {
		std::memset(base[y], ' ', WIDTH);
		base[y][WIDTH] = '\0';
	}

	// overlay は ttl を減らして、切れたセルだけ消す
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (ttl[y][x] > 0) {
				--ttl[y][x];
				if (ttl[y][x] == 0) {
					overlay[y][x] = ' ';
				}
			}
		}
		overlay[y][WIDTH] = '\0';
	}
}

void ScreenBuffer::Print(int x, int y, const std::string& text, int frames) {
	int px = x - 1;
	int py = y - 1;

	if (py < 0 || py >= HEIGHT) return;
	if (px >= WIDTH) return;
	if (px < 0) px = 0;

	const bool useOverlay = (frames > 0);
	const unsigned short f = useOverlay ? static_cast<unsigned short>(frames) : 0;

	for (std::size_t i = 0; i < text.size(); ++i) {
		const int cx = px + static_cast<int>(i);
		if (cx < 0) continue;
		if (cx >= WIDTH) break;

		if (useOverlay) {
			overlay[py][cx] = text[i];
			ttl[py][cx] = f;
		}
		else {
			base[py][cx] = text[i];
		}
	}
}

void ScreenBuffer::Show() {
	gotoxy(1, 1);

	std::string output;
	output.reserve(WIDTH * HEIGHT + HEIGHT);

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			const char c = (overlay[y][x] != ' ') ? overlay[y][x] : base[y][x];
			output.push_back(c);
		}
		if (y < HEIGHT - 1) output.push_back('\n');
	}

	std::cout << output;
}