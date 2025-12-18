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

public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};