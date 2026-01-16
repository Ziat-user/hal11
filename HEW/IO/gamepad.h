#pragma once
#include <vector>
#include <string>

enum class PadButton : int {
	PAD_LEFT = 1,
	PAD_UP = 2,
	PAD_DOWN = 4,
	PAD_RIGHT = 8,
	PAD_L_BUMPER = 16,
	PAD_R_BUMPER = 32,
	PAD_L_TRIGGER = 64,
	PAD_R_TRIGGER = 128,
	PAD_LS_PRESS = 256,
	PAD_RS_PRESS = 512,
	PAD_BACK = 1024,
	PAD_START = 2048,
	PAD_GUIDE = 4096,
};

enum class rightleft {
	LEFT,RIGHT
};

// ボタンのビット値と表示名を関連付ける構造体
struct ButtonMapping {
	PadButton button;
	std::string name;
};

// 判定したいボタンのリストをインライン関数で提供
// staticローカル変数として定義することで、初回呼び出し時に一度だけ初期化されます。
inline const std::vector<ButtonMapping>& getButtonMappings() {
	static const std::vector<ButtonMapping> buttonMappings = {
		{ PadButton::PAD_LEFT, "R←ボタン" },
		{ PadButton::PAD_DOWN, "R↓ボタン" },
		{ PadButton::PAD_RIGHT, "R→ボタン" },
		{ PadButton::PAD_UP, "R↑ボタン" },
		{ PadButton::PAD_L_BUMPER, "L Bumper" },
		{ PadButton::PAD_R_BUMPER, "R Bumper" },
		{ PadButton::PAD_L_TRIGGER, "L Trigger" },
		{ PadButton::PAD_R_TRIGGER, "R Trigger" },
		{ PadButton::PAD_LS_PRESS, "LS press" },
		{ PadButton::PAD_RS_PRESS, "RS Press" },
		{ PadButton::PAD_BACK, "BACK" },
		{ PadButton::PAD_START, "START" },
		{ PadButton::PAD_GUIDE, "GUIDE" },
	};
	return buttonMappings;
}

inline constexpr int NX = 32767;
inline constexpr int NY = 32511;//自分のコントローラーのニュートラル値

inline constexpr int NZONE = 5000;
inline constexpr int FZONE = 13000;//フリック入力用
inline constexpr long long NZSQ = 1LL * NZONE * NZONE;
inline constexpr long long FZSQ = 1LL * FZONE * FZONE;