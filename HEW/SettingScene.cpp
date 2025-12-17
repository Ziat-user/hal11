#include "gamepad.h"
#include "setting.h"
#include "Game.h"
#include "ScreenBuffer.h"
#define CONIOEX
#include "conioex.h"

#include "SettingScene.h"

void SettingScene::Initialize() {
    if (ziat::IsGamepadConnect())gp_connect = true;
    else gp_connect = false;
    bt_trigger = 0;
    kb_trigger_enter = 0;
    stick_s_check = false;

    // FPS計測初期化
    last_check_time = std::chrono::steady_clock::now();
    frames_in_interval = 0;
    current_fps = 0.0;
}

SceneName SettingScene::Update() {
    bt_trigger = ziat::IsButtonTriggered();
    kb_trigger_enter = ziat::IsKeybordTrigger(PK_ENTER);

    if (gp_connect) {
        if (stick_s_check == false) {
            // まだ設定が完了していない場合
            if (((bt_trigger & static_cast<int>(PadButton::PAD_LEFT)) != 0) || kb_trigger_enter) {
                ziat::setting_stick(NEUTRAL_STICK_R_X, NEUTRAL_STICK_R_Y, NEUTRAL_STICK_L_X, NEUTRAL_STICK_L_Y);
                stick_s_check = true; // 設定完了フラグを立てる
            }
        }
        else {
            // 設定が完了している場合
            if (((bt_trigger & static_cast<int>(PadButton::PAD_LEFT)) != 0) || kb_trigger_enter) {
                // ボタンが押されたら次のシーンへ
                return SceneName::Game;
            }
        }
    }
    else {
        // コントローラー未接続の場合、Enterキーでゲームへ
        if (kb_trigger_enter) {
            return SceneName::Game;
        }
    }

    // 0.5秒ごとのFPS計測処理
    frames_in_interval++;
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - last_check_time;

    if (elapsed.count() >= 0.5) {
        current_fps = frames_in_interval / elapsed.count();
        frames_in_interval = 0;
        last_check_time = now;
    }
    return SceneName::None; // 何もなければ維持
}

void SettingScene::Draw() {
    if (gp_connect) {
        if (stick_s_check == false) {
            ScreenBuffer::Print(1, 1, "コントローラーの設定を変更します");
            ScreenBuffer::Print(1, 2, "コントローラーがニュートラルの状態で、←ボタンを押してください");
        }
        else {
            ScreenBuffer::Print(1, 1, "設定が完了しました");
            ScreenBuffer::Print(1, 2, "←で次に進みます");
        }
    }
    else {
        ScreenBuffer::Print(1, 1, "コントローラーが接続されていません");
        ScreenBuffer::Print(1, 2, "Enterキーを押してゲームを開始します");
    }

    // 計測したFPSを表示
    ScreenBuffer::Print(1, 5, "FPS: " + std::to_string(current_fps));
}