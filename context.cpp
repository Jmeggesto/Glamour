#include "context.h"
#include <stdlib.h>

namespace glamour {

	Context::Context() { }

	Context::~Context() {
		windows.clear();
	}

	void* Context::errout() {
		XWindow* stdscr;
		if(getstdscr()) {
			stdscr = stdscreen.release();
			delete stdscr;
			return nullptr;
		} else {
			return nullptr;
		}
	}

	XWindow* Context::start(int cflags) {
		int status;

		XWindow* stdscr = nullptr;
		stdscreen = std::unique_ptr<XWindow>(new XWindow());

		stdscr = stdscreen.get();

		flags = cflags;

		if(!(stdscr->win = initscr()))
		{
			stdscreen.release();
			delete stdscr;
			return nullptr;
		}

		if(cflags & BREAK) {
			if((status = cbreak()) != OK) {
				return (XWindow *)errout();
			}
		} else {
			if((status = nocbreak()) != OK) {
				return (XWindow *)errout();
			}
		}
		if(cflags & ECHO) {
			if((status = echo()) != OK) {
				return (XWindow *)errout();
			}
		} else {
			if((status = noecho()) != OK) {
				
				return (XWindow *)errout();
			}
		}
		if (cflags & RAW) {
			if((status = raw()) != OK) {
				return (XWindow *)errout();
			}
		} else {
			if((status = noraw()) != OK) {
				
				return (XWindow *)errout();
			}
		}
		if (cflags & COLOR) {
			if((status = start_color()) != OK) {
				return (XWindow *)errout();
			}
		}
		if (cflags & HIDECURSOR) {
			if((status = curs_set(0)) == ERR) {
				return (XWindow *)errout();
			}				
		}
		if (cflags & KEYPAD_STDSCR) {
			if((status = keypad(stdscr->win, TRUE)) != OK) {
				return (XWindow *)errout();
			}				
		}		
		return stdscr;
	}

	XWindow* Context::getstdscr() {
		return stdscreen.get();
	}

	XWindow* Context::createWin(int x, int y, int width, int height)  {

		XWindow* newWindow;

		windows.push_back(std::unique_ptr<XWindow>(new XWindow(x,y,width,height)));
		newWindow = windows.back().get();

		newWindow->win = newwin(height,width,y,x);
		return newWindow;
	}

	int Context::deleteWindow(XWindow* window) {
		int status;
		if(window) 
		{
			for(int i = 0; i < windows.size(); i++){
      			if(window == windows[i].get()) {
        			windows.erase(windows.begin() + i);
        			return OK;
      			}
    		}
		} else {
			return ERR;
		}
		return status;
	}

	int Context::update() {
		int status;
		status = doupdate();
		return status;
	}

	int Context::end() {

		XWindow* stdscr;
		stdscr = stdscreen.release();
		delete stdscr;
		return endwin();
	}

} // namespace glamour