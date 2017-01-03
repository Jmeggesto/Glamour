#include "window.h"
#include <ncurses.h>

#include <string.h>

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
	// Window IMPLEMENTATION
	//////////////////////

	// CONSTRUCTORS/DESTRUCTORS

	Window::Window() {}

	Window::Window(double x, double y, int width, int height) {
		rect = RectMake(x,y,width,height);
	}

	Window::~Window() {
		if(win){
			delwin(win);
		}
		if(rect){
			delete rect;
		}
	}

	// SETTERS/GETTERS

	double Window::getX() {
		return rect->x;
	}

	double Window::getY() {
		return rect->y;
	}

	int Window::getWidth() {
		return rect->width;
	}

	int Window::getHeight() {
		return rect->height;
	}

	void Window::setVelocity(double x, double y) {
		vel_x = x;
		vel_y = y;
	}

	double Window::getXVelocity() {
		return vel_x;
	}

	double Window::getYVelocity() {
		return vel_y;
	}

	// WINDOW DRAWING/MOVING METHODS

	int Window::standardBox() {
		int status;
		status = box(win,0,0);
		return status;
	}

	int Window::makebox(chtype verch, chtype horch) {
		int status;
		status = box(win, verch, horch);
		return status;
	}

	int Window::curses_mvwin(int newx, int newy) {
		int status;
		status = mvwin(win, newy, newx);
		return status;
	}
	int Window::translate(double delta_x, double delta_y) {
		int status;

		rect->x += delta_x;
		rect->y += delta_y;
		status = curses_mvwin((int)rect->x, (int)rect->y);
		return status;
	}

	int Window::autoTranslate() {
		return translate(vel_x, vel_y);
	}

	int Window::moveWindow(int newx, int newy) {
		int status;
		rect->x = (double)newx;
		rect->y = (double)newy;
		return curses_mvwin(newx,newy);
	}

	// WINDOW UPDATE METHODS

	int Window::clear() {
		int status;
		status = werase(win);
		return status;
	}

	int Window::refresh() {
		int status;
		status = wnoutrefresh(win);
		return status;
	}
	int Window::addString(const char *string){
		int status;
		status = waddstr(win, string);
	}
	int Window::addString(const char *string, enum Justification justify, int ypos){
		int xpos;
		switch(justify){
			case Left:
				xpos = (int)getX() + 1;
				break;
			case Center:
				xpos = (getWidth() / 2) - (strlen(string) / 2);
				break;
			case Right:
				xpos = (getWidth() - strlen(string)) - 1;
				break;
			default:
				break;
		}
		addStringAt(xpos,ypos,string);
	}
	int Window::addStringAt(int x, int y, const char *str){
		mvwaddstr(win,y,x,str);
	}

} // namespace glamour