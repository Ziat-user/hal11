#include "Animation.h"
#include "ScreenBuffer.h"

#include <algorithm>
#include <string>

Starfield::Starfield(int width, int height)
	: width_(width), height_(height) {
}

void Starfield::Reset() {
	stars_.clear();
	frameCounter_ = 0;
	rng_ = 0x12345678;
}

void Starfield::SetSpawnIntervalFrames(int frames) {
	spawnIntervalFrames_ = (frames > 0) ? frames : 1;
}

void Starfield::SetMaxStars(int maxStars) {
	maxStars_ = (maxStars > 0) ? maxStars : 1;
}

void Starfield::SetTailLength(int len) {
	tailLength_ = (len > 0) ? len : 1;
}

void Starfield::Tick() {
	++frameCounter_;

	// 星の更新（右下へ移動、寿命減少）
	for (auto& s : stars_) {
		s.x += 1;
		s.y += 1;
		s.life -= 1;
	}

	// 画面外/寿命切れを削除
	stars_.erase(
		std::remove_if(stars_.begin(), stars_.end(),
			[this](const Star& s) {
				return s.life <= 0 || s.x < 0 || s.y < 0 || s.x >= width_ || s.y >= height_;
			}),
		stars_.end()
	);

	// 一定間隔で生成（数も制限）
	if (frameCounter_ % spawnIntervalFrames_ == 0) {
		if (static_cast<int>(stars_.size()) < maxStars_) {
			Spawn();
		}
	}
}

void Starfield::Spawn() {
	// xorshift（軽量）
	rng_ ^= rng_ << 13;
	rng_ ^= rng_ >> 17;
	rng_ ^= rng_ << 5;

	// 上端～少し上から出す（斜めに入ってくる感じ）
	const int x = static_cast<int>(rng_ % (width_ > 0 ? width_ : 1));
	const int y = 0;

	stars_.push_back(Star{ x, y, tailLength_ });
}

void Starfield::Draw(int originX, int originY) const {
	// 尾：斜め左上方向へ薄く描画
	for (const auto& s : stars_) {
		for (int t = 0; t < tailLength_; ++t) {
			const int px = s.x - t;
			const int py = s.y - t;
			if (px < 0 || py < 0 || px >= width_ || py >= height_) continue;

			char c = '.';
			if (t == 0) c = '*';             // 先頭
			else if (t <= 2) c = '+';        // 少し明るい尾
			else c = '.';                    // 薄い尾

			ScreenBuffer::Print(originX + px + 1, originY + py + 1, std::string(1, c));
		}
	}
}