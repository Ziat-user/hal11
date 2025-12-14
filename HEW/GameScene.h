#pragma once
#include "IScene.h"

class GameScene : public IScene {
public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};