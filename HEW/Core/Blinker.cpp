#include "Blinker.h"

Blinker::Blinker(int intervalFrames)
	: intervalFrames_(intervalFrames > 0 ? intervalFrames : 1),
	frame_(0),
	on_(true) {
}

void Blinker::Reset() {
	frame_ = 0;
	on_ = true;
}

void Blinker::Tick() {
	++frame_;
	if (frame_ >= intervalFrames_) {
		frame_ = 0;
		on_ = !on_;
	}
}

bool Blinker::IsOn() const {
	return on_;
}