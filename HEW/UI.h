#pragma once
#define CONIOEX
#include "conioex.h"
#include "ScreenBuffer.h"

namespace ziat {
    // x,y‚ğ’†S‚Æ‚µ‚½”¼Œar‚Ì‰~‚ğc‚Å•`‰æ‚·‚é
    bool create_circle(int x, int y, int r, char c);

    // ¶ã‚ÌÀ•W‚ğx,y‚Æ‚µA‰¡‚Ì‘å‚«‚³‚ğxsAc‚Ì‘å‚«‚³‚ğys‚Æ‚·‚é
    // (ˆø”–¼‚Ì xy ‚Íc• ys ‚Æ‚µ‚ÄÀ‘•‚µ‚Ü‚·)
    bool create_square(int x, int y, int xs, int ys, char x_edge, char y_edge, char vertex);
}