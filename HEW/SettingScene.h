#pragma once
#include "IScene.h"

class SettingScene : public IScene {
private:
    bool trigger = false;
    bool stick_s_check = false;
public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};