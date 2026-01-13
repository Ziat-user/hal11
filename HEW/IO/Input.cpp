#define CONIOEX
#include <cmath>
#include <iostream>
#include "Input.h"
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
		// Virtual-Key は通常 0..255
		if (key < 0 || key > 0xFF) return false;

		static unsigned char prev_state[256] = {}; // キーごとに保持
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

	
	int getInportStick(int nowx,int nowy,int nowz,int nowr) {
		static int prev_x, prev_y, prev_z, prev_r;
		int r = 0;
		if (trigger(prev_x, nowx, 65535, triggermode::EQUAL)) r |= 0b00000001;
		if (trigger(prev_x, nowx, 0,     triggermode::EQUAL)) r |= 0b00000010;
		if (trigger(prev_y, nowy, 65535, triggermode::EQUAL)) r |= 0b00000100;
		if (trigger(prev_y, nowy, 0,     triggermode::EQUAL)) r |= 0b00001000;
		if (trigger(prev_z, nowz, 65535, triggermode::EQUAL)) r |= 0b00010000;
		if (trigger(prev_z, nowz, 0,     triggermode::EQUAL)) r |= 0b00100000;
		if (trigger(prev_r, nowr, 65535, triggermode::EQUAL)) r |= 0b01000000;
		if (trigger(prev_r, nowr, 0,     triggermode::EQUAL)) r |= 0b10000000;
		return r;
	}

	// prev_state:1f前, now_state,現在, trigger_state:トリガーとなる値 mode:EQUAL,GREATER,SMALLER
	bool trigger(int prev_state, int now_state, int trigger_state,triggermode mode) {
		if (mode == triggermode::EQUAL)
			return prev_state != trigger_state && now_state == trigger_state;
		if (mode == triggermode::GREATER)
			return prev_state < trigger_state && now_state >= trigger_state;
		if (mode == triggermode::SMALLER)
			return prev_state > trigger_state && now_state <= trigger_state;
		std::cerr << "trigger get error";
		return 0;
	}
}