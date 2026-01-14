#include "TitleScene.h"

#include "Input.h"
#include "ScreenBuffer.h"
#include "debug.h"

#define CONIOEX
#include "conioex.h"

#include "UI.h"

void TitleScene::Initialize() {
    bt_trigger = 0;
    kb_trigger_enter = false;
    kb_trigger_esc = false;
    debug = 0;

    pressBlink.Reset();

    starfield.Reset();
    starfield.SetSpawnIntervalFrames(6); // 出現頻度（小さいほど多い）
    starfield.SetMaxStars(10);           // 同時表示数
    starfield.SetTailLength(7);          // 尾の長さ
}

SceneName TitleScene::Update() {
    pressBlink.Tick();
    starfield.Tick();
    ziat::getInportGamepad(sticklx,stickly,stickrx,stickry);
    st_trigger = ziat::getInportStick(sticklx, stickly, stickrx, stickry);
    bt_trigger = ziat::IsButtonTriggered();
    kb_trigger_enter = ziat::IsKeybordTrigger(PK_ENTER);
    kb_trigger_esc = ziat::IsKeybordTrigger(PK_ESC);

    const bool start = kb_trigger_enter || ((bt_trigger & static_cast<int>(PadButton::PAD_RIGHT)) != 0);
    const bool exit = kb_trigger_esc || ((bt_trigger & static_cast<int>(PadButton::PAD_LEFT)) != 0);

    if (exit) return SceneName::Exit;
    if (start) return SceneName::Setting;
    if (ziat::getDebugkey()) debug = !debug;
    return SceneName::None;
}

void TitleScene::Draw() {
    starfield.Draw();

    ziat::create_square(10, 6, 60, 12, '=', '|', '+');

    ScreenBuffer::Print(25, 8, "HEW - TITLE (TEST)");
    ScreenBuffer::Print(16, 10, "ENTER / PAD_RIGHT : START");
    ScreenBuffer::Print(16, 11, "ESC   / PAD_LEFT  : EXIT");
    ScreenBuffer::Print(16, 13, "This is a simple test title scene.");

    if (pressBlink.IsOn()) {
        ScreenBuffer::Print(23, 15, ">>> PRESS ENTER <<<");
    }
    if (st_trigger & static_cast<int>(ziat::STICKVECTOR::LsDOWN)) ScreenBuffer::Print(23, 17, "leftstick");
    if (debug) ziat::showDebugBox(60, 19);
}