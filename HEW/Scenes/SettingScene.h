#pragma once
#include "IScene.h"
#include <chrono>

class SettingScene : public IScene {
private:
    int bt_trigger = 0;
    bool stick_s_check = false;
    bool kb_trigger_enter = false;
    bool gp_connect = false;
    bool debug = false;

    // プルダウン(FPS)
    bool fpsPulldownOpen = false;
    int fpsSelectedIndex = 0;

    // 追加：UIフォーカス
    enum class Focus {
        Pulldown,
        DecideButton,
    };
    Focus focus = Focus::Pulldown;

public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};