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
		void Serialize(Chess* chess, Position pos)
		{
			message = new char[100];
			sprintf(message,
				"%d %d %d %d %d %d",
				chess->player_,
				chess->type_,
				chess->pos_.x,
				chess->pos_.y,
				pos.x,
				pos.y);
		}
		void Deserialize(Chess* chess, Position& pos) const
		{
			sscanf(message,
				"%d %d %d %d %d %d",
				&chess->player_,
				&chess->type_,
				&chess->pos_.x,
				&chess->pos_.y,
				&pos.x,
				&pos.y);
		}
		char* getMessage() const
		{
			return message;
		}
};
