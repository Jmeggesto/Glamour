#include "xwindow.h"
#include <stdlib.h>
#include <vector>
#include <memory>

#ifndef CONTEXT_H_
#define CONTEXT_H_

namespace Glamour {


	enum context_flags {

		BREAK = 1,
		ECHO = 2,
		RAW = 4,
		COLOR = 8,
		HIDECURSOR = 16,
		KEYPAD_STDSCR = 32
	};

	class Context {

	public:

		Context();
		~Context();

		std::unique_ptr<XWindow> stdscreen;

		int flags;

		XWindow* start(int cflags);
		XWindow* getstdscr();

		XWindow* createWin(int x, int y, int width, int height);

		int deleteWindow(XWindow* window);

		int update();

		int end();

	private:

		std::vector<std::unique_ptr<XWindow>> windows;

		void* errout();

	};
}

#endif