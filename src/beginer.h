//
// Created by Pygone on 2023/12/16.
//
#pragma once
enum class pairStatus
{
	to_choose,
	to_wait,
	none
};
pairStatus whoFirst(int fd);
