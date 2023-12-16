//
// Created by Pygone on 2023/12/14.
//

#include "src/source.h"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fcntl.h>

extern "C" {
#include <common/common.h>
}

char buf[1024];
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