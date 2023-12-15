#include <stdio.h>
#include "src/show.h"
#include "src/chess.h"

extern "C" {
    #include "common/common.h"
}

extern Chess* chessBoard[10][9];

int main() {
    fb_init("/dev/fb0");
    font_init("../font.ttc");
    initChessBoard(player::red);
    // printChess();
    mytest();
    draw_message_prompt("hello world");
    return 0;
}