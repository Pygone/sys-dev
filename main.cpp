//
// Created by Pygone on 2023/12/14.
//
#include <cstdio>

extern "C" {
#include <common/common.h>
}

#include <src/source.h>

#include "src/chess.h"
int main()
{
	initChessBoard();
	Position pre_pos{ 0, 0 }, pos{ 0, 0 };
	Message message;
	bool yourTurn = true;
	int bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	if (bluetooth_fd == -1) return 0;
	task_add_file(bluetooth_fd, bluetooth_tty_event_cb);
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
			}
			else
			{
				printf("Invalid move!\n");
				continue;
			}
			myWrite_nonblock(bluetooth_fd, message.getMessage(), strlen(message.getMessage()));
			yourTurn = false;
		}
		else
		{
			myRead_nonblock(bluetooth_fd, message.getMessage(), strlen(message.getMessage()));
			message.Deserialize();
			yourTurn = true;
		}
	}
}
