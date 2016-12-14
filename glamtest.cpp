#include "glamour.h"
#include <iostream>
#include <stdlib.h>

#define FRAMERATE 33333

using namespace Glamour;

int framecount;

int getKey();
bool collision(XWindow* win1, XWindow* win2);
enum window_direction directionForWindow(XWindow* window);

int main() {

	int input;

	FrameRateManager FRM = FrameRateManager(60);

	XWindow *mainscreen = nullptr;
	XWindow *window1, *window2 = nullptr;

	int win1y, win1x;

	Context context;

	mainscreen = context.start(BREAK | COLOR | HIDECURSOR | KEYPAD_STDSCR);

	if(!mainscreen) {
		exit(1);
	}

	nodelay(mainscreen->win, TRUE);

	init_pair(1,COLOR_RED,COLOR_BLUE);

	window1 = context.createWin(0,0,10,5);
	window2 = context.createWin(5,5,10,5);

	window1->vel_x = 1.0;
	window1->vel_y = 1.0;

	window2->standardBox();
	window1->standardBox();

	mainscreen->refresh();
	window1->refresh();
	window2->refresh();
	context.update();

	auto condition = [&]() -> bool {
		return true;
	};
	auto gameloop = [&](double delta_time) -> int {

		input = getKey();
		switch(input){
			case 'q':
				return -1;
				break;
			case 'a':
				window1->translate(-window1->vel_x, 0);
				break;
			case 'd':
				window1->translate(window1->vel_x, 0);
				break;
			case 'w':
				window1->moveWindow(UP, 1);
				break;
			case 's':
				window1->moveWindow(DOWN, 1);
				break;
			default:
				break;
		}
		erase();
		window1->clear();
		window1->standardBox();
		window2->standardBox();
		if(collision(window1, window2)){
			return -1;
		}
		printw("Don't let your box touch the other box!");
		mainscreen->refresh();
		window1->refresh();
		window2->refresh();
		context.update();
		return 1;
	};

	FRM.update(gameloop, condition);

	end:

	context.deleteWindow(window1);
	context.end();

	return 0;
}
bool collision(XWindow* win1, XWindow* win2)
{
	if (win1->x < win2->x + win2->width &&
   win1->x + win1->width > win2->x &&
   win1->y < win2->y + win2->height &&
   win1->height + win1->y > win2->y) {
    	return true;
	} else {
		return false;
	}
}

int getKey()
{
	int key;
	key = getch();
	flushinp();
	return key;
}

enum window_direction directionForWindow(XWindow* window)
{

	enum window_direction dir;
	int winx, winy, maxx, maxy;

	winx = window->x;
	winy = window->y;

	maxx = COLS - window->width;
	maxy = LINES - window->height;

	int test;

	if(winx == 0 && winy == 0){
		test = 1;
		dir = RIGHT;
	} else if(winx == maxx && winy == 0) {
		test = 2;
		dir = DOWN;
	} else if(winx == maxx && winy == maxy){
		test = 3;
		dir = LEFT;
	} else if(winx == 0 && winy == maxy){
		test = 4;
		dir = UP;
	} else {
		test = 5;
		dir = window->direction;
	}

	return dir;
}
