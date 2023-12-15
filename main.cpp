//
// Created by Pygone on 2023/12/14.
//
#include <cstdio>

extern "C" {
#include <common/common.h>
}

#include <src/source.h>

#include "src/chess.h"
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s color\n", argv[0]);
		return 0;
	}
	if (strcmp(argv[1], "red") != 0 && strcmp(argv[1], "black") != 0)
	{
		printf("Invalid color!\n");
		return 0;
	}
	player myColor = strcmp(argv[1], "red") == 0 ? player::red : player::black;
	initChessBoard(myColor);
	bool yourTurn = myColor == player::red ? true : false;
	Position pre_pos{ 0, 0 }, pos{ 0, 0 };
	Message message;
	int bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	if (bluetooth_fd == -1) return 0;
	while (true)
	{
		if (yourTurn)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			pos.x = x;
			pos.y = y;
			if (chessBoard[pre_pos.x][pre_pos.y]->move(pos))
			{
				message.Serialize(pre_pos, pos);
				printChess();
			}
			else
			{
				printf("Invalid move!\n");
				continue;
			}
			myWrite_nonblock(bluetooth_fd, message.getMessage(), strlen(message.getMessage()));
			yourTurn = false;
			result res = checkResult();
			if (res == result::red_win)
			{
				printf("Red win!\n");
				break;
			}
			else if (res == result::black_win)
			{
				printf("Black win!\n");
				break;
			}
			else
			{
				continue;
			}
		}
		else
		{
			myRead_nonblock(bluetooth_fd, message.getMessage(), strlen(message.getMessage()));
			message.Deserialize();
			yourTurn = true;
		}
	}
}
