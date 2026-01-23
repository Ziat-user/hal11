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

    kb_trigger_enter = 0;
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

    kb_trigger_enter = ziat::IsKeybordTrigger(PK_ENTER);
    const bool keyUp = ziat::IsKeybordTrigger(PK_UP);
    const bool keyDown = ziat::IsKeybordTrigger(PK_DOWN);
    const bool keyEsc = ziat::IsKeybordTrigger(PK_ESC);
    const bool keyTab = ziat::IsKeybordTrigger(VK_TAB);

    // --- プルダウンが開いている間は、選択処理を最優先 ---
    if (fpsPulldownOpen) {
        if (keyUp) fpsSelectedIndex--;
        if (keyDown) fpsSelectedIndex++;

        fpsSelectedIndex = clamp_index(fpsSelectedIndex, static_cast<int>(kRenderFpsChoices.size()));

        // 適用して閉じる: Enter / →
        if (kb_trigger_enter) {
            TARGET_RENDER_FPS = choice_to_fps(kRenderFpsChoices[fpsSelectedIndex]);
            fpsPulldownOpen = false;
        }

        // キャンセル: Esc / ←
        if (keyEsc) {
            fpsPulldownOpen = false;
        }

        if (ziat::getDebugkey()) debug = !debug;
        return SceneName::None;
    }

    // --- フォーカス移動（プルダウンが閉じている時だけ）---
    if (keyTab || keyUp || keyDown) {
        focus = (focus == Focus::Pulldown) ? Focus::DecideButton : Focus::Pulldown;
    }

    // --- フォーカスに応じた操作 ---
    if (focus == Focus::Pulldown) {
        // 開く: Enter / →
        if (kb_trigger_enter) {
            fpsPulldownOpen = true;
        }
    }
    else { // Focus::DecideButton
        // 「設定完了」を押したら GameScene へ
        if (kb_trigger_enter) {
            return SceneName::Game;
        }
    }

    if (ziat::getDebugkey()) debug = !debug;
    return SceneName::None;
}

void SettingScene::Draw() {
    ziat::create_square(3, 4, 56, 12, '=', '|', '+');

    ScreenBuffer::Print(5, 5, u8"描画FPS（プルダウン式）");
    ScreenBuffer::Print(5, 6, u8"Tab / ↑↓でフォーカス移動、Enter / →で決定");

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