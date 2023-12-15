//
// Created by wyxm on 2023/12/15.
//

#include "controller.h"
extern "C" {
    #include "../common/common.h"
}

extern Chess* chessBoard[10][9];
std::map<std::pair<int,int>, Position> posMap;
std::map<std::pair<int,int>, Button> buttonMap;

Controller::Controller() {
}

Controller::~Controller() {
}

void Controller::init(player myColor_) {
    myColor = myColor_;
    yourTurn = (myColor == player::red);
    current_state = playing;
    hasChoose = hasLanding = false;
    initMap();
}

void Controller::initMap() {
    // 棋子
    int dis = CHESS_Radius * CHESS_Radius;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            std::pair<int, int> res = posConvert({i, j});
            for (int k = -CHESS_Radius; k <= CHESS_Radius; k++) {
                for (int l = -CHESS_Radius; l <= CHESS_Radius; l++) {
                    if (k * k + l * l <= dis) {
                        int x = res.first + k, y = res.second + l;
                        posMap[{x, y}] = {i, j};
                    }
                }
            }
        }
    }
    // 取消键
    for (int x = 75; x <= 125; x ++) {
        for (int y = 50; y <= 190; y ++) {
            buttonMap[{x, y}] = quxiao;
        }
    }
    // 确认键
    for (int x = 75; x <= 125; x ++) {
        for (int y = 230; y <= 370; y++) {
            buttonMap[{x, y}] = queren;
        }
    }
    // 投降键
    for (int x = 75; x <= 125; x ++) {
        for (int y = 410; y <= 550; y++) {
            buttonMap[{x, y}] = touxiang;
        }
    }
}

TouchType Controller::getTouchType(int touch_x, int touch_y, Activity state) {
    if (state == playing) {
        if (posMap.find({touch_x, touch_y}) != posMap.end()) {
            return chess;
        }
        else if (buttonMap.find({touch_x, touch_y}) != buttonMap.end()) {
            return button;
        }
        else {
            return invalid;
        }
    }
    else {
        // TODO
        return invalid;
    }
}

void Controller::do_chess(int touch_x, int touch_y) {
    Position pos = posMap[{touch_x, touch_y}];
    if (chessBoard[pos.x][pos.y] == nullptr) {
        draw_message_prompt("No chess here!");
    }
    else {
        if (hasChoose) {
            if (chessBoard[pos.x][pos.y]->getChessColor() == myColor) { // 更换选中的棋子 & 绘制选中的棋子
                printChess();  // 打印棋盘
                draw_choose(pos, chessBoard[pos.x][pos.y]->getChessType(), chessBoard[pos.x][pos.y]->getChessColor());
                pre_pos = pos;
                fb_update();
            }
            else { // 记录nxt & 绘制落点(要么为空, 要么是对方的棋子)
                printChess();
                draw_choose(pre_pos, chessBoard[pre_pos.x][pre_pos.y]->getChessType(), chessBoard[pre_pos.x][pre_pos.y]->getChessColor());
                draw_landing_point(pos);
                hasLanding = true;
                nxt_pos = pos;
                fb_update();
            }
        }
        else {
            if (chessBoard[pos.x][pos.y]->getChessColor() == myColor) { // 选中棋子 & 绘制选中的棋子
                printChess();
                draw_choose(pos, chessBoard[pos.x][pos.y]->getChessType(), chessBoard[pos.x][pos.y]->getChessColor());
                hasChoose = true;
                pre_pos = pos;
                fb_update();
            }
            else {
                draw_message_prompt("Not your chess!");
            }
        }  
    }
}

void Controller::do_quxiao() { // 貌似不需要取消键
    hasChoose = false;
    printChess();
    fb_update();
}

bool Controller::do_queren() {
    if (hasChoose && hasLanding) {
        hasChoose = false;
        hasLanding = false;
        if ( !chessBoard[pre_pos.x][pre_pos.y]->move(nxt_pos) ) {
            draw_message_prompt("Invalid move!");
            printChess();
            fb_update();
            return false;
        }
        else {
            printChess();
            fb_update();
            return true;
        } 
    }
    else {
        draw_message_prompt("Please choose a chess and a landing point!");
        return false;
    }
}

char* Controller::do_touxiang() {
    return "touxiang";
}

char* Controller::do_touch(int touch_x, int touch_y) {
    if (current_state == playing) {
        TouchType type = getTouchType(touch_x, touch_y, current_state);
        switch (type) {
            case chess:
                do_chess(touch_x, touch_y);
                break;
            case button:
                switch (buttonMap[{touch_x, touch_y}]) {
                    case quxiao:
                        do_quxiao();
                        break;
                    case queren: {
                        bool res = do_queren();
                        if (res) { // 成功走子
                            message.Serialize(pre_pos, nxt_pos);
                            return message.getMessage();
                        }
                        break;
                    }
                    case touxiang:
                        return do_touxiang();
                        break;
                }
                break;
            case invalid:
                draw_message_prompt("Invalid touch!");
                break;
        }
    }
    else {
        exit(0); // 进入over模式 按击任意位置退出
    }
    return NULL;
}