#include "ScreenBuffer.h"
#include <iostream>
#include <cstring>
#include <cstddef>

#define CONIOEX
#include "conioex.h"

char ScreenBuffer::buffer[ScreenBuffer::HEIGHT][ScreenBuffer::WIDTH + 1];

void ScreenBuffer::Initialize() {
	Clear();
}

void ScreenBuffer::Clear() {
	for (int y = 0; y < HEIGHT; ++y) {
		std::memset(buffer[y], ' ', WIDTH);
		buffer[y][WIDTH] = '\0';
	}
}

void ScreenBuffer::Print(int x, int y, const std::string& text) {
    int px = x - 1;
    int py = y - 1;

    if (py < 0 || py >= HEIGHT) return;
    if (px >= WIDTH) return;          // 右に完全にはみ出し
    if (px < 0) px = 0;               // 左は 0 に丸め（簡易）

    std::size_t start = static_cast<std::size_t>(px);
    for (std::size_t i = 0; i < text.size() && start + i < WIDTH; ++i) {
        buffer[py][start + i] = text[i];
    }
}

void ScreenBuffer::Show() {
    gotoxy(1, 1);

    // バッファの内容を一気に出力
    // 最後の行以外は改行を入れるなどの調整が可能ですが、
    // ここでは単純に全行を出力します。
    std::string output;
    output.reserve(WIDTH * HEIGHT + HEIGHT); // メモリ確保

    for (int y = 0; y < HEIGHT; ++y) {
        output += buffer[y];
        if (y < HEIGHT - 1) {
            output += "\n";
        }
    }
    // 一回のcoutで出力することでチラつきを抑える
    std::cout << output;
}