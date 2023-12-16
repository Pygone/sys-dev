//
// Created by wyxm on 2023/12/15.
//

#include "controller.h"

#include "beginer.h"

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
		// TODO
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
		hasChoose = false;
		hasLanding = false;
		if (!chessBoard[pre_pos.x][pre_pos.y]->move(nxt_pos))
		{
			draw_message_prompt("Invalid move!");
			printChess();
			fb_update();
			return false;
		}
		else
		{
			printChess();
			draw_message_prompt("");
			fb_update();
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
				break;
			}
			case touxiang:
				return touch_result::touxiang;
				break;
			}
			break;
		case invalid:
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
		return touch_result::invalid;
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
		if (whoFirst(fd) == pairStatus::to_choose)
		{
			current_state = choose_side;
			// draw_choose_side();// TODO: draw choose side
		}
		else if (whoFirst(fd) == pairStatus::to_wait)
		{
			current_state = wait;
			// draw_wait();// TODO: draw wait
		}
	}
	else if (current_state == wait)
	{
		int n = 0;
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
			myColor = player::red;
		}
		else
		{
			myColor = player::black;
		}
		current_state = playing;
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
		message.clearMessage();
		printChess();
		fb_update();
	}
}
void Controller::handleTouch(int fd)
{
	if (current_state == wait || current_state == over || current_state == pairing || (current_state == playing && !
		getYourTurn()))
	{
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
			myWrite_nonblock(fd, message.getMessage(), 100);
			setTurnOff();
		}
		else if (status == touch_result::touxiang)
		{
			myWrite_nonblock(fd, (void*)"touxiang", 100);
			draw_lose();
			setOver();
		}
		else if (status == touch_result::begin)
		{
			// draw_pairing();// TODO: draw pairing
			current_state = pairing;
		}
		else if (status == touch_result::choose_red)
		{
			myWrite_nonblock(fd, (void*)"1", 100);
			myColor = player::red;
			initChessBoard(myColor);
			initChess();
			current_state = playing;
		}
		else if (status == touch_result::choose_black)
		{
			myWrite_nonblock(fd, (void*)"2", 100);
			myColor = player::black;
			initChessBoard(myColor);
			initChess();
			current_state = playing;
		}
		else if (status == touch_result::invalid)
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
