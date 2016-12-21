#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "gameworld.h"
#include <vector>

namespace glamour {

  class EnemyManager {
  public:

    EnemyManager(GameWorld& world, Context& ctxt);
    ~EnemyManager();

    void shoot(XWindow* origin);
    void updateEntities(double delta_time);
    void refreshEntities();

  private:

    GameWorld& gameWorld;
    Context& factory;

    XWindow* projectile = nullptr;

    std::vector<XWindow*> entities;

    Rect* rect = nullptr;

    const int enemy_rows = 5;
    const int enemy_columns = 11;

    const int enemy_width = 6;
    const int enemy_height = 3;
    const int enemy_spacingX = 3;
    const int enemy_spacingY = 1;

    double x_velocity = 2.0;
    
    void calculateProjectile(double dtime);
    bool checkHit();
    void removeEntity(XWindow* entity);

  };


} //namespace glamour

#endif
