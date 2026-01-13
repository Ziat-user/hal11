#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#define CONIOEX
#include "conioex.h"
#include "ScreenBuffer.h"

#include <string>
#include <vector>



namespace ziat {
    // x,yを中心とした半径rの円をcで描画する
    bool create_circle(int x, int y, int r, char c);

    // 左上の座標をx,yとし、横の大きさをxs、縦の大きさをysとする
    bool create_square(int x, int y, int xs, int ys, char x_edge, char y_edge, char vertex);

    // プルダウン(コンボボックス風)の描画のみ行う
    // x,y: 左上座標（1-origin想定。ScreenBuffer::Printに合わせる）
    // width: 枠の横幅（最小4推奨）
    // open: trueなら候補リストも描画
    // selectedIndex: 0..choices.size()-1
    // visibleRows: open時に表示する最大行数（スクロール表示）
    void pulldown_draw(
        int x,
        int y,
        int width,
        const std::vector<std::string>& choices,
        int selectedIndex,
        bool open,
        int visibleRows = 6
    );
}