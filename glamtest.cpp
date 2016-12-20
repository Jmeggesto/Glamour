#include "glamour.h"

#include <iostream>
#include <stdlib.h>

double DeltaTime;

int getKey();

int main() {

	glamour::FrameRateManager FRM = glamour::FrameRateManager(60);
	glamour::Context context;
    
	glamour::XWindow *mainscreen = context.start(glamour::BREAK | 
												 glamour::COLOR | 
												 glamour::HIDECURSOR | 
												 glamour::KEYPAD_STDSCR);

	if(!mainscreen) {
		exit(1);
	}

	glamour::GameWorld world = glamour::GameWorld(mainscreen, context);
	glamour::EnemyManager enemyManager = glamour::EnemyManager(world, context);

	nodelay(mainscreen->win, TRUE);

	mainscreen->refresh();
	context.update();

	auto condition = [&]() -> bool {
		return true;
	};

	int input;

	auto gameloop = [&](double dtime) -> int {

		DeltaTime = dtime;
		input = getKey();
		switch(input){
			case 'q':
				return -1;
				break;
			default:
				break;
		}
		//enemyManager.updateEntities(DeltaTime);
		return 1;
	};

	FRM.update(gameloop, condition);

	end:

	context.end();

	return 0;
}


int getKey() {
	int key;
	key = getch();
	flushinp();
	return key;
}
/*
glamour::XWindow* shoot(glamour::XWindow* origin, glamour::Context& spawner) {
	glamour::XWindow* projectile = nullptr;
	projectile = spawner.createWin(origin->getX() + (origin->getWidth() / 2), origin->getY() - 2,2,2);
	projectile->setVelocity(0, -40.0);
	projectile->standardBox();
	projectiles++;
	return projectile;
}
glamour::XWindow* calculateProjectile(glamour::XWindow* projectile, glamour::Context& deleter) {	
	if(!projectile) {
		return nullptr;
	}
	if(projectile->getY() > 0) {
		projectile->translate(0,projectile->getYVelocity() * DeltaTime);
	} else {
		deleter.deleteWindow(projectile);
		projectile = nullptr;
		projectiles--;
		return nullptr;
	}
	return projectile;
}
*/