#pragma once
#include <cstdint>

class Blinker {
public:
	// intervalFrames: 何フレームごとに ON/OFF を反転するか
	explicit Blinker(int intervalFrames = 30);

	void Reset();
	void Tick();          // 1フレーム進める
	bool IsOn() const;    // 現在ONか

private:
	int intervalFrames_;
	int frame_;
	bool on_;
};