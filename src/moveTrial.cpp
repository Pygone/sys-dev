//
// Created by Pygone on 2023/12/20.
//
#include "moveTrial.h"

#include <algorithm>
player player_;
bool move(const Position& pre_pos, const Position& pos)

{
	if (chessBoard[pre_pos.x][pre_pos.y] == nullptr) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pre_pos.x][pre_pos.y]->getChessColor() == chessBoard[pos.x][
		pos.y]->getChessColor())
		return false;
	chessType type = chessBoard[pre_pos.x][pre_pos.y]->getChessType();
	switch (type)
	{
	case chessType::bing: return move_bing(pre_pos, pos);
	case chessType::jiang: return move_jiang(pre_pos, pos);
	case chessType::ma: return move_ma(pre_pos, pos);
	case chessType::pao: return move_pao(pre_pos, pos);
	case chessType::shi: return move_shi(pre_pos, pos);
	case chessType::xiang: return move_xiang(pre_pos, pos);
	case chessType::ju: return move_ju(pre_pos, pos);
	}
	return false;
}
bool restore(Chess* chess, Position originPos, Position nxtPos, Chess* nxtChess)
{
	chessBoard[originPos.x][originPos.y] = chess;
	chessBoard[nxtPos.x][nxtPos.y] = nxtChess;
	chess->pos_ = originPos;
	return true;
}
bool move_jiang(const Position& pre_pos, const Position& pos)
{
	bool is_our_side = chessBoard[pre_pos.x][pre_pos.y]->getChessColor() == player_;
	if (is_our_side)
	{
		if (pos.x > 3 || pos.x < 0 || pos.y < 3 || pos.y > 5) return false;
	}
	else
	{
		if (pos.x > 9 || pos.x < 7 || pos.y < 3 || pos.y > 5) return false;
	}
	if (abs(pos.x - pre_pos.x) + abs(pos.y - pre_pos.y) != 1) return false;
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
	chessBoard[pos.x][pos.y]->pos_ = pos;
	return true;
}
bool move_shi(const Position& pre_pos, const Position& pos)
{
	bool is_our_side = chessBoard[pre_pos.x][pre_pos.y]->getChessColor() == player_;
	if (is_our_side)
	{
		if (pos.x > 3 || pos.x < 0 || pos.y < 3 || pos.y > 5) return false;
	}
	else
	{
		if (pos.x > 9 || pos.x < 7 || pos.y < 3 || pos.y > 5) return false;
	}
	if (abs(pos.x - pre_pos.x) != 1 || abs(pos.y - pre_pos.y) != 1) return false;
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
	chessBoard[pos.x][pos.y]->pos_ = pos;
	return true;
}
bool move_xiang(const Position& pre_pos, const Position& pos)
{
	bool is_our_side = chessBoard[pre_pos.x][pre_pos.y]->getChessColor() == player_;
	if (is_our_side)
	{
		if (pos.x > 4 || pos.x < 0 || pos.y < 0 || pos.y > 8) return false;
	}
	else
	{
		if (pos.x > 9 || pos.x < 5 || pos.y < 0 || pos.y > 8) return false;
	}
	if (abs(pos.x - pre_pos.x) != 2 || abs(pos.y - pre_pos.y) != 2) return false;
	if (chessBoard[(pos.x + pre_pos.x) / 2][(pos.y + pre_pos.y) / 2] != nullptr) return false;
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
	chessBoard[pos.x][pos.y]->pos_ = pos;
	return true;
}
bool move_ma(const Position& pre_pos, const Position& pos)
{
	if (pos.x > 9 || pos.x < 0 || pos.y < 0 || pos.y > 8) return false;
	if (abs(pos.x - pre_pos.x) + abs(pos.y - pre_pos.y) != 3) return false;
	if (abs(pos.x - pre_pos.x) == 2)
	{
		if (chessBoard[(pos.x + pre_pos.x) / 2][pre_pos.y] != nullptr) return false;
	}
	else
	{
		if (chessBoard[pre_pos.x][(pos.y + pre_pos.y) / 2] != nullptr) return false;
	}
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
	chessBoard[pos.x][pos.y]->pos_ = pos;
	return true;
}

bool move_ju(const Position& pre_pos, const Position& pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (pos.x != pre_pos.x && pos.y != pre_pos.y) return false;
	if (pos.x == pre_pos.x)
	{
		int min_y = std::min(pos.y, pre_pos.y);
		int max_y = std::max(pos.y, pre_pos.y);
		for (int i = min_y + 1; i < max_y; ++i)
		{
			if (chessBoard[pos.x][i] != nullptr) return false;
		}
	}
	else
	{
		int min_x = std::min(pos.x, pre_pos.x);
		int max_x = std::max(pos.x, pre_pos.x);
		for (int i = min_x + 1; i < max_x; ++i)
		{
			if (chessBoard[i][pos.y] != nullptr) return false;
		}
	}
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
	chessBoard[pos.x][pos.y]->pos_ = pos;
	return true;
}

bool move_pao(const Position& pre_pos, const Position& pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (pos.x != pre_pos.x && pos.y != pre_pos.y) return false;
	if (pos.x == pre_pos.x)
	{
		int min_y = std::min(pos.y, pre_pos.y);
		int max_y = std::max(pos.y, pre_pos.y);
		int cnt = 0;
		for (int i = min_y + 1; i < max_y; ++i)
		{
			if (chessBoard[pos.x][i] != nullptr) cnt++;
		}
		if (cnt > 1) return false;
	}
	else
	{
		int min_x = std::min(pos.x, pre_pos.x);
		int max_x = std::max(pos.x, pre_pos.x);
		int cnt = 0;
		for (int i = min_x + 1; i < max_x; ++i)
		{
			if (chessBoard[i][pos.y] != nullptr) cnt++;
		}
		if (cnt > 1) return false;
	}
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
	chessBoard[pos.x][pos.y]->pos_ = pos;
	return true;
}

bool move_bing(const Position& pre_pos, const Position& pos)
{
	bool is_our_side = chessBoard[pre_pos.x][pre_pos.y]->getChessColor() == player_;
	if (is_our_side)
	{
		if (pos.x < 0 || pos.x > 4 || pos.y < 0 || pos.y > 8) return false;
		if (pos.x - pre_pos.x != 1) return false;
	}
	else
	{
		if (pos.x < 5 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
		if (pre_pos.x - pos.x != 1) return false;
	}
	if (abs(pos.y - pre_pos.y) != 1) return false;
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
	chessBoard[pos.x][pos.y]->pos_ = pos;
	return true;
}
