//
// Created by wyxm on 2023/12/15.
//
#pragma once

#include "chess.h"
#include <utility>

static int XBaseline = 200;

void draw_chessboard();
void draw_chesspiece(Position pos, chessType type_, player play_);
void draw_chesspiece(int x, int y, chessType type_, player play_);
char* getCharacters(chessType type_, player play_);
std::pair<int, int> posConvert(Position pos);
void draw_choose(Position pos, chessType type_, player play_);
void draw_landing_point(Position pos);
void initChess();
void printChess();
void draw_message_prompt(char* msg);
void draw_win(); // 游戏结束(win)
void draw_lose(); // 游戏结束(lose)
void draw_begin(); // 开始界面
void draw_match(int size); // 匹配界面
void draw_match_win(); // 匹配win(即选边界面)
void draw_match_lose(); // 匹配lose(即等待对方选边界面)

/*************用于被调用************/
bool isClickBegin(int x, int y); // 是否按下开始按钮
bool isClickQuit(int x, int y); // 是否按下退出按钮
bool isClickChooseRed(int x, int y); // 是否按下选红按钮
bool isClickChooseBlack(int x, int y); // 是否按下选黑按钮

void mytest();
void pair_stage(int period);
