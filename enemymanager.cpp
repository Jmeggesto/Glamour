#include "enemymanager.h"
#include <stdlib.h>

namespace glamour {

	EnemyManager::EnemyManager(GameWorld& world, Context& ctxt, Scoreboard& sboard) : gameWorld(world), factory(ctxt), board(sboard) {

		const int rectWidth = (11 * enemy_width) + (10 * enemy_spacingX);
		const int rectHeight = (enemy_height * 5) + (enemy_spacingY * 4);
		const int rectX = (gameWorld.width / 2) - (rectWidth / 2);
		const int rectY = 5;

		rect = RectMake(rectX, rectY, rectWidth, rectHeight);

		for(int i = rectX; i < rectX + rectWidth; i += (enemy_width + enemy_spacingX)) {
			for(int j = rectY; j < rectY + rectHeight; j += (enemy_height + enemy_spacingY)) {
				entities.push_back(factory.createWin(i,j,enemy_width,enemy_height));
				gameWorld.updateMatrix(entities.back(),i,j,enemy_width,enemy_height);
				entities.back()->standardBox();
			}
		}
	}

	EnemyManager::~EnemyManager() {
		entities.clear();
	}

	void EnemyManager::shoot(Window* origin) {
		if(!origin){
			return;
		}
		if(projectile){
			return;
		}
		projectile = factory.createWin(origin->getX() + (origin->getWidth() / 2), origin->getY() - 2,2,2);
		projectile->setVelocity(0, -40.0);
		projectile->standardBox();
		projectile->refresh();
	}

	void EnemyManager::refreshEntities() {
		for(int i = 0; i < entities.size(); i++){
			entities[i]->refresh();
		}
	}

	void EnemyManager::updateEntities(double delta_time) {

		int y_translation = 0;

		if((rect->right() + (x_velocity * delta_time)) > gameWorld.width || (rect->x + (x_velocity * delta_time)) < 0){
			rect->x = (x_velocity > 0) ? gameWorld.width - rect->width : 0;
			x_velocity *= -4.0;
			y_translation = 1;
		} else {
			rect->x += x_velocity * delta_time;
		}
		rect->y += y_translation;

		board.update();
		calculateProjectile(delta_time);

		for(int i = 0; i < entities.size(); i ++ ) {
			entities[i]->clear();
			entities[i]->standardBox();
			gameWorld.updateMatrix(nullptr, entities[i]->getX(),entities[i]->getY(), enemy_width, enemy_height);
			entities[i]->translate(x_velocity * delta_time, y_translation);
			gameWorld.updateMatrix(entities[i], entities[i]->getX(),entities[i]->getY(), enemy_width, enemy_height);
			entities[i]->refresh();
		}

	}
	void EnemyManager::calculateProjectile(double dtime){
		if(projectile) {
			if(projectile->getY() > 0) {
				if(!checkHit()) { 
					projectile->translate(0,projectile->getYVelocity() * dtime); 
					projectile->refresh();
					projectile->standardBox();
				}
			} else {
				factory.deleteWindow(projectile);
				projectile = nullptr;
			}
		}
	}
	bool EnemyManager::checkHit() {

		if(!projectile) {
			return false;
		}

		Window* en = nullptr;

		int p_x = (int)projectile->getX();
		int next_y = ((int)projectile->getY()) + 1;
		en = gameWorld.getEntityAt(p_x, next_y);
		if(en) {
			removeEntity(en);
			projectile->clear();
			factory.deleteWindow(projectile);
			board.increaseScore(100);
			projectile = nullptr;
			return true;
		} else {
			return false;
		}
	}

	void EnemyManager::removeEntity(Window* entity) {
		
		Window* en;

		for(int i = 0; i < entities.size(); i ++) {
			if(entities[i] == entity) {
				en = entities[i];
				gameWorld.updateMatrix(nullptr, en->getX(), en->getY(), en->getWidth(), en->getHeight());
				entities.erase(entities.begin() + i);
				en->clear();
				factory.deleteWindow(en);
			}
		}
	}

} // namespace glamour
