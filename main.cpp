//
// Created by Pygone on 2023/12/14.
//
#include <cstdio>
#include "src/chess.h"
int main()
{
	initChessBoard();
	for (auto & i : chessBoard)
	{
		for (auto & j : i) printf("%d ", j == nullptr ? 0 : 1);
		printf("\n");
	}
	return 0;
}
