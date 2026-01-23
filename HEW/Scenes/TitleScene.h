#pragma once
#include "IScene.h"
#include "Blinker.h"
#include "Animation.h"

class TitleScene : public IScene {
private:
    bool kb_trigger_enter = false;
    bool kb_trigger_esc = false;
    bool debug = false;
    Blinker pressBlink{ 30 };
    Starfield starfield{ 80, 25 };

public:
    void Initialize() override;
    SceneName Update() override;
    void Draw() override;
};