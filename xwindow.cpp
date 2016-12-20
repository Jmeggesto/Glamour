#include "xwindow.h"
#include <ncurses.h>

namespace glamour {

	///////////////////////
	// RECT IMPLEMENTATION
	//////////////////////

	double Rect::top() {
		return y;
	}
	double Rect::bottom() {
		return y + height;
	}

	double Rect::left() {
		return x;
	}
	double Rect::right(){
		return x + width;
	}

	Rect* RectMake(double x, double y, int width, int height) {
		Rect* r = new Rect();
		r->x = x;
		r->y = y;
		r->width = width;
		r->height = height;
		return r;
	}

	///////////////////////
	// XWINDOW IMPLEMENTATION
	//////////////////////

	// CONSTRUCTORS/DESTRUCTORS

	XWindow::XWindow() {}

	XWindow::XWindow(double x, double y, int width, int height) {
		rect = RectMake(x,y,width,height);
	}

	XWindow::~XWindow() {
		if(win){
			delwin(win);
		}
		if(rect){
			delete rect;
		}
	}

	// SETTERS/GETTERS

	double XWindow::getX() {
		return rect->x;
	}

	double XWindow::getY() {
		return rect->y;
	}

	int XWindow::getWidth() {
		return rect->width;
	}

	int XWindow::getHeight() {
		return rect->height;
	}

	void XWindow::setVelocity(double x, double y) {
		vel_x = x;
		vel_y = y;
	}

	double XWindow::getXVelocity() {
		return vel_x;
	}

	double XWindow::getYVelocity() {
		return vel_y;
	}

	// WINDOW DRAWING/MOVING METHODS

	int XWindow::standardBox() {
		int status;
		status = box(win,0,0);
		return status;
	}

	int XWindow::makebox(chtype verch, chtype horch) {
		int status;
		status = box(win, verch, horch);
		return status;
	}

	int XWindow::curses_mvwin(int newx, int newy) {
		int status;
		status = mvwin(win, newy, newx);
		return status;
	}
	int XWindow::translate(double delta_x, double delta_y) {
		int status;

		rect->x += delta_x;
		rect->y += delta_y;
		status = curses_mvwin((int)rect->x, (int)rect->y);
		return status;
	}

	int XWindow::autoTranslate() {
		return translate(vel_x, vel_y);
	}

	int XWindow::moveWindow(int newx, int newy) {
		int status;
		rect->x = (double)newx;
		rect->y = (double)newy;
		return curses_mvwin(newx,newy);
	}

	// WINDOW UPDATE METHODS

	int XWindow::clear() {
		int status;
		status = werase(win);
		return status;
	}

	int XWindow::refresh() {
		int status;
		status = wnoutrefresh(win);
		return status;
	}

} // namespace glamour