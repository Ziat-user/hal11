#include "gamepad.h"
#include "setting.h"
#include "Game.h"
#include "ScreenBuffer.h"

#include "SettingScene.h"

void SettingScene::Initialize() {
    stick_s_check = 0;
    trigger = 0;

    // FPS計測初期化
    last_check_time = std::chrono::steady_clock::now();
    frames_in_interval = 0;
    current_fps = 0.0;
}

SceneName SettingScene::Update() {
    trigger = ziat::IsButtonTriggered(PadButton::PAD_LEFT);
    if (stick_s_check == false) {
        // まだ設定が完了していない場合
        if (trigger) {
            ziat::setting_stick(NEUTRAL_STICK_R_X, NEUTRAL_STICK_R_Y, NEUTRAL_STICK_L_X, NEUTRAL_STICK_L_Y);
            stick_s_check = true; // 設定完了フラグを立てる
        }
    }
    else {
        // 設定が完了している場合
        if (trigger) {
            // ボタンが押されたら次のシーンへ
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
    if (stick_s_check == false) {
        ScreenBuffer::Print(1, 1, "コントローラーの設定を変更します");
        ScreenBuffer::Print(1, 2, "コントローラーがニュートラルの状態で、←ボタンを押してください");
    }
    else {
        ScreenBuffer::Print(1, 1, "設定が完了しました");
        ScreenBuffer::Print(1, 2, "←で次に進みます");
    }
    // 計測したFPSを表示
    ScreenBuffer::Print(1, 5, "FPS: " + std::to_string(current_fps));
}