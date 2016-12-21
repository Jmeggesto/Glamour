#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "xwindow.h"
#include "context.h"

#include <vector>

namespace glamour {

	class GameWorld {

	public:

		GameWorld(XWindow* scr, Context &context);
		~GameWorld();
		XWindow* getEntityAt(int xposition, int yposition);
		int projectileHit(XWindow* window);
		void updateMatrix(XWindow* entity, int x, int y, int width, int height);

		const char* testfunc();

		int width;
		int height;

	private:

		XWindow* screen = nullptr;

		std::vector<std::vector<XWindow*>> worldspace;
		Context& factory;

	};

} // namespace glamour

#endif