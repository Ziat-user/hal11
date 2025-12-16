#include "gamepad.h"
#include "setting.h"
#include "Game.h"
#include "ScreenBuffer.h"

#include "SettingScene.h"



void SettingScene::Initialize() {
    stick_s_check = 0;
    trigger = 0;
    fps_c = 0; // 初期化を追加
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
    fps_c++; // フレーム数をカウントアップ
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

    // 現在のフレーム数を表示
    const std::string fps_cs = std::to_string(fps_c);
    const std::string fps_css = std::to_string(fps_c / 30);
    ScreenBuffer::Print(1, 3, fps_cs);
    ScreenBuffer::Print(1, 4, fps_css);
}