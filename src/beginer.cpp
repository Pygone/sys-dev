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
		int ret = myRead_nonblock(fd, Buffer, 1024);
		if (ret > 0)
		{
			sscanf(Buffer, "%d", &num);
			send_or_recv = true;
		}
	}
	if (send_or_recv && rand_num == -1)
	{
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
