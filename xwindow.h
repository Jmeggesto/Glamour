#include <ncurses.h>

#ifndef XWINDOW_H_   /* Include guard */
#define XWINDOW_H_

namespace Glamour {

	enum window_direction {
		
		NONE = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8,

		DIAGONAL_UPRIGHT = 9,
		DIAGONAL_UPLEFT = 5,
		DIAGONAL_DOWNRIGHT = 10,
		DIAGONAL_DOWNLEFT = 6

	};

	const char* windirstr(enum window_direction direction);

	class XWindow {
	public:

		XWindow();
		~XWindow();

		WINDOW* win = nullptr;

		double x;
		double y;

		int height;
		int width;

		// cardinal direction and speed along
		// that direction of motion 
		enum window_direction direction;
		int speed;

		// representations of speed along the 
		// x and y axis, respectively
		double vel_x;
		double vel_y;

		int standardBox(); // boxes the window with standard lines
		int makebox(chtype verch, chtype horch); // boxes the window with custom characters/flags

		int translate(double x, double y);
		int moveWindow(enum window_direction dir, int value);
		int moveWindow(int newx, int newy);

		int clear();
		int refresh();

		int addString(const char *string);
		int addNstring(const char *str, int n);

		int addStringAt(int y, int x, const char *str);
        int addNStringAt(int x, int y, const char *str, int n);

    private:

    	// moves and refreshes `win`. Used in 
    	// all public move functions.
    	int curses_mvwin(int newx, int newy);

	};
}

#endif // XWINDOW_H_