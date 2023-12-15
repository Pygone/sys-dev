//
// Created by wyxm on 2023/12/15.
//
#pragma once

#include "source.h"
#include "chess.h"
#include <unordered_map>
#include <map>

typedef enum {
    quxiao,
    queren,
    touxiang
}Button;

typedef enum {
    playing,
    over
}Activity;

typedef enum {
    chess,
    button,
    invalid
}TouchType;

extern std::map<std::pair<int,int>, Position> posMap;
extern std::map<std::pair<int,int>, Button> buttonMap;
extern player myColor;

class Controller {
    public:
        Controller();
        ~Controller();
        void init(player myColor_);
        char* do_touch(int touch_x, int touch_y);
        bool getYourTurn() { return yourTurn; }
        void setOver() { current_state = over;}

    private:
        Message message;
        bool yourTurn;
        player myColor;
        Activity current_state;
        bool hasChoose;
        bool hasLanding;
        Position pre_pos;
        Position nxt_pos;

        void initMap();
        TouchType getTouchType(int touch_x, int touch_y, Activity state);
        void do_chess(int touch_x, int touch_y);
        void do_quxiao();
        bool do_queren();
        char* do_touxiang();
};
