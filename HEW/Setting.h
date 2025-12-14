#pragma once

inline int TARGET_FPS;
inline int NEUTRAL_STICK_R_X, NEUTRAL_STICK_R_Y, NEUTRAL_STICK_L_X, NEUTRAL_STICK_L_Y;

namespace ziat {
	void initialize(int* stickrx, int* stickry, int* sticklx, int* stickly, int* fps);
	void setting_stick(int* stickrx, int* stickry, int* sticklx, int* stickly);
}