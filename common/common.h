#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

// 旋转方向
typedef enum {
	NONE,
	LEFT,
	RIGHT
}TurnDirection;

// 颜色库
#define COLOR_BROWN	0x8b4513
#define COLOR_WHITE	0xffffff
#define COLOR_BLACK	0x000000
#define COLOR_grey31 0x4f4f4f
#define COLOR_grey41 0x696969
#define COLOR_Bisque1 0xffe4c4
#define COLOR_RED	0xff0000
#define COLOR_Burlywood 0xdeb887
#define COLOR_PeachPuff 0xffdab9
#define COLOR_PeachPuff3 0xcdaf95
#define COLOR_Burlywood3 0xcdaa7d
#define COLOR_Burlywood4 0x8b7355
#define COLOR_NavajoWhite1 0xffdead
#define COLOR_Tan2 0xee9a49	// 棋子底色
#define COLOR_Tan3 0xcd853f // 棋盘底色
#define COLOR_DeepSkyBlue 0x00bfff
#define COLOR_LightSkyBlue 0x87cefa

// 棋局的基本文字颜色
#define CHESS_FONT_COLOR 0xffffff

// 棋子大小设置
#define CHESS_Radius 27
#define CHESS_Ring 22
#define CHESS_FontSize 30
#define CHESS_LandingPoint 5

/*======================== task.c ============================*/
/*所有的时间以毫秒为单位*/
typedef int myTime;
#define MYTIME_DIFF(a, b) ((myTime)(a) - (myTime)(b))

myTime task_get_time(void); /*得到系统当前运行的时间*/

void task_delay(myTime msecs);

typedef void (*Task_Func)(int arg); /*用户的回调函数*/

#define FILE_NUM_MAX    4	/*最多add的文件任务个数*/
#define TIMER_NUM_MAX   4	/*最多add的定时器任务个数*/

/*添加一个文件任务, 当fd可读时, 会自动调用callback函数*/
void task_add_file(int fd, Task_Func callback);

/*增加一个定时器任务, 每隔period时间, 会自动调用callback函数*/
void task_add_timer(myTime period, Task_Func callback);

void task_delete_file(int fd); /*删除文件任务*/
void task_delete_timer(int period); /*删除定时器任务*/
void task_loop(void); /*进入任务循环, 该函数不返回*/

/*非阻塞方式读/写文件, 返回实际读/写的字节数*/
int myRead_nonblock(int fd, void *p, int n);
int myWrite_nonblock(int fd, void *p, int n);

/*======================== image.c ============================*/
#define FB_COLOR(r,g,b)	(0xff000000|(r<<16)|(g<<8)|b)

#define FB_COLOR_RGB_8880	1
#define FB_COLOR_RGBA_8888	2
#define FB_COLOR_ALPHA_8	3

typedef struct {
	int color_type; /* FB_COLOR_XXXX */
	int pixel_w, pixel_h;
	int line_byte;
	char *content; /*4 byte align*/
} fb_image;

fb_image * fb_new_image(int color_type, int w, int h, int line_byte);
void fb_free_image(fb_image *image);

fb_image * fb_read_jpeg_image(char *file);
fb_image * fb_read_png_image(char *file);

/*得到一个图片的子图片,子图片和原图片共享颜色内存*/
fb_image *fb_get_sub_image(fb_image *img, int x, int y, int w, int h);

typedef struct {
	int bytes;	//UTF-8编码所占字节数
	int advance_x; //x方向步进距离
	int left;	//左跨距
	int top;	//上跨距
} fb_font_info;

void font_init(char *font_file);
fb_image * fb_read_font_image(const char *text, int pixel_size, fb_font_info *format);

/*=========================== graphic.c ===============================*/
#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	600

void fb_init(char *dev);
void fb_update(void);

/*lab2*/
void fb_draw_pixel(int x, int y, int color);
void fb_draw_rect(int x, int y, int w, int h, int color);
void fb_draw_border(int x, int y, int w, int h, int color);
void fb_draw_line(int sx, int sy, int dx, int dy, int color);
void fb_draw_bold_line(int sx, int sy, int dx, int dy, int color);

/*lab3*/
void fb_draw_image(int x, int y, fb_image *image, int color);
void fb_draw_text(int x, int y, char *text, int font_size, int color, TurnDirection dir);
void fb_draw_circle(int x, int y, int r, int color);
void fb_draw_ring(int x, int y, int r, int color);
void fb_draw_filled_circle(int x, int y, int r, int color);

/*=========================== input.c ===============================*/
/*lab4*/
#define TOUCH_NO_EVENT	0
#define TOUCH_PRESS	1
#define TOUCH_MOVE	2
#define TOUCH_RELEASE	3
#define TOUCH_ERROR	9
#define FINGER_NUM_MAX	5

int touch_init(char *dev); /*返回touch_fd*/
int touch_read(int touch_fd, int *x, int *y, int *finger);

/*=========================== board.c ===============================*/
/*和硬件平台相关的函数*/
void * board_video_get_addr(void);

/*声音采样格式是 s16/mono, 采样率是3.072MHz */
void board_audio_record(uint16_t *BufAddr, int nsamples);
void board_audio_play(uint16_t *BufAddr, int nsamples);

#endif /* _COMMON_H_ */
