#pragma once
#include <vector>
#include <cstdint>

class Starfield {
public:
	Starfield(int width, int height);

	void Reset();
	void Tick(); // 1フレーム進める
	void Draw(int originX = 0, int originY = 0) const; // ScreenBufferへ描画（座標オフセット）

	// 設定
	void SetSpawnIntervalFrames(int frames); // 何フレームごとに星を出すか
	void SetMaxStars(int maxStars);
	void SetTailLength(int len);

private:
	struct Star {
		int x;
		int y;
		int life; // 残り寿命（尾の長さにも利用）
	};

	void Spawn();

	int width_;
	int height_;

	int spawnIntervalFrames_ = 10;
	int maxStars_ = 12;
	int tailLength_ = 6;

	int frameCounter_ = 0;
	std::uint32_t rng_ = 0x12345678;

	std::vector<Star> stars_;
};