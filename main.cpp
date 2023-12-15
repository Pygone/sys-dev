//
// Created by Pygone on 2023/12/14.
//
#include <cstdio>

extern "C" {
#include <common/common.h>
}

#include <src/source.h>
#include "src/chess.h"

int bluetooth_fd;
int touch_fd;

Controller ctrler;

void touch_event_cb(int fd)
{
	printf("your click\n");
	if (!ctrler.getYourTurn()) return;

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
			char* ret = ctrler.do_touch(x, y);
			if (ret) {
				printf("%s\n", ret);
				result res = checkResult();
				if (res == result::redWin || res == result::blackWin) {
					printf("Win!\n");
					draw_win();
					ctrler.setOver();
					myWrite_nonblock(bluetooth_fd, (void*)"lose", strlen("lose"));
				}
				else if (strcmp(ret, "touxiang") == 0) {
					printf("touxiang\n");
					draw_lose();
					ctrler.setOver();
					myWrite_nonblock(bluetooth_fd, (void*)"touxiang", strlen("touxiang"));
				}
				else {
					printf("send: %s\n", ret);
					myWrite_nonblock(bluetooth_fd, ret, strlen(ret));
				}
				flag = true;
			}
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
	return;
}

void bluetooth_event_cb(int fd)
{
	if (ctrler.getYourTurn()) return;
	Message msg;
	int n;
	memset(msg.getMessage(), 0, 100);
	n = myRead_nonblock(fd, msg.getMessage(), 100);
	if (n <= 0)
	{
		printf("close bluetooth tty fd\n");
		exit(0);
		return;
	}
	printf("bluetooth_event_cb read: %s\n", msg.getMessage());
	if (strcmp(msg.getMessage(), "touxiang") == 0)
	{
		draw_win();
		ctrler.setOver();
		return;
	}
	else if (strcmp(msg.getMessage(), "lose") == 0)
	{
		draw_lose();
		ctrler.setOver();
		return;
	}
	else {
		msg.Deserialize();
		printChess();
	}
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
	// bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	// if (bluetooth_fd == -1) return 0;
	touch_fd = touch_init("/dev/input/event2");
	if (touch_fd == -1) return 0;
	player myColor_ = strcmp(argv[1], "red") == 0 ? player::red : player::black;
	ctrler.init(myColor_);
	initChessBoard(myColor_);
	initChess();
	task_add_file(touch_fd, touch_event_cb);
	// task_add_file(bluetooth_fd, bluetooth_event_cb);
	task_loop();
	return 0;
}
