#pragma once
#include "gamepad.h"

namespace ziat {
	enum class triggermode {
		EQUAL, GREATER, SMALLER
	};
	// ボタンが押された瞬間かを判定する関数
	int IsButtonTriggered();
	// スティックはじきを判定する関数
	int IsStickFrickTriggered();
	//キーボード入力判定
	bool IsKeybordTrigger(int key);
	//ゲームパッド接続判定
	bool IsGamepadConnect();
	// 
	void getInportGamepad(int& a, int& b, int& c, int& d);
	//bitで管理　1の位から左sr 左sl 左sd 左su 右sr 右sl 右sd 右su
	int getInportStick(int nowx, int nowy, int nouz, int nowr);

	enum class StickVector {
		LsRIGHT = 0b00000001,
		LsLEFT  = 0b00000010,
		LsDOWN  = 0b00000100,
		LsUP    = 0b00001000,
		RsRIGHT = 0b00010000,
		RsLEFT  = 0b00100000,
		RsUP    = 0b01000000,
		RsDOWN  = 0b10000000
	};

	//EQUAL:同値、GREATER:大なり、SMALLER:小なり
	bool trigger(int prev_state, int now_state, int trigger_state, triggermode mode);
	
}