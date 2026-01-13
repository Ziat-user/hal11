#include "UI.h"
#include <string>
#include <cmath>
#include <numbers>
#include <algorithm>


namespace ziat {
    bool create_circle(int x, int y, int r, char c) {
        if (r <= 0) return false;

        std::string s(1, c);

        const double aspect = 0.5;
        double step = 1.0 / (static_cast<double>(r) * 2.0);

        for (double theta = 0.0; theta < 2.0 * std::numbers::pi; theta += step) {
            int px = static_cast<int>(std::round(x + r * std::cos(theta)));
            int py = static_cast<int>(std::round(y + r * std::sin(theta) * aspect));
            ScreenBuffer::Print(px, py, s);
        }
        return true;
    }

    bool create_square(int x, int y, int xs, int ys, char x_edge, char y_edge, char vertex) {
        if (xs <= 0 || ys <= 0) return false;

        std::string s_vertex(1, vertex);
        std::string s_y_edge(1, y_edge);

        // 内側をスペースで塗りつぶして「透過」を防止
        if (xs > 2 && ys > 2) {
            std::string fill_line(xs - 2, ' ');
            for (int iy = 1; iy < ys - 1; ++iy) {
                ScreenBuffer::Print(x + 1, y + iy, fill_line);
            }
        }

        // 四隅
        ScreenBuffer::Print(x, y, s_vertex);
        ScreenBuffer::Print(x + xs - 1, y, s_vertex);
        ScreenBuffer::Print(x, y + ys - 1, s_vertex);
        ScreenBuffer::Print(x + xs - 1, y + ys - 1, s_vertex);

        // 横の辺
        if (xs > 2) {
            std::string s_x_edge_line(xs - 2, x_edge);
            ScreenBuffer::Print(x + 1, y, s_x_edge_line);
            ScreenBuffer::Print(x + 1, y + ys - 1, s_x_edge_line);
        }

        // 縦の辺
        if (ys > 2) {
            for (int i = 1; i < ys - 1; ++i) {
                ScreenBuffer::Print(x, y + i, s_y_edge);
                ScreenBuffer::Print(x + xs - 1, y + i, s_y_edge);
            }
        }
        return true;
    }

    static std::string fit_text(const std::string& s, int width) {
        if (width <= 0) return "";
        if (static_cast<int>(s.size()) <= width) {
            return s + std::string(width - static_cast<int>(s.size()), ' ');
        }
        if (width == 1) return s.substr(0, 1);
        return s.substr(0, width - 1) + "…";
    }

    void pulldown_draw(
        int x,
        int y,
        int width,
        const std::vector<std::string>& choices,
        int selectedIndex,
        bool open,
        int visibleRows
    ) {
        if (width < 4) width = 4;
        if (visibleRows < 1) visibleRows = 1;

        // データが空のときの表示
        const bool hasChoices = !choices.empty();
        const int maxIndex = hasChoices ? static_cast<int>(choices.size()) - 1 : 0;
        const int idx = hasChoices ? std::clamp(selectedIndex, 0, maxIndex) : 0;

        // 1行の枠（コンボボックス本体）
        create_square(x, y, width, 3, '-', '|', '+');

        const int innerW = width - 2;
        std::string label = hasChoices ? choices[idx] : "(empty)";
        label = fit_text(label, std::max(0, innerW - 2));

        // 左: テキスト、右: 開閉記号
        const std::string arrow = open ? "^" : "v";
        ScreenBuffer::Print(x + 1, y + 1, label + " " + arrow);

        if (!open) return;
        if (!hasChoices) return;

        const int rows = std::min(visibleRows, static_cast<int>(choices.size()));

        // 表示開始位置（選択中が常に見えるようにする簡易スクロール）
        int start = 0;
        if (idx >= rows) start = idx - rows + 1;
        start = std::clamp(start, 0, static_cast<int>(choices.size()) - rows);

        // 候補枠
        create_square(x, y + 3, width, rows + 2, '-', '|', '+');

        for (int i = 0; i < rows; ++i) {
            const int choiceIndex = start + i;
            const bool isSel = (choiceIndex == idx);

            // 選択中に ">" を付ける
            std::string line = (isSel ? ">" : " ");
            line += fit_text(choices[choiceIndex], std::max(0, innerW - 1));

            ScreenBuffer::Print(x + 1, y + 4 + i, line);
        }
    }
}