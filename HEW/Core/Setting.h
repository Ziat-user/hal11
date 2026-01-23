#pragma once

inline int TARGET_FPS;
inline int TARGET_RENDER_FPS;
inline int NEUTRAL_STICK_R_X, NEUTRAL_STICK_R_Y, NEUTRAL_STICK_L_X, NEUTRAL_STICK_L_Y;


enum class ConWindow {
	Auto = -1,
	PRIMARY = 0,
	SUB_A = 1,
};

namespace ziat {
	void initGamepad(int& stickrx, int& stickry, int& sticklx, int& stickly, int& fps);
	void setting_stick(int& stickrx, int& stickry, int& sticklx, int& stickly);
	bool initConsole(bool on = 1);
}