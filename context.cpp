#include "context.h"
#include <stdlib.h>

namespace glamour {

	Context::Context() { }

	Context::~Context() {
		windows.clear();
	}

	void* Context::errout() {
		Window* stdscr;
		if(getstdscr()) {
			stdscr = stdscreen.release();
			delete stdscr;
			return nullptr;
		} else {
			return nullptr;
		}
	}

	Window* Context::start(int cflags) {
		int status;

		Window* stdscr = nullptr;
		stdscreen = std::unique_ptr<Window>(new Window());

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
				return (Window *)errout();
			}
		} else {
			if((status = nocbreak()) != OK) {
				return (Window *)errout();
			}
		}
		if(cflags & ECHO) {
			if((status = echo()) != OK) {
				return (Window *)errout();
			}
		} else {
			if((status = noecho()) != OK) {
				
				return (Window *)errout();
			}
		}
		if (cflags & RAW) {
			if((status = raw()) != OK) {
				return (Window *)errout();
			}
		} else {
			if((status = noraw()) != OK) {
				
				return (Window *)errout();
			}
		}
		if (cflags & COLOR) {
			if((status = start_color()) != OK) {
				return (Window *)errout();
			}
		}
		if (cflags & HIDECURSOR) {
			if((status = curs_set(0)) == ERR) {
				return (Window *)errout();
			}				
		}
		if (cflags & KEYPAD_STDSCR) {
			if((status = keypad(stdscr->win, TRUE)) != OK) {
				return (Window *)errout();
			}				
		}		
		return stdscr;
	}

	Window* Context::getstdscr() {
		return stdscreen.get();
	}

	Window* Context::createWin(int x, int y, int width, int height)  {

		Window* newWindow;

		windows.push_back(std::unique_ptr<Window>(new Window(x,y,width,height)));
		newWindow = windows.back().get();

		newWindow->win = newwin(height,width,y,x);
		return newWindow;
	}

	int Context::deleteWindow(Window* window) {
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

		Window* stdscr;
		stdscr = stdscreen.release();
		delete stdscr;
		return endwin();
	}

} // namespace glamour
