//
// Created by Pygone on 2023/12/14.
//
#include <cstdio>

extern "C" {
#include <common/common.h>
}

#include <src/source.h>

#include "src/chess.h"
static bool yourTurn = false;
int bluetooth_fd;
int touch_fd;
Message message;
void touch_event_cb(int fd)
{
	if (!yourTurn) return;

	int type, x, y, finger;
	Position pre_pos{}, pos{};
	bool flag = false;
	while (true)
	{
		type = touch_read(fd, &x, &y, &finger);
		switch (type)
		{
		case TOUCH_PRESS:
		{
			scanf("%d %d %d %d", &pre_pos.x, &pre_pos.y, &pos.x, &pos.y);
			if (chessBoard[pre_pos.x][pre_pos.y]->move(pos))
			{
				message.Serialize(pre_pos, pos);
				printChess();
			}
			else printf("Invalid move!\n");
			myWrite_nonblock(bluetooth_fd, message.getMessage(), strlen(message.getMessage()));
			yourTurn = false;
			result res = checkResult();
			if (res == result::redWin)
			{
				printf("Red win!\n");
				exit(0);
			}
			else if (res == result::blackWin)
			{
				printf("Black win!\n");
				exit(0);
			}
			flag = true;
			break;
		}
		case TOUCH_ERROR:
			printf("close touch fd\n");
			task_delete_file(fd);
			close(fd);
			exit(0);
			break;
		default:
			return;
		}
		if (flag) break;
	}
	yourTurn = false;
	return;
}
void bluetooth_event_cb(int fd)
{
	if (yourTurn) return;
	int n;
	memset(message.getMessage(), 0, 100);
	n = myRead_nonblock(fd, message.getMessage(), 100);
	if (n <= 0)
	{
		printf("close bluetooth tty fd\n");
		exit(0);
		return;
	}
	printf("bluetooth_event_cb read: %s\n", message.getMessage());
	yourTurn = true;
	return;
}
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
	fb_init("/dev/fb0");
	font_init("./font.ttc");
	bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	if (bluetooth_fd == -1) return 0;
	touch_fd = touch_init("/dev/input/event2");
	if (touch_fd == -1) return 0;
	player myColor = strcmp(argv[1], "red") == 0 ? player::red : player::black;
	initChessBoard(myColor);
	yourTurn = myColor == player::red ? true : false;
	printChess();
	task_add_file(touch_fd, touch_event_cb);
	task_add_file(bluetooth_fd, bluetooth_event_cb);
	task_loop();
	return 0;
}
