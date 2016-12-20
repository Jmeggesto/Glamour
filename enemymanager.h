#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "gameworld.h"
#include <vector>

namespace glamour {

  class EnemyManager {
  public:

    EnemyManager(GameWorld& world, Context& ctxt);
    ~EnemyManager();

    void updateEntities(double delta_time);

  private:

    GameWorld& gameWorld;
    Context& factory;

    std::vector<XWindow*> entities;

    Rect* rect = nullptr;

    const int enemy_rows = 5;
    const int enemy_columns = 11;

    const int enemy_width = 8;
    const int enemy_height = 4;
    const int enemy_spacing = 3;

    double x_velocity = 2.0;
    
  };


} //namespace glamour

#endif
