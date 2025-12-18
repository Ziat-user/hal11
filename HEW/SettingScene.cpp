#include "gamepad.h"
#include "setting.h"
#include "Game.h"
#include "ScreenBuffer.h"
#define CONIOEX
#include "conioex.h"
#include "UI.h"
#include "debug.h"

#include "SettingScene.h"

void SettingScene::Initialize() {
    if (ziat::IsGamepadConnect())gp_connect = true;
    else gp_connect = false;
    bt_trigger = 0;
    kb_trigger_enter = 0;
    stick_s_check = false;
    debug = 0;
}

SceneName SettingScene::Update() {
    bt_trigger = ziat::IsButtonTriggered();
    kb_trigger_enter = ziat::IsKeybordTrigger(PK_ENTER);

    if (gp_connect) {
        if (stick_s_check == false) {
            // まだ設定が完了していない場合
            if (((bt_trigger & static_cast<int>(PadButton::PAD_LEFT)) != 0) || kb_trigger_enter){
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
        if (((bt_trigger & static_cast<int>(PadButton::PAD_LEFT)) != 0) || kb_trigger_enter) {
            return SceneName::Game;
        }
    }
    if (ziat::getDebugkey()) debug = !debug;
    
    return SceneName::None; // 何もなければ維持
}

void SettingScene::Draw() {
    ziat::create_square(3, 4, 50, 4, '=', '|', '+');
 
    if (gp_connect) {
        if (stick_s_check == false) {
            ScreenBuffer::Print(5, 5, "コントローラーの設定を変更します");
            ScreenBuffer::Print(5, 6, "コントローラーがニュートラルの状態で、←ボタンを押してください");
        }
        else {
            ScreenBuffer::Print(5, 5, "設定が完了しました");
            ScreenBuffer::Print(5, 6, "←で次に進みます");
        }
    }
    else {
        ScreenBuffer::Print(5, 5, "コントローラーが接続されていません");
        ScreenBuffer::Print(5, 6, "Enterキーを押してゲームを開始します");
    }

    if (debug)ziat::showDebugBox(60, 20);
    
}