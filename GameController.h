#ifndef GameController_h
#define GameController_h

#include "Player.h"
#include "LevelCreator.h"

class GameController {
  public:
    GameController(Player* player,LevelCreator* levelCreator ):player(player), levelCreator(levelCreator) {}

    bool checkCollision() {
      return levelCreator->valueAtPlayer == 1 && player->getMovementState().getLocation() != 1 ;
    }
  private:
    Player* player;
    LevelCreator* levelCreator;
};

#endif
