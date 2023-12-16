//
// Created by wyxm on 2023/12/15.
//
#pragma once

#include "source.h"
#include "chess.h"
#include <unordered_map>
#include <map>

typedef enum
{
	quxiao,
	queren,
	touxiang
} Button;

typedef enum
{
	begin,
	// 开始界面
	pairing,
	// 匹配界面
	choose_side,
	// 选边
	wait,
	// 等待对方选边
	playing,
	// 对弈中
	over // 结束
} Activity;

typedef enum
{
	chess,
	button,
	invalid
} TouchType;
enum class touch_result
{
	move_chess,
	touxiang,
	begin,
	choose_red,
	choose_black,
	invalid,
};
extern std::map<std::pair<int, int>, Position> posMap;
extern std::map<std::pair<int, int>, Button> buttonMap;
extern Message message;
class Controller
{
	public:
		Controller();
		~Controller();
		void init(int bluetooth_fd, int touch_fd);
		touch_result do_touch(int touch_x, int touch_y);
		bool getYourTurn() const { return yourTurn; }
		void setBegin() { current_state = begin; }
		void setTurnOn() { yourTurn = true; }
		void setTurnOff() { yourTurn = false; }
		void setPlaying() { current_state = playing; }
		void setOver() { current_state = over; }
		void setWait() { current_state = wait; }
		Activity getState() { return current_state; }
		void handleMessage(int fd);
		void handleTouch(int fd);
		char* get_message() { return message.getMessage(); }

	private:
		Message message;
		bool yourTurn{};
		player myColor;
		Activity current_state;
		bool hasChoose{};
		bool hasLanding{};
		Position pre_pos{};
		Position nxt_pos{};
		int touxiangCnt{};
		int bluetooth_fd{};
		int touch_fd{};

		static void initMap();
		static TouchType getTouchType(int touch_x, int touch_y, Activity state);
		void do_chess(int touch_x, int touch_y);
		void do_quxiao();
		bool do_queren();
		char* do_touxiang();
};
