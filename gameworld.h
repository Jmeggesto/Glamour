#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "window.h"
#include "context.h"

#include <vector>

namespace glamour {

	class GameWorld {

	public:

		GameWorld(Window* scr, Context &context);
		~GameWorld();
		Window* getEntityAt(int xposition, int yposition);
		int projectileHit(Window* window);
		void updateMatrix(Window* entity, int x, int y, int width, int height);

		const char* testfunc();

		int width;
		int height;

	private:

		Window* screen = nullptr;

		std::vector<std::vector<Window*>> worldspace;
		Context& factory;

	};

} // namespace glamour

#endif
