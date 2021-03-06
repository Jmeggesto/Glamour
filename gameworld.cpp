#include "gameworld.h"

#include <stdlib.h>

namespace glamour {

	GameWorld::GameWorld(Window* scr, Context& context) : screen(scr), factory(context) {

		width = COLS;
		height = LINES;

		worldspace.resize(width);
		for(int i = 0; i < width; i++){
			worldspace[i] = std::vector<Window*>(height, nullptr);
			worldspace[i].resize(height);
		}

	}
	GameWorld::~GameWorld() {

	}
	Window* GameWorld::getEntityAt(int xposition, int yposition) {
		return worldspace[xposition][yposition];
	}
	int GameWorld::projectileHit(Window* window){

		if(!window) {
			return -1;
		}
		if(window == getEntityAt(window->getX(), window->getY())) {
			updateMatrix(nullptr, window->getX(), window->getY(), window->getWidth(), window->getHeight());
			window->clear();
			factory.deleteWindow(window);
			return 1;
		} else {
			return -1;
		}
	}
	void GameWorld::updateMatrix(Window* entity, int x, int y, int width, int height) {
		
		for(int i = x; (i) < (x + width); i ++) {
			for(int j = y; (j) < (y + height); j++) {
				worldspace[i][j] = entity;
			}
		}
	}
	const char* GameWorld::testfunc() {
		return "hello, world!";
	}

} //
