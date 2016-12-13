#include "xwindow.h"
#include <ncurses.h>

namespace Glamour {

	const char* windirstr(window_direction direction)
	{
		switch(direction){
			case NONE:
				return "None";
				break;
			case UP:
				return "Up";
				break;
			case DOWN:
				return "Down";
				break;			
			case LEFT:
				return "Left";
				break;
			case RIGHT:
				return "Right";
				break;
			case DIAGONAL_UPRIGHT:
				return "Up/Right";
				break;
			case DIAGONAL_UPLEFT:
				return "Up/Left";
				break;
			case DIAGONAL_DOWNRIGHT:
				return "Down/Right";
				break;
			case DIAGONAL_DOWNLEFT:
				return "Down/Left";
				break;
		}
	}

	XWindow::XWindow() {}
	XWindow::~XWindow()
	{
		delwin(win);
	}
	int XWindow::standardBox()
	{
		int status;
		status = box(win,0,0);
		return status;
	}
	int XWindow::makebox(chtype verch, chtype horch) 
	{
		int status;
		status = box(win, verch, horch);
		return status;
	}

	int XWindow::curses_mvwin(int newx, int newy)
	{
		int status;
		status = mvwin(win, newy, newx);
		return status;
	}

	int XWindow::translate(double delta_x, double delta_y)
	{
		int status;

		x += delta_x;
		y += delta_y;

		status = curses_mvwin((int)x, (int)y);
		return status;
	}
	int XWindow::moveWindow(enum window_direction dir, int value)
	{

		int status;
		direction = dir;

		if(direction & UP){
			y -= value;
		}
		if(direction & DOWN){
			y += value;
		}
		if(direction & LEFT){
			x -= value;
		}
		if(direction & RIGHT){
			x += value;
		}
		status = curses_mvwin((int)x,(int)y);
		return status;

	}
	int XWindow::moveWindow(int newx, int newy)
	{
		int status;
		x = newx;
		y = newy;
		if((status = curses_mvwin(x,y)) != OK ){
			int testx, testy;
			getbegyx(win,testy,testx);
			if(testx != x) {
				x = (int)testx;
			}
			if(testy != y){
				y = (int)testy;
			}
			return status;
		}
		return status;
	}

	int XWindow::clear()
	{
		int status;
		status = werase(win);
		return status;
	}
	int XWindow::refresh()
	{
		int status;
		status = wnoutrefresh(win);
		return status;
	}

}