#include <chrono> //時刻取得に使用
#include <thread>  //C++用のsleepに使用
#include <memory>
#include <iostream>

#include "Setting.h"
#include "condoi.h"
#include "IScene.h"
#include "ScreenBuffer.h"

#include "SettingScene.h"
#include "GameScene.h"

int main(){
	if (!CL11Startup()) {
		std::cerr << "cl11error";
		return 0;
	}
	ziat::initialize(NEUTRAL_STICK_R_X, NEUTRAL_STICK_R_Y, NEUTRAL_STICK_L_X, NEUTRAL_STICK_L_Y, TARGET_FPS);
	SetCursorVisibility(FALSE);

	ScreenBuffer::Initialize();

	auto FRAME_DURATION = std::chrono::milliseconds(1000) / TARGET_FPS;

	std::unique_ptr<IScene> currentScene = std::make_unique<SettingScene>();

	currentScene->Initialize();
	bool isRunning = true;
	while (isRunning) {
		auto frame_start = std::chrono::steady_clock::now();

		ScreenBuffer::Clear();

		//ここにゲーム本体を挿入
		SceneName nextScene = currentScene->Update();

		currentScene->Draw(); ScreenBuffer::Show();//Drawでバッファに登録、Showで表示

		if (nextScene != SceneName::None) {
			switch (nextScene) {
			case SceneName::Title:
				currentScene = std::make_unique<SettingScene>(); // タイトルに入れ替え
				currentScene->Initialize();
				break;
			case SceneName::Game:
				currentScene = std::make_unique<GameScene>();  // ゲームに入れ替え
				currentScene->Initialize();
				break;
			case SceneName::Exit:
				isRunning = false; // ループを抜ける
				break;
			}
		}

		auto frame_end = std::chrono::steady_clock::now();
		auto elapsed_time = frame_end - frame_start;
		if (elapsed_time < FRAME_DURATION) {
			std::this_thread::sleep_for(FRAME_DURATION - elapsed_time);
		}
	}
}