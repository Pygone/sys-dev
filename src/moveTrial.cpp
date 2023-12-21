//
// Created by Pygone on 2023/12/20.
//
#include "moveTrial.h"

#include <algorithm>
player player_;

void movement(const Position& pre_pos, const Position& pos)
{
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
	chessBoard[pos.x][pos.y]->pos_ = pos;
}

bool check_jiang_condition()
{
	Chess* shuai = playerMap[red];
	Chess* jiang = playerMap[black];
	if (jiang->pos_.y == shuai->pos_.y)
	{
		int y = jiang->pos_.y;
		int min_x = std::min(shuai->pos_.x, jiang->pos_.x);
		int max_x = std::max(shuai->pos_.x, jiang->pos_.x);
		bool flag = false;
		for (int i = min_x + 1; i < max_x; ++i)
		{
			if (chessBoard[i][y] != nullptr) flag = true;
		}
		if (!flag) return false;
	}
	return true;
}

bool move(const Position& pre_pos, const Position& pos)
{
	if (chessBoard[pre_pos.x][pre_pos.y] == nullptr) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pre_pos.x][pre_pos.y]->getChessColor() == chessBoard[pos.x][
		pos.y]->getChessColor())
		return false;
	chessType type = chessBoard[pre_pos.x][pre_pos.y]->getChessType();
	Chess* orignChess = chessBoard[pre_pos.x][pre_pos.y];
	Chess* nxtChess = chessBoard[pos.x][pos.y];
	bool res = false;
	switch (type)
	{
	case chessType::bing: res = move_bing(pre_pos, pos);
		break;
	case chessType::jiang: res = move_jiang(pre_pos, pos);
        break;
	case chessType::ma: res = move_ma(pre_pos, pos);
        break;
	case chessType::pao: res = move_pao(pre_pos, pos);
        break;
	case chessType::shi: res = move_shi(pre_pos, pos);
        break;
	case chessType::xiang: res = move_xiang(pre_pos, pos);
        break;
	case chessType::ju: res = move_ju(pre_pos, pos);
        break;
	}
	if (res)
    {
        if (!check_jiang_condition())
        {
            restore(orignChess, pre_pos, pos, nxtChess);
            return false;
        }
        else
        {
            return true;
        }
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
	movement(pre_pos, pos);
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
	movement(pre_pos, pos);
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
	movement(pre_pos, pos);
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
	movement(pre_pos, pos);
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
	movement(pre_pos, pos);
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
		if (chessBoard[pos.x][pos.y] == nullptr && cnt != 0) return false; // 落点为nullptr,则cnt必定为0
		if (chessBoard[pos.x][pos.y] != nullptr && cnt == 0) return false; // 如果落点不为nullptr,则cnt必定为1
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
		if (chessBoard[pos.x][pos.y] == nullptr && cnt != 0) return false; // 落点为nullptr,则cnt必定为0
		if (chessBoard[pos.x][pos.y] != nullptr && cnt == 0) return false; // 如果落点不为nullptr,则cnt必定为1
	}
	movement(pre_pos, pos);
	return true;
}

bool move_bing(const Position& pre_pos, const Position& pos)
{
	bool is_our_side = chessBoard[pre_pos.x][pre_pos.y]->getChessColor() == player_;
	// 位置合法性判断
	if (is_our_side)
	{
		if (pos.x < 0 || pos.x > 4 || pos.y < 0 || pos.y > 8) return false;
	}
	else
	{
		if (pos.x < 5 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	}
	// 移动合法性判断
	if (abs(pre_pos.x - pos.x) + abs(pre_pos.y - pos.y) != 1) return false;
	// 兵过河前后移动规则不同
	if (is_our_side)
	{
		// 过河前只能往前
		if (pre_pos.x < 5 && pos.x - pre_pos.x != 1) return false;
		// 过河后只能往前或者左右
		if (pre_pos.x >= 5 && pos.x - pre_pos.x == -1) return false;
	}
	else
	{
		// 过河前只能往前
		if (pre_pos.x > 4 && pos.x - pre_pos.x != -1) return false;
		// 过河后只能往前或者左右
		if (pre_pos.x <= 4 && pos.x - pre_pos.x == 1) return false;
	}
	movement(pre_pos, pos);
	return true;
}
