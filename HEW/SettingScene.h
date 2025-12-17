#pragma once
#include "IScene.h"
#include <chrono>

class SettingScene : public IScene {
private:
    bool bt_trigger = false;
    bool stick_s_check = false;
    bool kb_trigger_enter = false;
    bool gp_connect = false;

    // FPSŒv‘ª—p
    std::chrono::steady_clock::time_point last_check_time;
    int frames_in_interval = 0;
    double current_fps = 0.0;

public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};