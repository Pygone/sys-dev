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
		Message() = default;
		~Message() = default;
		void Serialize(Position pre_pos, Position pos) const;
		void Deserialize() const;
		char* getMessage() const;
};
