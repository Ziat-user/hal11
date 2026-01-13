#define CONIOEX
#include <cmath>
#include "conioex.h"
#include "gamepad.h"
#include "setting.h"

namespace ziat {
	int IsButtonTriggered() {
		static int prev_state = 0;
		int current_padbtn_state = inport(PJ_BTNS);
		if (current_padbtn_state == -1) {
			current_padbtn_state = 0;
		}

		int r = current_padbtn_state & ~prev_state;
		prev_state = current_padbtn_state;
		return r;
	}

	int IsStickFrickTriggered() {
		static long long prev_r_dis = 0;
		static long long prev_l_dis = 0;
		int i = 0b00;
		int rxstick = (int)inport(PJ_ZPOS) - NEUTRAL_STICK_R_X;
		int rystick = (int)inport(PJ_RPOS) - NEUTRAL_STICK_R_Y;
		int lxstick = (int)inport(PJ_XPOS) - NEUTRAL_STICK_L_X;
		int lystick = (int)inport(PJ_YPOS) - NEUTRAL_STICK_L_Y;
		long long r_dis = 1LL * rxstick * rxstick + 1LL * rystick * rystick;
		long long l_dis = 1LL * lxstick * lxstick + 1LL * lystick * lystick;
		if (prev_r_dis > FZSQ && r_dis < NZSQ)i |= 0b01;
		if (prev_l_dis > FZSQ && l_dis < NZSQ)i |= 0b10;
		prev_r_dis = r_dis;
		prev_l_dis = l_dis;
		return i;
	}

	bool IsKeybordTrigger(int key) {
		// Virtual-Key ÇÕí èÌ 0..255
		if (key < 0 || key > 0xFF) return false;

		static unsigned char prev_state[256] = {}; // ÉLÅ[Ç≤Ç∆Ç…ï€éù
		const int current = inport(key) ? 1 : 0;

		const bool triggered = (current != 0) && (prev_state[key] == 0);
		prev_state[key] = static_cast<unsigned char>(current);
		return triggered;
	}

	bool IsGamepadConnect() { 
		return (inport(PJ_BTNS) != -1); 
	}

	void getInportGamepad(int& a, int& b, int& c, int& d) {
		a = inport(PJ_XPOS);
		b = inport(PJ_YPOS);
		c = inport(PJ_ZPOS);
		d = inport(PJ_RPOS);
	}

}