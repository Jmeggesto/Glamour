#include "glamour.h"

#include <unistd.h>

#include <iostream>
#include <stdlib.h>
#include <vector>

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

	glamour::XWindow* player = context.createWin(0,LINES-3,6,3);
	player->standardBox();

	glamour::GameWorld world = glamour::GameWorld(mainscreen, context);
	glamour::EnemyManager manager = glamour::EnemyManager(world, context);

	nodelay(mainscreen->win, TRUE);

	mainscreen->refresh();
	player->refresh();
	manager.refreshEntities();
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
			case 'a':
				player->translate(-80.0 * DeltaTime, 0);
				break;
			case 'd':
				player->translate(80.0 * DeltaTime, 0);
				break;
			case 'e':
				manager.shoot(player);
				break;
			default:
				break;
		}
		mainscreen->clear();
		mainscreen->refresh();
		player->refresh();
		player->standardBox();
		manager.updateEntities(DeltaTime);
		context.update();
		return 1;
	};

	FRM.update(gameloop, condition);

	end:

	fprintf(stderr, "stderr\n");

	context.end();

	return 0;
}


int getKey() {
	int key;
	key = getch();
	flushinp();
	return key;
}
