#pragma once
#include <vector>

namespace ziat {

	enum class Groundtype {
		Air,
		normal, // 地面扱いにする予定のタイル
	};

	struct Tile {
		char glyph = ' ';                 // 表示用（任意）
		Groundtype ground = Groundtype::Air; // タグ
	};

	inline constexpr int MAP_WIDTH = 80;
	inline constexpr int MAP_HEIGHT = 25;

	// 2次元タイルマップ（[y][x]）
	extern std::vector<std::vector<Tile>> map;

	// 初期化（空気で埋める/床を作る等）
	void InitializeMap();
	bool IsGroundAt(int x, int y);
}