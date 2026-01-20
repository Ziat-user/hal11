#include "gamepad.h"
#define CONIOEX
#include "conioex.h"
#include <iostream>
#include <string>

#include "hew_console.h"
#include "Setting.h"

namespace ziat {
	void initGamepad(int& stickrx, int& stickry, int& sticklx, int& stickly, int& fps) {
		fps = 120;
		TARGET_RENDER_FPS = 60;

		stickrx = NX;
		stickry = NY;
		sticklx = NX;
		stickly = NY;
	}

	//falseでエラーを返す
	bool initConsole() {
		if (int start = hew_console_start(static_cast<int>(ConWindow::Auto)); start != 0) {
			std::cerr << "error:" << start;
			hew_console_restore();
			return false;
		}
		//カーソル非表示
		setcursortype(NOCURSOR);
		return true;
	}

	void setting_stick(int& stickrx, int& stickry, int& sticklx, int& stickly) {
		stickrx = inport(PJ_ZPOS);
		stickry = inport(PJ_RPOS);
		sticklx = inport(PJ_XPOS);
		stickly = inport(PJ_YPOS);
	}
}