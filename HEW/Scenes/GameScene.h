#pragma once
#include "IScene.h"

class GameScene : public IScene {
private:
    bool kb_trigger_enter = 0;
    bool debug = false;
public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};