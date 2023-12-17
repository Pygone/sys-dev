//
// Created by wyxm on 2023/12/15.
//

#include "controller.h"

#include "beginer.h"
const char* win_c = "win";
const char* lose_c = "lose";

extern "C" {
#include "../common/common.h"
}

std::map<std::pair<int, int>, Position> posMap;
std::map<std::pair<int, int>, Button> buttonMap;

Controller::Controller()
{
	current_state = begin;
}

Controller::~Controller()
= default;

void Controller::init(int bluetooth_fd, int touch_fd)
{
	this->bluetooth_fd = bluetooth_fd;
	this->touch_fd = touch_fd;
	initMap();
}

void Controller::initMap()
{
	// 棋子
	int dis = CHESS_Radius * CHESS_Radius;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::pair<int, int> res = posConvert({ i, j });
			for (int k = -CHESS_Radius; k <= CHESS_Radius; k++)
			{
				for (int l = -CHESS_Radius; l <= CHESS_Radius; l++)
				{
					if (k * k + l * l <= dis)
					{
						int x = res.first + k, y = res.second + l;
						posMap[{ x, y }] = { i, j };
					}
				}
			}
		}
	}
	// 取消键
	for (int x = 75; x <= 125; x++)
	{
		for (int y = 50; y <= 190; y++)
		{
			buttonMap[{ x, y }] = quxiao;
		}
	}
	// 确认键
	for (int x = 75; x <= 125; x++)
	{
		for (int y = 230; y <= 370; y++)
		{
			buttonMap[{ x, y }] = queren;
		}
	}
	// 投降键
	for (int x = 75; x <= 125; x++)
	{
		for (int y = 410; y <= 550; y++)
		{
			buttonMap[{ x, y }] = touxiang;
		}
	}
}

TouchType Controller::getTouchType(int touch_x, int touch_y, Activity state)
{
	if (state == playing)
	{
		if (posMap.find({ touch_x, touch_y }) != posMap.end())
		{
			return chess;
		}
		else if (buttonMap.find({ touch_x, touch_y }) != buttonMap.end())
		{
			return button;
		}
		else
		{
			return invalid;
		}
	}
	else if (state == begin)
	{
		return invalid;
	}
	else if (state == choose_side)
	{
		// TODO
		return invalid;
	}
	return invalid;
}

void Controller::do_chess(int touch_x, int touch_y)
{
	Position pos = posMap[{ touch_x, touch_y }];
	if (!hasChoose && chessBoard[pos.x][pos.y] == nullptr)
	{
		draw_message_prompt("No chess here!");
	}
	else
	{
		if (hasChoose)
		{
			if (chessBoard[pos.x][pos.y] != nullptr && chessBoard[pos.x][pos.y]->getChessColor() == myColor)
			{
				printf("switch\n");
				// 更换选中的棋子 & 绘制选中的棋子
				draw_message_prompt("");
				printChess(); // 打印棋盘
				draw_choose(pos, chessBoard[pos.x][pos.y]->getChessType(), chessBoard[pos.x][pos.y]->getChessColor());
				pre_pos = pos;
				hasLanding = false;
				fb_update();
			}
			else
			{
				printf("landing\n");
				// 记录nxt & 绘制落点(要么为空, 要么是对方的棋子)
				draw_message_prompt("");
				printChess();
				draw_choose(pre_pos,
					chessBoard[pre_pos.x][pre_pos.y]->getChessType(),
					chessBoard[pre_pos.x][pre_pos.y]->getChessColor());
				draw_landing_point(pos);
				hasLanding = true;
				nxt_pos = pos;
				fb_update();
			}
		}
		else
		{
			if (chessBoard[pos.x][pos.y]->getChessColor() == myColor)
			{
				printf("choose\n");
				// 选中棋子 & 绘制选中的棋子
				draw_message_prompt("");
				printChess();
				draw_choose(pos, chessBoard[pos.x][pos.y]->getChessType(), chessBoard[pos.x][pos.y]->getChessColor());
				hasChoose = true;
				pre_pos = pos;
				fb_update();
			}
			else
			{
				draw_message_prompt("Not your chess!");
			}
		}
	}
}

void Controller::do_quxiao()
{
	// 貌似不需要取消键
	hasChoose = false;
	hasLanding = false;
	printChess();
	fb_update();
}

bool Controller::do_queren()
{
	if (hasChoose && hasLanding)
	{
		Chess* orignChess = chessBoard[pre_pos.x][pre_pos.y];
		Chess* nxtChess = chessBoard[nxt_pos.x][nxt_pos.y];
		if (!chessBoard[pre_pos.x][pre_pos.y]->move(nxt_pos))
		{
			printChess();
			draw_message_prompt("Invalid move!");
			fb_update();
			return false;
		}
		else
		{
			player otherColor = myColor == player::red ? player::black : player::red;
			if (canWin(otherColor))
			{
				orignChess->restore(pre_pos, nxt_pos, nxtChess);
				printChess();
				draw_message_prompt("invalid move cause game over!");
				return false;
			}
			printf("success move\n");
			printChess();
			draw_message_prompt("");
			return true;
		}
	}
	else
	{
		if (!hasChoose)
		{
			draw_message_prompt("Please choose a chess!");
		}
		else if (!hasLanding)
		{
			draw_message_prompt("No landing point!");
		}
		hasChoose = false;
		hasLanding = false;
		return false;
	}
}

char* Controller::do_touxiang()
{
	touxiangCnt++;
	if (touxiangCnt == 1)
	{
		draw_message_prompt("surrender?");
		fb_update();
		return NULL;
	}
	else if (touxiangCnt == 2)
	{
		current_state = over;
		return "touxiang";
	}
}

touch_result Controller::do_touch(int touch_x, int touch_y)
{
	if (current_state == playing)
	{
		TouchType type = getTouchType(touch_x, touch_y, current_state);
		switch (type)
		{
		case chess:
			do_chess(touch_x, touch_y);
			touxiangCnt = 0;
			break;
		case button:
			switch (buttonMap[{ touch_x, touch_y }])
			{
			case quxiao:
				do_quxiao();
				touxiangCnt = 0;
				break;
			case queren:
			{
				touxiangCnt = 0;
				bool res = do_queren();
				if (res)
				{
					message.Serialize(pre_pos, nxt_pos);
					return touch_result::move_chess;
				}
				return touch_result::invalid;
				break;
			}
			case touxiang:
				return touch_result::touxiang;
				break;
			}
			break;
		case invalid:
			printChess();
			draw_message_prompt("Invalid touch!");
			break;
		}
	}
	else if (current_state == over)
	{
		printf("quit\n");
		fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK);
		fb_update();
		exit(0); // 进入over模式 按击任意位置退出
	}
	else if (current_state == begin)
	{
		if (isClickBegin(touch_x, touch_y))
		{
			return touch_result::begin;
		}
		else
		{
			return touch_result::invalid;
		}
	}
	else if (current_state == choose_side)
	{
		if (isClickChooseRed(touch_x, touch_y))
		{
			return touch_result::choose_red;
		}
		else if (isClickChooseBlack(touch_x, touch_y))
		{
			return touch_result::choose_black;
		}
		else
		{
			return touch_result::invalid;
		}
	}
	else
	{
		return touch_result::invalid;
	}
}

void Controller::handleMessage(int fd)
{
	if (current_state == begin || current_state == choose_side || current_state == over)
	{
		return;
	}
	if (current_state == pairing)
	{
		pairStatus status = whoFirst(fd);
		if (status == pairStatus::to_choose)
		{
			printf("to choose\n");
			current_state = choose_side;
			task_delete_timer(500);
			draw_match_win();
		}
		else if (status == pairStatus::to_wait)
		{
			printf("to wait\n");
			current_state = wait;
			task_delete_timer(500);
			draw_match_lose();
		}
		else
		{
			whoFirst(fd);
		}
	}
	else if (current_state == wait)
	{
		int n = 0;
		printf("wait\n");
		n = myRead_nonblock(fd, message.getMessage(), 100);
		if (n <= 0)
		{
			printf("close bluetooth tty fd\n");
			exit(0);
		}
		int num;
		sscanf(message.getMessage(), "%d", &num);
		if (num == 1)
		{
			printf("your side is red\n");
			myColor = player::red;
			setTurnOn();
		}
		else
		{
			printf("your side is black\n");
			myColor = player::black;
			setTurnOff();
		}
		current_state = playing;
		initChessBoard(myColor);
		initChess();
	}
	else if (current_state == playing)
	{
		int n = 0;
		if (getYourTurn()) return;
		setTurnOn();
		n = myRead_nonblock(fd, message.getMessage(), 100);

		if (n <= 0)
		{
			printf("close bluetooth tty fd\n");
			exit(0);
		}
		printf("read: %s\n", message.getMessage());
		if (strcmp(message.getMessage(), "touxiang") == 0)
		{
			draw_win();
			setOver();
			return;
		}
		if (strcmp(message.getMessage(), "lose") == 0)
		{
			draw_lose();
			setOver();
			return;
		}
		message.Deserialize();
		printChess();
		fb_update();
		player otherColor = myColor == player::red ? player::black : player::red;
		bool isOtherWin = gameOver(otherColor);
		if (isOtherWin)
		{
			// 对方必赢
			draw_lose();
			setOver();
		}
	}
}
void Controller::handleTouch(int fd)
{
	if (current_state == wait || current_state == over || current_state == pairing || (current_state == playing && !
		getYourTurn()))
	{
		if (current_state == over)exit(1);
		return;
	}
	int type, x, y, finger;
	type = touch_read(fd, &x, &y, &finger);
	switch (type)
	{
	case TOUCH_PRESS:
	{
		touch_result status = do_touch(x, y);
		if (status == touch_result::move_chess)
		{
			printf("move chess\n");
			myWrite_nonblock(bluetooth_fd, message.getMessage(), 100);
			setTurnOff();
			bool isWin = gameOver(myColor);
			printf("not over\n");
			if (isWin)
			{
				// 我方必赢
				draw_win();
				setOver();
			}
		}
		else if (status == touch_result::touxiang)
		{
			myWrite_nonblock(bluetooth_fd, (void*)"touxiang", 100);
			draw_lose();
			setOver();
		}
		else if (status == touch_result::begin)
		{
			// draw_pairing();// TODO: draw pairing
			printf("pairing\n");
			task_add_timer(500, pair_stage);
			current_state = pairing;
			whoFirst(bluetooth_fd);
		}
		else if (status == touch_result::choose_red)
		{
			printf("your side is red\n");
			myWrite_nonblock(bluetooth_fd, (void*)"1", 100);
			myColor = player::red;
			initChessBoard(myColor);
			initChess();
			current_state = playing;
			setTurnOn();
		}
		else if (status == touch_result::choose_black)
		{
			printf("your side is black\n");
			myWrite_nonblock(bluetooth_fd, (void*)"2", 100);
			myColor = player::black;
			initChessBoard(myColor);
			initChess();
			current_state = playing;
			setTurnOff();
		}
		else
		{
			// do nothing
		}
		break;
	}
	case TOUCH_ERROR:
		printf("close touch fd\n");
		task_delete_file(fd);
		close(fd);
		break;
	default:
		return;
	}
	fb_update();
}
