#pragma once
#include "IScene.h"
#include <chrono>

class SettingScene : public IScene {
private:
    int bt_trigger = 0;
    int st_trigger = 0;
    int sticklx, stickly, stickrx, stickry;
    bool stick_s_check = false;
    bool kb_trigger_enter = false;
    bool gp_connect = false;
    bool debug = false;

    // ƒvƒ‹ƒ_ƒEƒ“(FPS)
    bool fpsPulldownOpen = false;
    int fpsSelectedIndex = 0;

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