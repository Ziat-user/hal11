#pragma once
#include "IScene.h"

class GameScene : public IScene {
private:
    short int st_trigger = 0;
    int bt_trigger = 0;
    int comment_l_timer = 0;
    int comment_r_timer = 0;
    bool kb_trigger_enter = 0;
public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};