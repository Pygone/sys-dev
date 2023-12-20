//
// Created by Pygone on 2023/12/16.
//

#include "beginer.h"

extern "C" {
#include <common/common.h>
}

bool finsih = false;
char Buffer[1024];
bool send_or_recv = true;
int rand_num = -1, num = -1;
pairStatus whoFirst(int fd)
{
	if (!send_or_recv && num == -1)
	{
		printf("recv\n");
		int ret = myRead_nonblock(fd, Buffer, 1024);
		printf("Buffer :%s", Buffer);
		if (ret > 0)
		{
			sscanf(Buffer, "%d", &num);
			send_or_recv = true;
		}
		else
		{
			send_or_recv = true;
			rand_num = -1;
		}
	}
	if (send_or_recv && rand_num == -1)
	{
		printf("send\n");
		rand_num = rand() % 2;
		sprintf(Buffer, "%d", rand_num);
		myWrite_nonblock(fd, Buffer, strlen(Buffer));
		send_or_recv = false;
	}
	if (rand_num != -1 && num != -1)
	{
		if (rand_num == num)
		{
			rand_num = -1;
			num = -1;
			send_or_recv = true;
		}
		else if (rand_num > num)
		{
			return pairStatus::to_choose;
		}
		else
		{
			return pairStatus::to_wait;
		}
	}
	return pairStatus::none;
}
