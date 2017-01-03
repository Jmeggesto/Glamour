#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "gameworld.h"
#include "scoreboard.h"
#include <vector>

namespace glamour {

  class EnemyManager {
  public:

    EnemyManager(GameWorld& world, Context& ctxt, Scoreboard& sboard);
    ~EnemyManager();

    void shoot(Window* origin);
    void updateEntities(double delta_time);
    void refreshEntities();

  private:

    GameWorld& gameWorld;
    Context& factory;
    Scoreboard& board;

    Window* projectile = nullptr;

    std::vector<Window*> entities;

    Rect* rect = nullptr;

    const int enemy_rows = 5;
    const int enemy_columns = 11;

    const int enemy_width = 7;
    const int enemy_height = 3;
    const int enemy_spacingX = 3;
    const int enemy_spacingY = 1;

    double x_velocity = 2.0;
    
    void calculateProjectile(double dtime);
    bool checkHit();
    void removeEntity(Window* entity);

  };


} //namespace glamour

#endif
