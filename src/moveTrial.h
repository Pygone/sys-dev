//
// Created by Pygone on 2023/12/20.
//
#pragma once

#include <cmath>

#include "chess.h"
extern player player_;
bool move(const Position& pre_pos, const Position& pos);
bool restore(Chess* chess, Position originPos, Position nxtPos, Chess* nxtChess);
bool move_jiang(const Position& pre_pos, const Position& pos);
bool move_ma(const Position& pre_pos, const Position& pos);
bool move_pao(const Position& pre_pos, const Position& pos);
bool move_shi(const Position& pre_pos, const Position& pos);
bool move_xiang(const Position& pre_pos, const Position& pos);
bool move_ju(const Position& pre_pos, const Position& pos);
bool move_bing(const Position& pre_pos, const Position& pos);



