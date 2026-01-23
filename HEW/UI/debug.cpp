#include "debug.h"
#define CONIOEX
#include "conioex.h"
#include "ScreenBuffer.h"
#include "Input.h"
#include <chrono>
#include <bitset>

namespace ziat {
    namespace {
        std::chrono::steady_clock::time_point g_lastUpdateHzCheck = std::chrono::steady_clock::now();
        int g_updatesInInterval = 0;
        double g_currentHz = 0.0;
    }

    bool getDebugkey() {
        static bool prev_all_down = false;

        const bool ctrl = (inport(PK_CTRL) != 0);
        const bool shift = (inport(PK_SHIFT) != 0);
        const bool alt = (inport(VK_MENU) != 0);

        const bool all_down = ctrl && shift && alt;

        const bool triggered = all_down && !prev_all_down;
        prev_all_down = all_down;

        return triggered;
    }

    void showFPS(int x, int y) {
        static std::chrono::steady_clock::time_point last_check_time = std::chrono::steady_clock::now();
        static int frames_in_interval = 0;
        static double current_fps = 0.0;

        frames_in_interval++;
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - last_check_time;

        if (elapsed.count() >= 0.5) {
            current_fps = frames_in_interval / elapsed.count();
            frames_in_interval = 0;
            last_check_time = now;
        }
        ScreenBuffer::Print(x, y, "FPS: " + std::to_string(current_fps));
    }

    void showGamepadstick(int x, int y) {
        if (!ziat::IsGamepadConnect()) {
            ScreenBuffer::Print(x, y, "Lsx: NC");
            ScreenBuffer::Print(x, y + 1, "Lsy: NC");
            ScreenBuffer::Print(x, y + 2, "Rsx: NC");
            ScreenBuffer::Print(x, y + 3, "Rsy: NC");
            return;
        }

        ScreenBuffer::Print(x, y, "Lsx: " + std::to_string(inport(PJ_XPOS)));
        ScreenBuffer::Print(x, y + 1, "Lsy: " + std::to_string(inport(PJ_YPOS)));
        ScreenBuffer::Print(x, y + 2, "Rsx: " + std::to_string(inport(PJ_ZPOS)));
        ScreenBuffer::Print(x, y + 3, "Rsy: " + std::to_string(inport(PJ_RPOS)));
    }

    void showGamepadbtns(int x, int y) {
        if (!ziat::IsGamepadConnect()) {
            ScreenBuffer::Print(x, y, "btns: NC");
            return;
        }
        ScreenBuffer::Print(x, y, "btns: " + std::bitset<13>(inport(PJ_BTNS)).to_string());
    }

    void showDebugBox(int x, int y) {
        showFPS(x, y);
        /*showGamepadstick(x, y + 1);
        showGamepadbtns(x, y + 5);*/
    }
}