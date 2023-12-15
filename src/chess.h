//
// Created by Pygone on 2023/12/14.
//
#pragma once

struct Position
{
	int x;
	int y;
};
enum chessType
{
	jiang,
	shi,
	xiang,
	ma,
	ju,
	pao,
	bing
};
enum player
{
	red,
	black
};
class Chess
{
	protected:
		player player_;

		chessType type_;

	public:
		Position pos_{};
		Chess(player player, chessType type, Position pos): player_(player), type_(type), pos_(pos)
		{
		}
		virtual bool move(Position pos) = 0;
		virtual ~Chess()
		= default;
		chessType getChessType() const;
		void setChessType(chessType type);
		player getChessColor() const;
		void setChessColor(player player);
};
class ChessJiang : public Chess
{
	public:
		ChessJiang(player player, Position pos) : Chess(player, chessType::jiang, pos)
		{
		}
		bool move(Position pos) override;
		~ChessJiang() override
		= default;
};
class ChessShi : public Chess
{
	public:
		ChessShi(player player, Position pos) : Chess(player, chessType::shi, pos)
		{
		}
		bool move(Position pos) override;
		~ChessShi() override
		= default;
};
class ChessXiang : public Chess
{
	public:
		ChessXiang(player player, Position pos) : Chess(player, chessType::xiang, pos)
		{
		}
		bool move(Position pos) override;
		~ChessXiang() override
		= default;
};
class ChessMa : public Chess
{
	public:
		ChessMa(player player, Position pos) : Chess(player, chessType::ma, pos)
		{
		}
		bool move(Position pos) override;
		~ChessMa() override
		= default;
};
class ChessJu : public Chess
{
	public:
		ChessJu(player player, Position pos) : Chess(player, chessType::ju, pos)
		{
		}
		bool move(Position pos) override;
		~ChessJu() override
		= default;
};
class ChessPao : public Chess
{
	public:
		ChessPao(player player, Position pos) : Chess(player, chessType::pao, pos)
		{
		}
		bool move(Position pos) override;
		~ChessPao() override
		= default;
};
class ChessBing : public Chess
{
	public:
		ChessBing(player player, Position pos) : Chess(player, chessType::bing, pos)
		{
		}
		bool move(Position pos) override;
		~ChessBing() override
		= default;
};
extern Chess* chessBoard[10][9];
extern void initChessBoard();
extern void printChessBoard(); //TODO print chess board
