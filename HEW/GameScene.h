#pragma once
#include "IScene.h"

class GameScene : public IScene {
private:
    int comment_timer = 0;
public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};