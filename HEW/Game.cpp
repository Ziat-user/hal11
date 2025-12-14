#define CONIOEX
#include <cmath>
#include "conioex.h"
#include "gamepad.h"
#include "setting.h"

namespace ziat {
	bool IsButtonTriggered(PadButton button) {
		static unsigned char prev_state = 0;
		unsigned char current_padbtn_state = inport(PJ_BTNS);
		unsigned char button_flag = static_cast<unsigned char>(button);
		bool r = (current_padbtn_state & button_flag) && !(prev_state & button_flag);
		prev_state = current_padbtn_state;
		return r;
	}

	int IsStickTriggered() {
		static long long prev_r_dis = 0;
		static long long prev_l_dis = 0;
		int i = 0b00;
		int rxstick = (int)inport(PJ_XPOS) - NEUTRAL_STICK_R_X;
		int rystick = (int)inport(PJ_YPOS) - NEUTRAL_STICK_R_Y;
		int lxstick = (int)inport(PJ_ZPOS) - NEUTRAL_STICK_L_X;
		int lystick = (int)inport(PJ_RPOS) - NEUTRAL_STICK_L_Y;
		long long r_dis = 1LL * rxstick * rxstick + 1LL * rystick * rystick;
		long long l_dis = 1LL * lxstick * lxstick + 1LL * lystick * lystick;
		if (prev_r_dis > FZSQ && r_dis < NZSQ)i |= 0b01;
		if (prev_l_dis > FZSQ && l_dis < NZSQ)i |= 0b10;
		prev_r_dis = r_dis;
		prev_l_dis = l_dis;
		return i;
	}
}