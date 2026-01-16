#include "Map.h"

namespace ziat {

	std::vector<std::vector<Tile>> map;

	void InitializeMap() {
		// map[y][x] でアクセスできるように確保
		map.assign(MAP_HEIGHT, std::vector<Tile>(MAP_WIDTH));

		// 全部Airで初期化（glyphも空白）
		for (int y = 0; y < MAP_HEIGHT; ++y) {
			for (int x = 0; x < MAP_WIDTH; ++x) {
				map[y][x].ground = Groundtype::Air;
				map[y][x].glyph = ' ';
			}
		}

		// 仮：一番下の行を地面(normal)にする
		const int groundY = MAP_HEIGHT - 1;
		for (int x = 0; x < MAP_WIDTH; ++x) {
			map[groundY][x].ground = Groundtype::normal;
			map[groundY][x].glyph = '=';
		}
	}

	bool IsGroundAt(int x, int y) {
		if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH) return false;
		return map[y][x].ground == Groundtype::normal;
	}

}