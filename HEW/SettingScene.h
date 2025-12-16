#pragma once
#include "IScene.h"

class SettingScene : public IScene {
private:
    bool trigger = false;
    bool stick_s_check = false;
    int fps_c = 0;
public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};