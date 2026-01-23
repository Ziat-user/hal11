#pragma once
#include <vector>

namespace ziat {

	enum class Groundtype {
		AIR,
		NORMAL, // 地面扱いにする予定のタイル
		THORN,
	};

	struct Tile {
		char glyph;        // 表示用（任意）
		Groundtype ground; // タグ
	};

	inline const std::vector<Tile> block = {
		{' ',Groundtype::AIR},
		{'=',Groundtype::NORMAL},
		{'*',Groundtype::THORN},
	};

	inline constexpr int MAP_WIDTH = 80;
	inline constexpr int MAP_HEIGHT = 25;

	// 2次元タイルマップ（[y][x]）
	extern std::vector<std::vector<Tile>> map;

	// 初期化（空気で埋める/床を作る等）
	void InitializeMap();
	bool IsGroundAt(int x, int y);
}