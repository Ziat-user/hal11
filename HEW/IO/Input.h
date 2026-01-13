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
	//bitで管理　1の位から左sl 左sr 左su 左sd 右sl 右sr 右su 右sd
	int getInportStick(int nowx, int nowy, int nouz, int nowr);
	//EQUAL:同値、GREATER:大なり、SMALLER:小なり
	bool trigger(int prev_state, int now_state, int trigger_state, triggermode mode);
	
	
}