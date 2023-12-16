//
// Created by Pygone on 2023/12/14.
//
#include <cstdio>
#include <src/beginer.h>

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
	ctrler.handleTouch(fd);
}

void bluetooth_event_cb(int fd)
{
	ctrler.handleMessage(fd);
}
int main()
{
	fb_init("/dev/fb0");
	font_init("./font.ttc");
	bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	if (bluetooth_fd == -1) return 0;
	touch_fd = touch_init("/dev/input/event2");
	if (touch_fd == -1) return 0;
	draw_begin(); // TODO: draw begin
	printf("begin\n");
	ctrler.init(bluetooth_fd, touch_fd);
	task_add_file(touch_fd, touch_event_cb);
	task_add_file(bluetooth_fd, bluetooth_event_cb);
	task_loop();
	return 0;
}
