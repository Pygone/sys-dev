//
// Created by Pygone on 2023/12/14.
//

#include "message.h"
#include "chess.h"
void Message::Serialize(Position pre_pos, Position pos) const
{
	sprintf(message, "%d %d %d %d", pre_pos.x, pre_pos.y, pos.x, pos.y);
}
void Message::Deserialize() const
{
	Position pre_pos{}, pos{};
	sscanf(message, "%d %d %d %d", &pre_pos.x, &pre_pos.y, &pos.x, &pos.y);
	chessBoard[pos.x][pos.y] = chessBoard[pre_pos.x][pre_pos.y];
	chessBoard[pre_pos.x][pre_pos.y] = nullptr;
}
char* Message::getMessage() const
{
	return message;
}
