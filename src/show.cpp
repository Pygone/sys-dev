//
// Created by wyxm on 2023/12/15.
//

#include "show.h"
#include <cstring>

extern "C" {
    #include "../common/common.h"
}

static void draw_back() {
    int x = 990, y = 10;
    int delta = 20;
    int len = 55;
    fb_draw_bold_line(x, y, x, y + len, COLOR_grey41);
    fb_draw_bold_line(x, y, x + delta, y + delta, COLOR_grey41);
    fb_draw_bold_line(x, y, x - delta, y + delta, COLOR_grey41);
    fb_update();
}

static void draw_welcome(bool flag) {
    if (flag) {
        fb_image* img = fb_read_jpeg_image("../pic/xuhua600.jpg"); // 最终版本
        fb_draw_image(0, 0, img, 0);
    } 
    else {
        fb_image* img = fb_read_jpeg_image("../pic/main.jpg"); // 最终版本
        fb_draw_image(0, 0, img, 0);
        draw_back();
    }
    fb_update();
}

static void draw_below(int x, int y) {
    fb_draw_bold_line(x - 5, y + 5, x - 10, y + 5, COLOR_grey41);
    fb_draw_bold_line(x + 5, y + 5, x + 10, y + 5, COLOR_grey41);
    fb_draw_bold_line(x - 5, y + 5, x - 5, y + 10, COLOR_grey41);
    fb_draw_bold_line(x + 5, y + 5, x + 5, y + 10, COLOR_grey41);
}

static void draw_upon(int x, int y) {
    fb_draw_bold_line(x - 5, y - 5, x - 10, y - 5, COLOR_grey41);
    fb_draw_bold_line(x + 5, y - 5, x + 10, y - 5, COLOR_grey41);
    fb_draw_bold_line(x - 5, y - 5, x - 5, y - 10, COLOR_grey41);
    fb_draw_bold_line(x + 5, y - 5, x + 5, y - 10, COLOR_grey41);
}

static void draw_chuhe_and_hanjie() {
    fb_draw_text(XBaseline + 4 * 60 + 30, 90, "楚", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline + 4 * 60 + 30, 150, "河", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline + 4 * 60 + 35, 60 + 180 + 10, "H", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline + 4 * 60 + 35, 60 + 220 + 10, "U", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline + 4 * 60 + 35, 60 + 260 + 10, "S", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline + 4 * 60 + 35, 60 + 300 + 10, "T", 40, CHESS_FONT_COLOR, RIGHT);
    // fb_draw_text(XBaseline + 4 * 60 + 35, 60 + 180 + 10, "HUST", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline + 4 * 60 + 30, 450, "漢", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline + 4 * 60 + 30, 510, "界", 40, CHESS_FONT_COLOR, RIGHT);
}

static int prompt_x = XBaseline + 580 + 15;
static int prompt_x_len = 150;
static int prompt_x_st = prompt_x + 95;

static void draw_frames() {
    fb_draw_rect(XBaseline - 100 - 25, 50, 50, 140, COLOR_Tan3);
    fb_draw_rect(XBaseline - 100 - 25, 230, 50, 140, COLOR_Tan3);
    fb_draw_rect(XBaseline - 100 - 25, 410, 50, 140, COLOR_Tan3);
    fb_draw_text(XBaseline - 100, 90, "取", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline - 100, 150, "消", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline - 100, 270, "确", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline - 100, 330, "定", 40, CHESS_FONT_COLOR, RIGHT);   
    fb_draw_text(XBaseline - 100, 450, "投", 40, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(XBaseline - 100, 510, "降", 40, CHESS_FONT_COLOR, RIGHT);
}

static void draw_region() {
    // fb_draw_rect(prompt_x, 20, 150, 560, COLOR_WHITE);
    fb_draw_text(prompt_x + 130, 35, "消", 30, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(prompt_x + 130, 65, "息", 30, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(prompt_x + 130, 95, "提", 30, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(prompt_x + 130, 125, "示", 30, CHESS_FONT_COLOR, RIGHT);
    fb_draw_text(prompt_x + 130, 155, "区", 30, CHESS_FONT_COLOR, RIGHT);
}

void draw_message_prompt(char* msg) {
    // fb_draw_rect(prompt_x, 20, 110, 560, COLOR_WHITE);
    fb_draw_text(prompt_x_st, 40, msg, 30, CHESS_FONT_COLOR, RIGHT);
    fb_update();
}

void draw_chessboard() {
    // 绘制背景
    // fb_draw_rect(XBaseline - 40, 20, 620, 560, COLOR_Tan3);
    draw_welcome(true); 

    // 画横线
    for (int i = 60;i <= 540; i += 60) {
        if (i == 60 || i == 540) 
            fb_draw_bold_line(XBaseline, i, XBaseline + 9 * 60, i, COLOR_grey41);
        else {
            fb_draw_bold_line(XBaseline, i, XBaseline + 4 * 60, i, COLOR_grey41);
            fb_draw_bold_line(XBaseline + 5 * 60, i, XBaseline + 9 * 60, i, COLOR_grey41);
        }
    }

    // 画竖线
    for (int i = XBaseline; i <= XBaseline + 9 * 60; i += 60) {
        fb_draw_bold_line(i, 60, i, 540, COLOR_grey41);
    }

    // 画斜线 
    fb_draw_bold_line(XBaseline, 240, XBaseline + 120, 360, COLOR_grey41);
    fb_draw_bold_line(XBaseline, 360, XBaseline + 120, 240, COLOR_grey41);
    fb_draw_bold_line(XBaseline + 7 * 60, 240, XBaseline + 9 * 60, 360, COLOR_grey41);
    fb_draw_bold_line(XBaseline + 7 * 60, 360, XBaseline + 9 * 60, 240, COLOR_grey41);

    // 画兵线
    for (int i = 3; i <= 6; i += 3) {
        for (int j = 0; j <= 8; j += 2) {
            int x = XBaseline + i * 60, y = 60 + j * 60;
            if (y == 60) {
                draw_below(x, y);
            }
            else if (y == 540) {
                draw_upon(x, y);
            }
            else {
                draw_below(x, y);
                draw_upon(x, y);
            }
        }
    }
    // 画炮位
    for (int i = 2; i <= 7; i += 5) {
        for (int j = 1; j <= 7; j += 6) {
            int x = XBaseline + i * 60, y = 60 + j * 60;
            draw_below(x, y);
            draw_upon(x, y);
        }
    }
    // 画外边框
    fb_draw_bold_line(XBaseline - 10, 60 - 10, XBaseline + 540 + 10, 60 - 10, COLOR_grey31);
    fb_draw_bold_line(XBaseline - 10, 540 + 10, XBaseline + 540 + 10, 540 + 10, COLOR_grey31);
    fb_draw_bold_line(XBaseline - 10, 60 - 10, XBaseline - 10, 540 + 10, COLOR_grey31);
    fb_draw_bold_line(XBaseline + 540 + 10, 60 - 10, XBaseline + 540 + 10, 540 + 10, COLOR_grey31);

    // 画楚河汉界
    draw_chuhe_and_hanjie();
    return;
}

char* getCharacters(chessType type_, player play_) {
    switch (type_) {
        case chessType::jiang:
            if (play_ == player::red) {
                return "帥";
            } else {
                return "将";
            }
            break;
        case chessType::shi:
            if (play_ == player::red) {
                return "仕";
            } else {
                return "士";
            }
            break;
        case chessType::xiang:
            return "象";
            break;
        case chessType::ma:
            return "馬";
            break;
        case chessType::ju:
            return "車";
            break;
        case chessType::pao:
            return "炮";
            break;
        case chessType::bing:
            if (play_ == player::red) {
                return "兵";
            } else {
                return "卒";
            }
            break;
    }
}

void draw_chesspiece(int x, int y, chessType type_, player play_) {
    char* buf;
    // memset(buf, '\0', sizeof(buf));
    buf = getCharacters(type_, play_); // 获取棋子字符
    fb_draw_filled_circle(x, y, CHESS_Radius, COLOR_Tan2); // 画棋子底色
    int color = COLOR_BLACK;
    if (play_ == player::red) {
        color = COLOR_RED;
    }
    fb_draw_ring(x, y, CHESS_Ring, color); // 画棋子边框
    if (play_ == player::red) {
        fb_draw_text(x, y, buf, CHESS_FontSize, COLOR_RED, RIGHT); // 画棋子字符
    } else {
        fb_draw_text(x, y, buf, CHESS_FontSize, COLOR_BLACK, RIGHT); // 画棋子字符
    }
}

std::pair<int, int> posConvert(Position pos) {
    int x = XBaseline + pos.x * 60, y = 60 + pos.y * 60;
    return std::make_pair(x, y);
}

void draw_chesspiece(Position pos, chessType type_, player play_) {
    std::pair<int, int>res = posConvert(pos);
    draw_chesspiece(res.first, res.second, type_, play_);
}

void draw_choose(Position pos, chessType type_, player play_) {
    std::pair<int, int>res = posConvert(pos);
    draw_chesspiece(res.first, res.second, type_, play_);
    fb_draw_ring(res.first, res.second, CHESS_Radius, COLOR_LightSkyBlue);
    // fb_update();
}

void draw_landing_point(Position pos) {
    std::pair<int, int>res = posConvert(pos);
    fb_draw_filled_circle(res.first, res.second, CHESS_LandingPoint, COLOR_LightSkyBlue);
    // fb_update();
}

void printChess() {
	draw_chessboard();
	for (auto & i : chessBoard) {
		for (auto & j : i) {
			if (j != nullptr) {
				draw_chesspiece(j->pos_, j->getChessType(), j->getChessColor());
			}
		}
	}
}

void initChess() {
    draw_chessboard(); // 绘制棋盘
    draw_frames(); // 绘制按钮框
    draw_region(); // 绘制提示区
    for (auto & i : chessBoard) {
		for (auto & j : i) {
			if (j != nullptr) {
				draw_chesspiece(j->pos_, j->getChessType(), j->getChessColor());
			}
		}
	}
    fb_update();
}

void draw_win() {
    draw_welcome(false);
    // fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK);
    fb_draw_text(SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT / 2 - 60, "W", 150, COLOR_RED, RIGHT);
    fb_draw_text(SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT / 2 - 60 + 100, "in!", 150, COLOR_RED, RIGHT);
    fb_update();
}

void draw_lose() {
    draw_welcome(false);
    // fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK);
    fb_draw_text(SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT / 2 - 80, "Lose!", 150, COLOR_RED, RIGHT);
    fb_update();
}

void draw_begin() {
    draw_welcome(false);
    fb_image* img = fb_read_jpeg_image("../pic/start.jpg");
    fb_draw_image(SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT / 2 - 160, img, 0);
    fb_update();
}

static void draw_waiting(int color) {
    // fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK); // TODO:test
    int x = SCREEN_WIDTH / 2 + 80, y = SCREEN_HEIGHT / 2;
    int r = 18; // 勾股数(45°)
    int rr = 11;
    int bias = 8;
    fb_draw_bold_line(x + bias, y, x + bias + r, y, color); // 上
    fb_draw_bold_line(x, y - bias - r, x, y - bias, color); // 左
    fb_draw_bold_line(x - bias - r, y, x - bias, y, color); // 下
    fb_draw_bold_line(x, y + bias, x, y + bias + r, color); // 右
    fb_draw_bold_line(x + bias + rr, y - bias - rr, x + bias, y - bias, color); // 左上
    fb_draw_bold_line(x - bias - rr - 1, y - bias - rr - 1, x - bias, y - bias, color); // 左下
    fb_draw_bold_line(x - bias, y + bias, x - bias - rr, y + bias + rr, color); // 右下
    fb_draw_bold_line(x + bias, y + bias, x + bias + rr + 1, y + bias + rr + 1, color); // 右上
    fb_update();
}

void draw_match() {
    draw_welcome(false);
    fb_draw_text(SCREEN_WIDTH / 2 + 170, SCREEN_HEIGHT / 2 - 70, "匹 配 中", 50, COLOR_BLACK, RIGHT);
    draw_waiting(COLOR_RED);
    fb_update();
}

static void draw_chesspiece_for_match_win(int x, int y, chessType type_, player play_) {
    char* buf;
    buf = getCharacters(type_, play_); // 获取棋子字符
    fb_draw_filled_circle(x, y, CHESS_Radius * 2, COLOR_Tan2); // 画棋子底色
    int color = COLOR_BLACK;
    if (play_ == player::red) {
        color = COLOR_RED;
    }
    fb_draw_ring(x, y, CHESS_Ring * 2, color); // 画棋子边框
    if (play_ == player::red) {
        fb_draw_text(x, y, buf, CHESS_FontSize * 2, COLOR_RED, RIGHT); // 画棋子字符
    } else {
        fb_draw_text(x, y, buf, CHESS_FontSize * 2, COLOR_BLACK, RIGHT); // 画棋子字符
    }
}

void draw_match_win() {
    draw_welcome(false);
    fb_draw_text(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 120, "执红", 60, COLOR_RED, RIGHT);
    fb_draw_text(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 120 + 180, "执黑", 60, COLOR_BLACK, RIGHT);
    Chess* jiang = new ChessJiang(black, { 0, 0 });
    Chess* shuai = new ChessJiang(red, { 0, 0 });
    draw_chesspiece_for_match_win(SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT / 2 - 120 + 40 - 10, shuai->getChessType(), shuai->getChessColor());
    draw_chesspiece_for_match_win(SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT / 2 - 120 + 240 - 40, jiang->getChessType(), jiang->getChessColor());
    fb_update();
}

void draw_match_lose() {
    draw_welcome(false);
    fb_draw_text(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 120, "等待对方选边", 50, COLOR_BLACK, RIGHT);
    fb_update();
}

bool isClickBegin(int posx, int posy) {
    int x = SCREEN_WIDTH / 2 + 40, y = SCREEN_HEIGHT / 2 - 160;
    int w = 90, h = 340;
    if (posx >= x && posx <= x + w && posy >= y && posy <= y + h) {
        return true;
    }
    return false;
}

bool isClickQuit(int posx, int posy) {
    int x = 990, delta = 20, y = 10, len = 55;
    if (posx >= x - delta && posx <= x + delta && posy >= y && posy <= y + len) {
        return true;
    }
    return false;
}

bool isClickChooseRed(int posx, int posy) {
    int x = SCREEN_WIDTH / 2 + 40, y = SCREEN_HEIGHT / 2 - 120 + 40 - 10, radius = CHESS_Radius * 2;
    if ((posx - x) * (posx - x) + (posy - y) * (posy - y) <= radius * radius) {
        return true;
    }
    return false;
}

bool isClickChooseBlack(int posx, int posy) {
    int x = SCREEN_WIDTH / 2 + 40, y = SCREEN_HEIGHT / 2 - 120 + 240 - 40, radius = CHESS_Radius * 2;
    if ((posx - x) * (posx - x) + (posy - y) * (posy - y) <= radius * radius) {
        return true;
    }
    return false;
}

void mytest() {
    draw_match();
    fb_update();
}

