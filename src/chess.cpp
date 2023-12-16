//
// Created by Pygone on 2023/12/14.
//

#include "chess.h"
#include "show.h"

#include <cmath>
#include <cstdio>
Chess* chessBoard[10][9];

void initChessBoard(player player_)
{
	player other = player_ == player::red ? player::black : player::red;
	chessBoard[0][0] = new ChessJu(player_, { 0, 0 });
	chessBoard[0][1] = new ChessMa(player_, { 0, 1 });
	chessBoard[0][2] = new ChessXiang(player_, { 0, 2 });
	chessBoard[0][1] = new ChessMa(player_, { 0, 1 });
	chessBoard[0][2] = new ChessXiang(player_, { 0, 2 });
	chessBoard[0][3] = new ChessShi(player_, { 0, 3 });
	chessBoard[0][4] = new ChessJiang(player_, { 0, 4 });
	chessBoard[0][5] = new ChessShi(player_, { 0, 5 });
	chessBoard[0][6] = new ChessXiang(player_, { 0, 6 });
	chessBoard[0][7] = new ChessMa(player_, { 0, 7 });
	chessBoard[0][8] = new ChessJu(player_, { 0, 8 });
	chessBoard[2][1] = new ChessPao(player_, { 2, 1 });
	chessBoard[2][7] = new ChessPao(player_, { 2, 7 });
	chessBoard[3][0] = new ChessBing(player_, { 3, 0 });
	chessBoard[3][2] = new ChessBing(player_, { 3, 2 });
	chessBoard[3][4] = new ChessBing(player_, { 3, 4 });
	chessBoard[3][6] = new ChessBing(player_, { 3, 6 });
	chessBoard[3][8] = new ChessBing(player_, { 3, 8 });
	chessBoard[9][0] = new ChessJu(other, { 9, 0 });
	chessBoard[9][1] = new ChessMa(other, { 9, 1 });
	chessBoard[9][2] = new ChessXiang(other, { 9, 2 });
	chessBoard[9][3] = new ChessShi(other, { 9, 3 });
	chessBoard[9][4] = new ChessJiang(other, { 9, 4 });
	chessBoard[9][5] = new ChessShi(other, { 9, 5 });
	chessBoard[9][6] = new ChessXiang(other, { 9, 6 });
	chessBoard[9][7] = new ChessMa(other, { 9, 7 });
	chessBoard[9][8] = new ChessJu(other, { 9, 8 });
	chessBoard[7][1] = new ChessPao(other, { 7, 1 });
	chessBoard[7][7] = new ChessPao(other, { 7, 7 });
	chessBoard[6][0] = new ChessBing(other, { 6, 0 });
	chessBoard[6][2] = new ChessBing(other, { 6, 2 });
	chessBoard[6][4] = new ChessBing(other, { 6, 4 });
	chessBoard[6][6] = new ChessBing(other, { 6, 6 });
	chessBoard[6][8] = new ChessBing(other, { 6, 8 });
}
bool ChessJiang::move(const Position& pos)
{
	if (pos.x > 3 || pos.x < 0 || pos.y < 3 || pos.y > 5) return false;
	if (abs(pos.x - pos_.x) + abs(pos.y - pos_.y) != 1) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->getChessColor() == player_) return false;
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessShi::move(const Position& pos)
{
	if (pos.x > 3 || pos.x < 0 || pos.y < 3 || pos.y > 5) return false;
	if (abs(pos.x - pos_.x) != 1 || abs(pos.y - pos_.y) != 1) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->getChessColor() == player_) return false;
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessXiang::move(const Position& pos)
{
	if (pos.x > 5 || pos.x < 0 || pos.y < 0 || pos.y > 8) return false;
	if (abs(pos.x - pos_.x) != 2 || abs(pos.y - pos_.y) != 2) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->getChessColor() == player_) return false;
	if (chessBoard[(pos.x + pos_.x) / 2][(pos.y + pos_.y) / 2] != nullptr) return false;
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessMa::move(const Position& pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (abs(pos.x - pos_.x) + abs(pos.y - pos_.y) != 3) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->getChessColor() == player_) return false;
	if (abs(pos.x - pos_.x) == 2)
	{
		if (chessBoard[(pos.x + pos_.x) / 2][pos_.y] != nullptr) return false;
	}
	else
	{
		if (chessBoard[pos_.x][(pos.y + pos_.y) / 2] != nullptr) return false;
	}
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessJu::move(const Position& pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (pos.x != pos_.x && pos.y != pos_.y) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->getChessColor() == player_) return false;
	if (pos.x == pos_.x)
	{
		int min = pos_.y < pos.y ? pos_.y : pos.y;
		int max = pos_.y > pos.y ? pos_.y : pos.y;
		for (int i = min + 1; i < max; i++)
		{
			if (chessBoard[pos.x][i] != nullptr) return false;
		}
	}
	else
	{
		int min = pos_.x < pos.x ? pos_.x : pos.x;
		int max = pos_.x > pos.x ? pos_.x : pos.x;
		for (int i = min + 1; i < max; i++)
		{
			if (chessBoard[i][pos.y] != nullptr) return false;
		}
	}
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessPao::move(const Position& pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (pos.x != pos_.x && pos.y != pos_.y) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->getChessColor() == player_) return false;
	if (pos.x == pos_.x)
	{
		int min = pos_.y < pos.y ? pos_.y : pos.y;
		int max = pos_.y > pos.y ? pos_.y : pos.y;
		int count = 0;
		for (int i = min + 1; i < max; i++)
		{
			if (chessBoard[pos.x][i] != nullptr) count++;
		}
		if (count > 1) return false;
	}
	else
	{
		int min = pos_.x < pos.x ? pos_.x : pos.x;
		int max = pos_.x > pos.x ? pos_.x : pos.x;
		int count = 0;
		for (int i = min + 1; i < max; i++)
		{
			if (chessBoard[i][pos.y] != nullptr) count++;
		}
		if (count > 1) return false;
	}
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessBing::move(const Position& pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (abs(pos.x - pos_.x) + abs(pos.y - pos_.y) != 1) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->getChessColor() == player_) return false;
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}

chessType Chess::getChessType() const
{
	return type_;
}
void Chess::setChessType(chessType type)
{
	type_ = type;
}
player Chess::getChessColor() const
{
	return player_;
}
void Chess::setChessColor(player player)
{
	player_ = player;
}

status checkResult()
{
	bool red = false, black = false;
	for (auto& i : chessBoard)
	{
		for (auto& j : i)
		{
			if (j != nullptr && j->getChessType() == chessType::jiang)
			{
				if (j->getChessColor() == player::red) red = true;
				else black = true;
			}
		}
	}
	if (red && black) return status::playing;
	else if (red) return status::redWin;
	else if (black) return status::blackWin;
	else return status::playing;
}
