#include "glamour.h"
#include <iostream>
#include <stdlib.h>

#define FRAMERATE 33333

using namespace Glamour;

int framecount;

int getKey();
int performWindowAnimation(XWindow* window);

enum window_direction directionForWindow(XWindow* window);

int main() {

	int input;

	FrameRateManager FRM = FrameRateManager(60);

	XWindow *mainscreen = nullptr;
	XWindow *window1 = nullptr;

	int win1y, win1x;

	Context context;

	mainscreen = context.start(BREAK | COLOR | HIDECURSOR);

	nodelay(mainscreen->win, TRUE);

	init_pair(1,COLOR_RED,COLOR_BLUE);

	window1 = context.createWin(0,0,10,5);
	window1->vel_x = 1.0;
	window1->vel_y = 2.0;

	window1->makebox(0,0);

	window1->direction = UP;

	mainscreen->refresh();
	window1->refresh();
	context.update();

	auto condition = [&]() -> bool {
		return window1->x < 100;
	};

	auto gameloop = [&](double delta_time) -> int {

		input = getKey();
		switch(input){
			case 'q':
				return -1;
				break;
			default:
				break;
		}

		window1->translate(window1->vel_x * delta_time, 0);
		erase();
		window1->clear();
		window1->makebox(0,0);

		getbegyx(window1->win,win1y,win1x);
		mvwprintw(window1->win,2,2,"%d %d", win1x, win1y);
		mainscreen->refresh();
		window1->refresh();
		context.update();
		return 1;

	};

	FRM.update(gameloop, condition);

	end:

	context.deleteWindow(window1);
	context.end();

	return 0;
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
