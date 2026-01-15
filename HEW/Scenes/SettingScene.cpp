#include "gamepad.h"
#include "setting.h"
#include "Input.h"
#include "ScreenBuffer.h"
#define CONIOEX
#include "conioex.h"
#include "UI.h"
#include "debug.h"

#include "SettingScene.h"

#include <vector>
#include <string>

static const std::vector<std::string> kRenderFpsChoices = {
    "30", "60", "90", "120", "144", "165", "240"
};

static int clamp_index(int i, int n) {
    if (n <= 0) return 0;
    if (i < 0) return 0;
    if (i >= n) return n - 1;
    return i;
}

static int choice_to_fps(const std::string& s) {
    return std::stoi(s);
}

void SettingScene::Initialize() {
    if (ziat::IsGamepadConnect()) gp_connect = true;
    else gp_connect = false;

    bt_trigger = 0;
    kb_trigger_enter = 0;
    stick_s_check = false;
    debug = 0;

    if (TARGET_RENDER_FPS <= 0) TARGET_RENDER_FPS = 120;

    fpsPulldownOpen = false;
    fpsSelectedIndex = 0;
    for (int i = 0; i < static_cast<int>(kRenderFpsChoices.size()); ++i) {
        if (choice_to_fps(kRenderFpsChoices[i]) == TARGET_RENDER_FPS) {
            fpsSelectedIndex = i;
            break;
        }
    }
    focus = Focus::Pulldown;
}

SceneName SettingScene::Update() {

    bt_trigger = ziat::IsButtonTriggered();
    kb_trigger_enter = ziat::IsKeybordTrigger(PK_ENTER);
    ziat::getInportGamepad(sticklx, stickly, stickrx, stickry);
    st_trigger = ziat::getInportStick(sticklx, stickly, stickrx, stickry);
    const bool keyUp = ziat::IsKeybordTrigger(PK_UP);
    const bool keyDown = ziat::IsKeybordTrigger(PK_DOWN);
    const bool keyEsc = ziat::IsKeybordTrigger(PK_ESC);
    const bool keyTab = ziat::IsKeybordTrigger(VK_TAB);

    const bool padUp = (bt_trigger & static_cast<int>(PadButton::PAD_UP)) != 0;
    const bool padDown = (bt_trigger & static_cast<int>(PadButton::PAD_DOWN)) != 0;
    const bool padRight = (bt_trigger & static_cast<int>(PadButton::PAD_RIGHT)) != 0;
    const bool padLeft = (bt_trigger & static_cast<int>(PadButton::PAD_LEFT)) != 0;

    const bool stickUp = (st_trigger & static_cast<int>(ziat::StickVector::LsUP));
    const bool stickDown = (st_trigger & static_cast<int>(ziat::StickVector::LsDOWN));

    // --- プルダウンが開いている間は、選択処理を最優先 ---
    if (fpsPulldownOpen) {
        if (padUp || stickUp) fpsSelectedIndex--;
        if (padDown || stickDown) fpsSelectedIndex++;

        fpsSelectedIndex = clamp_index(fpsSelectedIndex, static_cast<int>(kRenderFpsChoices.size()));

        // 適用して閉じる: Enter / →
        if (kb_trigger_enter || padRight) {
            TARGET_RENDER_FPS = choice_to_fps(kRenderFpsChoices[fpsSelectedIndex]);
            fpsPulldownOpen = false;
        }

        // キャンセル: Esc / ←
        if (keyEsc || padLeft) {
            fpsPulldownOpen = false;
        }

        if (ziat::getDebugkey()) debug = !debug;
        return SceneName::None;
    }

    // --- フォーカス移動（プルダウンが閉じている時だけ）---
    if (keyTab || padUp || padDown || stickUp || stickDown) {
        focus = (focus == Focus::Pulldown) ? Focus::DecideButton : Focus::Pulldown;
    }

    // --- フォーカスに応じた操作 ---
    if (focus == Focus::Pulldown) {
        // 開く: Enter / →
        if (kb_trigger_enter || padRight) {
            fpsPulldownOpen = true;
        }
    }
    else { // Focus::DecideButton
        // 「設定完了」を押したら GameScene へ
        if (kb_trigger_enter || padRight) {
            return SceneName::Game;
        }
    }

    if (ziat::getDebugkey()) debug = !debug;
    return SceneName::None;
}

void SettingScene::Draw() {
    ziat::create_square(3, 4, 56, 12, '=', '|', '+');

    ScreenBuffer::Print(5, 5, "描画FPS（プルダウン式）");
    ScreenBuffer::Print(5, 6, "Tab / ↑↓でフォーカス移動、Enter / →で決定");

    // プルダウン
    
    ScreenBuffer::Print(27, 8, "現在値: " + std::to_string((TARGET_RENDER_FPS > 0) ? TARGET_RENDER_FPS : 60));

    // 設定完了ボタン（フォーカス表示付き）
    const bool onButton = (focus == Focus::DecideButton) && !fpsPulldownOpen;
    ziat::create_square(5, 11, 20, 3, '-', '|', '+');
    ScreenBuffer::Print(6, 12, std::string(onButton ? "> " : "  ") + "設定完了");

    ziat::pulldown_draw(
        5, 7,
        20,
        kRenderFpsChoices,
        fpsSelectedIndex,
        fpsPulldownOpen,
        6
    );
    if (debug) ziat::showDebugBox(60, 19);
}