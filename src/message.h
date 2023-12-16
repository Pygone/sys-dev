//
// Created by Pygone on 2023/12/14.
//

#pragma once
#include <cstdio>

#include "chess.h"
class Message
{
	public:
		char* message{};
		Message();
		~Message();
		void Serialize(Position pre_pos, Position pos);
		void Deserialize() const;
		void clearMessage();
		char* getMessage() const;
};
