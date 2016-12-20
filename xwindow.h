#include <ncurses.h>

#ifndef XWINDOW_H_   /* Include guard */
#define XWINDOW_H_

namespace glamour {

  	struct Rect {
    	double x, y;
    	int width, height;

    	// returns y-coord value for top edge
    	double top();

    	// returns y-coord value for bottom edge
    	double bottom();

    	// returns x-coord value for left edge
    	double left();

    	// returns x-coord value for right edge
    	double right();

  	};

  	Rect* RectMake(double x, double y, int width, int height);

	class XWindow {
	public:

		XWindow();
		XWindow(double x, double y, int width, int height);
		~XWindow();

		// the ncurses WINDOW structure that 
		// XWindow provides an API for interacting with.
		WINDOW* win = nullptr;

		double getX();
		double getY();

		int getWidth();
		int getHeight();

		void setVelocity(double x, double y);

		double getXVelocity();
		double getYVelocity();

		// boxes the window with standard lines
		int standardBox(); 

		// boxes the window with custom characters/flags
		int makebox(chtype verch, chtype horch); 

		// floating-point translation with respect to X and Y axes
		int translate(double x, double y); 

		// Continue moving the window 
		// with the direction/magnitude
		// indicated by its x and y velocity
		int autoTranslate();

		//move the window directly to a new coordinate
		int moveWindow(int newx, int newy);

		// clears out the window. 
		// call this before refresh.
		int clear();

		// calls wnoutrefresh on the 
		// window's `win` member. must 
		// be called after any alterations
		// to the window itself.
		int refresh();

		int addString(const char *string);
		int addNstring(const char *str, int n);

		int addStringAt(int y, int x, const char *str);
        int addNStringAt(int x, int y, const char *str, int n);

    private:

    	// moves and refreshes `win`. Used in 
    	// all public move functions.
    	int curses_mvwin(int newx, int newy);
    	Rect* rect = nullptr;

    	double vel_x = 0.0;
    	double vel_y = 0.0;

	};
} // namespace glamour

#endif // XWINDOW_H_
