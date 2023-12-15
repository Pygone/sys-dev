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
void draw_win();
void draw_lose();

void mytest();