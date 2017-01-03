#include "window.h"

#include <stdlib.h>

#include <vector>
#include <memory>

#ifndef CONTEXT_H_
#define CONTEXT_H_

namespace glamour {


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

		std::unique_ptr<Window> stdscreen;

		int flags;

		Window* start(int cflags);
		Window* getstdscr();

		Window* createWin(int x, int y, int width, int height);

		int deleteWindow(Window* window);

		int update();

		int end();

	private:

		std::vector<std::unique_ptr<Window>> windows;
		void* errout();

	};
} // namespace glamour

#endif
