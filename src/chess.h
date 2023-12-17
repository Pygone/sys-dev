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
enum class Status
{
	redWin,
	blackWin,
	playing
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
		virtual bool move(const Position& pos) = 0;
		virtual ~Chess()
		= default;
		chessType getChessType() const;
		void setChessType(chessType type);
		player getChessColor() const;
		void setChessColor(player player);
		void restore(const Position& originPos, const Position& nxtPos, Chess* nxtChess); // 恢复
};
class ChessJiang : public Chess
{
	public:
		ChessJiang(player player, Position pos) : Chess(player, chessType::jiang, pos)
		{
		}
		bool move(const Position& pos) override;
		~ChessJiang() override
		= default;
};
class ChessShi : public Chess
{
	public:
		ChessShi(player player, Position pos) : Chess(player, chessType::shi, pos)
		{
		}
		bool move(const Position& pos) override;
		~ChessShi() override
		= default;
};
class ChessXiang : public Chess
{
	public:
		ChessXiang(player player, Position pos) : Chess(player, chessType::xiang, pos)
		{
		}
		bool move(const Position& pos) override;
		~ChessXiang() override
		= default;
};
class ChessMa : public Chess
{
	public:
		ChessMa(player player, Position pos) : Chess(player, chessType::ma, pos)
		{
		}
		bool move(const Position& pos) override;
		~ChessMa() override
		= default;
};
class ChessJu : public Chess
{
	public:
		ChessJu(player player, Position pos) : Chess(player, chessType::ju, pos)
		{
		}
		bool move(const Position& pos) override;
		~ChessJu() override
		= default;
};
class ChessPao : public Chess
{
	public:
		ChessPao(player player, Position pos) : Chess(player, chessType::pao, pos)
		{
		}
		bool move(const Position& pos) override;
		~ChessPao() override
		= default;
};
class ChessBing : public Chess
{
	public:
		ChessBing(player player, Position pos) : Chess(player, chessType::bing, pos)
		{
		}
		bool move(const Position& pos) override;
		~ChessBing() override
		= default;
};
extern Chess* chessBoard[10][9];
extern void initChessBoard(player player_);
extern Status checkResult();
bool gameOver(player TheColor); // TheColor是否必赢
bool canWin(player TheColor);
