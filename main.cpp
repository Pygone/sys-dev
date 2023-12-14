//
// Created by Pygone on 2023/12/14.
//
#include <cstdio>

extern "C" {
#include <common/common.h>
}

#include <src/bluetooth.h>
#include <src/message.h>

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
				message.Serialize(chessBoard[pre_pos.x][pre_pos.y], pos);
			}
			yourTurn = false;
		}
		else
		{
			scanf("%s", message.message);
			message.Deserialize(chessBoard[pre_pos.x][pre_pos.y], pos);
			chessBoard[pre_pos.x][pre_pos.y]->move(pos);
			yourTurn = true;
		}
	}
}
