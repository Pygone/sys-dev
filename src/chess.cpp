//
// Created by Pygone on 2023/12/14.
//

#include "chess.h"

#include <cmath>
Chess* chessBoard[10][9];

void initChessBoard()
{
	chessBoard[0][0] = new ChessJu(player::red, { 0, 0 });
	chessBoard[0][1] = new ChessMa(player::red, { 0, 1 });
	chessBoard[0][2] = new ChessXiang(player::red, { 0, 2 });
	chessBoard[0][3] = new ChessShi(player::red, { 0, 3 });
	chessBoard[0][4] = new ChessJiang(player::red, { 0, 4 });
	chessBoard[0][5] = new ChessShi(player::red, { 0, 5 });
	chessBoard[0][6] = new ChessXiang(player::red, { 0, 6 });
	chessBoard[0][7] = new ChessMa(player::red, { 0, 7 });
	chessBoard[0][8] = new ChessJu(player::red, { 0, 8 });
	chessBoard[2][1] = new ChessPao(player::red, { 2, 1 });
	chessBoard[2][7] = new ChessPao(player::red, { 2, 7 });
	chessBoard[3][0] = new ChessBing(player::red, { 3, 0 });
	chessBoard[3][2] = new ChessBing(player::red, { 3, 2 });
	chessBoard[3][4] = new ChessBing(player::red, { 3, 4 });
	chessBoard[3][6] = new ChessBing(player::red, { 3, 6 });
	chessBoard[3][8] = new ChessBing(player::red, { 3, 8 });
	chessBoard[9][0] = new ChessJu(player::black, { 9, 0 });
	chessBoard[9][1] = new ChessMa(player::black, { 9, 1 });
	chessBoard[9][2] = new ChessXiang(player::black, { 9, 2 });
	chessBoard[9][3] = new ChessShi(player::black, { 9, 3 });
	chessBoard[9][4] = new ChessJiang(player::black, { 9, 4 });
	chessBoard[9][5] = new ChessShi(player::black, { 9, 5 });
	chessBoard[9][6] = new ChessXiang(player::black, { 9, 6 });
	chessBoard[9][7] = new ChessMa(player::black, { 9, 7 });
	chessBoard[9][8] = new ChessJu(player::black, { 9, 8 });
	chessBoard[7][1] = new ChessPao(player::black, { 7, 1 });
	chessBoard[7][7] = new ChessPao(player::black, { 7, 7 });
	chessBoard[6][0] = new ChessBing(player::black, { 6, 0 });
	chessBoard[6][2] = new ChessBing(player::black, { 6, 2 });
	chessBoard[6][4] = new ChessBing(player::black, { 6, 4 });
	chessBoard[6][6] = new ChessBing(player::black, { 6, 6 });
	chessBoard[6][8] = new ChessBing(player::black, { 6, 8 });
}
bool ChessJiang::move(Position pos)
{
	if (pos.x < 7 || pos.x > 9 || pos.y < 3 || pos.y > 5) return false;
	if (abs(pos.x - pos_.x) + abs(pos.y - pos_.y) != 1) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->player_ == player_) return false;
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessShi::move(Position pos)
{
	if (pos.x < 7 || pos.x > 9 || pos.y < 3 || pos.y > 5) return false;
	if (abs(pos.x - pos_.x) != 1 || abs(pos.y - pos_.y) != 1) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->player_ == player_) return false;
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessXiang::move(Position pos)
{
	if (pos.x < 5 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (abs(pos.x - pos_.x) != 2 || abs(pos.y - pos_.y) != 2) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->player_ == player_) return false;
	if (chessBoard[(pos.x + pos_.x) / 2][(pos.y + pos_.y) / 2] != nullptr) return false;
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessMa::move(Position pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (abs(pos.x - pos_.x) + abs(pos.y - pos_.y) != 3) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->player_ == player_) return false;
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
bool ChessJu::move(Position pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (pos.x != pos_.x && pos.y != pos_.y) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->player_ == player_) return false;
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
bool ChessPao::move(Position pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (pos.x != pos_.x && pos.y != pos_.y) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->player_ == player_) return false;
	if (pos.x == pos_.x)
	{
		int min = pos_.y < pos.y ? pos_.y : pos.y;
		int max = pos_.y > pos.y ? pos_.y : pos.y;
		int count = 0;
		for (int i = min + 1; i < max; i++)
		{
			if (chessBoard[pos.x][i] != nullptr) count++;
		}
		if (count != 1) return false;
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
		if (count != 1) return false;
	}
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
bool ChessBing::move(Position pos)
{
	if (pos.x < 0 || pos.x > 9 || pos.y < 0 || pos.y > 8) return false;
	if (abs(pos.x - pos_.x) + abs(pos.y - pos_.y) != 1) return false;
	if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->player_ == player_) return false;
	if (player_ == player::red)
	{
		if (pos.x < pos_.x) return false;
		if (pos_.x < 5 && pos.x == pos_.x) return false;
	}
	else
	{
		if (pos.x > pos_.x) return false;
		if (pos_.x > 4 && pos.x == pos_.x) return false;
	}
	chessBoard[pos.x][pos.y] = this;
	chessBoard[pos_.x][pos_.y] = nullptr;
	pos_ = pos;
	return true;
}
