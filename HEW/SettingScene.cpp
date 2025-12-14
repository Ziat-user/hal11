#include <iostream>

#define CONIOEX
#include "conioex.h"
#include "gamepad.h"
#include "setting.h"
#include "Game.h"

#include "SettingScene.h"



void SettingScene::Initialize() {
    clrscr();
    stick_s_check = 0;
    trigger = 0;
}

SceneName SettingScene::Update() {
    trigger = ziat::IsButtonTriggered(PadButton::PAD_LEFT);
    if (stick_s_check == false) {
        // まだ設定が完了していない場合
        if (trigger) {
            ziat::setting_stick(&NEUTRAL_STICK_R_X, &NEUTRAL_STICK_R_Y, &NEUTRAL_STICK_L_X, &NEUTRAL_STICK_L_Y);
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
    return SceneName::None; // 何もなければ維持
}

void SettingScene::Draw() {
    gotoxy(1, 1); // 描画位置を先頭に
    clrscr();
    if (stick_s_check == false) {
        std::cout << "コントローラーの設定を変更します\n";
        std::cout << "コントローラーがニュートラルの状態で、←ボタンを押してください\n";
    }
    else {
        std::cout << "設定が完了しました。\n";
        std::cout << "←ボタンで次に進みます\n";
    }
    std::cout
        << TARGET_FPS << std::endl
        << "sticklx:" << inport(PJ_XPOS) << std::endl
        << "stickly:" << inport(PJ_YPOS) << std::endl
        << "stickrx:" << inport(PJ_ZPOS) << std::endl
        << "stickry:" << inport(PJ_RPOS) << std::endl
        << NEUTRAL_STICK_L_X << std::endl
        << NEUTRAL_STICK_L_Y << std::endl
        << NEUTRAL_STICK_R_X << std::endl
        << NEUTRAL_STICK_R_Y << std::endl;
}