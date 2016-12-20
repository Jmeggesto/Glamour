#include "enemymanager.h"
#include <stdlib.h>

namespace glamour {

	EnemyManager::EnemyManager(GameWorld& world, Context& ctxt) : gameWorld(world), factory(ctxt) {

		const int rectWidth = (11 * enemy_width) + (10 * enemy_spacing);
		const int rectHeight = (enemy_height * 5) + (enemy_spacing * 4);
		const int rectX = (gameWorld.width / 2) - (rectWidth / 2);
		const int rectY = 8;

		rect = RectMake(rectX, rectY, rectWidth, rectHeight);

		for(int i = rectX; i < rectX + rectWidth; i += enemy_spacing) {
			for(int j = rectY; j < rectY + rectHeight; j += enemy_spacing) {
				entities.push_back(factory.createWin(i,j,enemy_width,enemy_height));
				gameWorld.updateMatrix(entities.back(),i,j,enemy_width,enemy_height);
				entities.back()->refresh();
			}
		}

	}

	EnemyManager::~EnemyManager() {
		entities.clear();
	}

	void EnemyManager::updateEntities(double delta_time) {

		int y_translation = 0;

		if((rect->right() + (x_velocity * delta_time)) > gameWorld.width || (rect->x + (x_velocity * delta_time)) < 0){
			rect->x = (x_velocity > 0) ? gameWorld.width - rect->width : 0;
			x_velocity *= -1;
			//y_translation = 1;
		} else {
			rect->x += x_velocity * delta_time;
		}
		rect->y += y_translation;

		for(int i = 0; i < entities.size(); i ++ ) {
			gameWorld.updateMatrix(nullptr, entities[i]->getX(),entities[i]->getY(), enemy_width, enemy_height);
			entities[i]->translate(x_velocity * delta_time, y_translation);
			gameWorld.updateMatrix(entities[i], entities[i]->getX(),entities[i]->getY(), enemy_width, enemy_height);
			entities[i]->refresh();
		}
	}

} // namespace glamour