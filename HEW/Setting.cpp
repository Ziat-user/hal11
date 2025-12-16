#include "gamepad.h"
#define CONIOEX
#include "conioex.h"
#include <iostream>
#include <string>

namespace ziat {
	void initialize(int& stickrx, int& stickry, int& sticklx, int& stickly, int& fps) {
		fps = 30;
		stickrx = NX;
		stickry = NY;
		sticklx = NX;
		stickly = NY;
	}

	void setting_stick(int& stickrx, int& stickry, int& sticklx, int& stickly) {
		stickrx = inport(PJ_ZPOS);
		stickry = inport(PJ_RPOS);
		sticklx = inport(PJ_XPOS);
		stickly = inport(PJ_YPOS);
	}
}