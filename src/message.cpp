//
// Created by Pygone on 2023/12/14.
//

#include "message.h"

#include <algorithm>
#include <cstring>
#include <iostream>

#include "chess.h"
Position translate(Position pos)
{
	return { 9 - pos.x, 8 - pos.y };
}
void Message::Serialize(Position pre_pos, Position pos)
{
	clearMessage();
	sprintf(message, "%d %d %d %d", pre_pos.x, pre_pos.y, pos.x, pos.y);
}
void Message::Deserialize() const
{
	Position pre_pos{}, pos{};
	sscanf(message, "%d %d %d %d", &pre_pos.x, &pre_pos.y, &pos.x, &pos.y);
	pre_pos = translate(pre_pos);
	pos = translate(pos);
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pos.x][pos.y]->pos_ = pos;
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
}
char* Message::getMessage() const
{
	return message;
}

Message::Message()
{
	message = new char[100];
}
Message::~Message()
{
	delete[] message;
}
void Message::clearMessage()
{
	memset(message, 0, sizeof(message));
}
