#include "UI.h"
#include <string>
#include <cmath>
#include <numbers>

namespace ziat {
    bool create_circle(int x, int y, int r, char c) {
        if (r <= 0) return false;

        std::string s(1, c);

        // ƒRƒ“ƒ\[ƒ‹‚Ì•¶ŽšƒAƒXƒyƒNƒg”ä•â³ (’ÊíA•¶Žš‚Íc’·‚È‚Ì‚ÅY•ûŒü‚ðˆ³k‚·‚é)
        // 0.5 ‚­‚ç‚¢‚ªˆê”Ê“I (”¼Šp•¶Žš •1:‚2 ‚Ìê‡)
        const double aspect = 0.5;

        // Šp“x‚Ì‚Ý•B‰~Žü‚Ì’·‚³‚É‰ž‚¶‚Ä×‚©‚­‚·‚é
        // ‰~Žü‚Ì’·‚³(•¶Žš”Š·ŽZ)  2 * pi * r
        // Œ„ŠÔ‚ª‚Å‚«‚È‚¢‚æ‚¤‚É­‚µ×‚©‚­‚Þ
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

        // Žl‹÷
        ScreenBuffer::Print(x, y, s_vertex);                   // ¶ã
        ScreenBuffer::Print(x + xs - 1, y, s_vertex);          // ‰Eã
        ScreenBuffer::Print(x, y + ys - 1, s_vertex);          // ¶‰º
        ScreenBuffer::Print(x + xs - 1, y + ys - 1, s_vertex); // ‰E‰º

        // ‰¡‚Ì•Ó (•‚ª2‚æ‚è‘å‚«‚¢ê‡‚Ì‚Ý•`‰æ)
        if (xs > 2) {
            std::string s_x_edge_line(xs - 2, x_edge);
            ScreenBuffer::Print(x + 1, y, s_x_edge_line);          // ã•Ó
            ScreenBuffer::Print(x + 1, y + ys - 1, s_x_edge_line); // ‰º•Ó
        }

        // c‚Ì•Ó (‚‚³‚ª2‚æ‚è‘å‚«‚¢ê‡‚Ì‚Ý•`‰æ)
        if (ys > 2) {
            for (int i = 1; i < ys - 1; ++i) {
                ScreenBuffer::Print(x, y + i, s_y_edge);           // ¶•Ó
                ScreenBuffer::Print(x + xs - 1, y + i, s_y_edge);  // ‰E•Ó
            }
        }
        return true;
    }
}