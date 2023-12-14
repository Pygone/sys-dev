//
// Created by Pygone on 2023/12/14.
//

#include "bluetooth.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <common/common.h>

int bluetooth_tty_init(const char* dev)
{
	int fd = open(dev, O_RDWR | O_NOCTTY | O_NONBLOCK); /*非阻塞模式*/
	if (fd < 0)
	{
		printf("bluetooth_tty_init open %s error(%d): %s\n", dev, errno, strerror(errno));
		return -1;
	}
	return fd;
}

void bluetooth_tty_event_cb(int fd)
{
	char buf[1024];
	int len = myRead_nonblock(fd, buf, sizeof(buf));
	if (len > 0)
	{
		buf[len] = '\0';
		printf("bluetooth_tty_event_cb read: %s\n", buf);
	}
	else if (len < 0)
	{
		printf("bluetooth_tty_event_cb read error(%d): %s\n", errno, strerror(errno));
	}
	else
	{
		printf("bluetooth_tty_event_cb read EOF\n");
	}
}
