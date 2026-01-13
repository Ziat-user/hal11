#include <chrono>
#include <memory>
#include <iostream>
#include <conio.h>


#include "Setting.h"
#include "main.h"
#include "IScene.h"
#include "ScreenBuffer.h"
#include "debug.h"

#include "SettingScene.h"
#include "GameScene.h"
#include "TitleScene.h"

int main() {
	if (HEWConsoleStartup(0) != 0) {
		std::cerr << ("Initialization failed.\n");
		HEWConsoleCleanup(0);
		return 1;
	}
	setcursortype(NOCURSOR);
	ziat::initialize(NEUTRAL_STICK_R_X, NEUTRAL_STICK_R_Y, NEUTRAL_STICK_L_X, NEUTRAL_STICK_L_Y, TARGET_FPS);

	// 60固定（更新も描画も同一）
	TARGET_FPS = 60;

	ScreenBuffer::Initialize();

	using clock = std::chrono::steady_clock;
	using us = std::chrono::microseconds;

	const auto FRAME_DT = us(1000000 / 60); // 60fps
	auto last = clock::now();

	std::unique_ptr<IScene> currentScene = std::make_unique<TitleScene>();
	currentScene->Initialize();

	bool isRunning = true;
	while (isRunning) {
		const auto now = clock::now();
		const auto elapsed = std::chrono::duration_cast<us>(now - last);

		if (elapsed >= FRAME_DT) {
			last = now;

			SceneName nextScene = currentScene->Update();

			ScreenBuffer::Clear();
			currentScene->Draw();
			ScreenBuffer::Show();

			// シーン遷移
			if (nextScene != SceneName::None) {
				switch (nextScene) {
				case SceneName::Title:
					currentScene = std::make_unique<TitleScene>();
					currentScene->Initialize();
					break;
				case SceneName::Setting:
					currentScene = std::make_unique<SettingScene>();
					currentScene->Initialize();
					break;
				case SceneName::Game:
					currentScene = std::make_unique<GameScene>();
					currentScene->Initialize();
					break;
				case SceneName::Exit:
					isRunning = false;
					break;
				}
			}
		}
	}
	HEWConsoleCleanup(0);
	return 0;
}