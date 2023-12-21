//
// Created by Pygone on 2023/12/14.
//

#include "chess.h"

#include <unordered_map>
#include <cstring>

#include "moveTrial.h"
Chess* chessBoard[10][9];
std::unordered_map<player, Chess*> playerMap;
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
	playerMap[player_] = chessBoard[0][4];
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
	playerMap[other] = chessBoard[9][4];
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

/**
 * @brief 判断当前棋局TheColor能否一步吃掉!TheColor的将
 * @return true表示TheColor能吃掉!TheColor的将,false表示TheColor不能吃掉!TheColor的将
*/
bool canWin(player TheColor)
{
	// 判断当前棋局TheColor能否一步吃掉!TheColor的将
	Position otherJiangPos{};
	Chess* otherJiang = nullptr;
	player otherColor = TheColor == player::red ? player::black : player::red;
	otherJiang = playerMap[otherColor];
	otherJiangPos = otherJiang->pos_;
	// 遍历所有自己的棋子,只要有一个棋子能吃掉对方将,则return true
	for (auto& i : chessBoard)
	{
		for (auto& j : i)
		{
			if (j != nullptr && j->getChessColor() == TheColor)
			{
				Chess* orignChess = chessBoard[j->pos_.x][j->pos_.y];
				const Position originPos = j->pos_; // 引用 qwq
				if (move(originPos, otherJiangPos))
				{
					restore(orignChess, originPos, otherJiangPos, otherJiang);
					return true;
				}
			}
		}
	}
	return false;
}

/**
 * @brief 判断当前棋局TheColor是否必赢
 * @return true表示TheColor必赢,false表示TheColor不一定必赢
*/
bool gameOver(player TheColor)
{
	int cnt = 0; // !TheColor能走的类型数量(即考虑困毙)
	for (auto& i : chessBoard)
	{
		for (auto& j : i)
		{
			if (j != nullptr && j->getChessColor() != TheColor)
			{
				Position originPos = j->pos_; // 保存一下原先的位置
				for (int x = 0; x < 10; x++)
				{
					for (int y = 0; y < 9; y++)
					{
						Position nxtPos = { x, y };
						Chess* orignChess = chessBoard[originPos.x][originPos.y];
						Chess* nxtChess = chessBoard[x][y];
						if (move(originPos, nxtPos))
						{
							cnt++; // !TheColor能走的类型数量+1
							// printf("move and not restore\n");
							// printChessCmd();
							bool state = canWin(TheColor);
							if (state)
							{
								// TheColor能吃掉!TheColor的将,则!TheColor不能走这一步,继续判断下一步
								restore(orignChess, originPos, nxtPos, nxtChess);
							}
							else
							{
								// printf("origin_pos: %d %d nxt_pos: %d %d\n", originPos.x, originPos.y, nxtPos.x, nxtPos.y);
								// TheColor不能吃掉!TheColor的将,则!TheColor能走这一步,直接return false
								restore(orignChess, originPos, nxtPos, nxtChess);
								// printf("%d\n",chessBoard[nxtPos.x][nxtPos.y]==nullptr);
								return false;
							}
							// printf("move and restore\n");
							// printChessCmd();
						}
					}
				}
			}
		}
	}
	return true;
}

void printChessCmd() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (chessBoard[i][j] == nullptr) {
				printf("%-8s", " ");
			}
			else {
				char chessBuf[100];
				memset(chessBuf, '\0', sizeof(chessBuf));
				switch (chessBoard[i][j]->getChessType())
				{
				case chessType::bing:
					memcpy(chessBuf, "bing", sizeof("bing"));
					break;
				case chessType::jiang:
					memcpy(chessBuf, "jiang", sizeof("jiang"));
					break;
				case chessType::ma:
					memcpy(chessBuf, "ma", sizeof("ma"));
					break;
				case chessType::pao:
					memcpy(chessBuf, "pao", sizeof("pao"));
					break;
				case chessType::shi:
					memcpy(chessBuf, "shi", sizeof("shi"));
					break;
				case chessType::xiang:
					memcpy(chessBuf, "xiang", sizeof("xiang"));
					break;
				case chessType::ju:
					memcpy(chessBuf, "ju", sizeof("ju"));
					break;
				}
				printf("%-8s", chessBuf);
			}	
		}
		printf("\n");
	}
}
