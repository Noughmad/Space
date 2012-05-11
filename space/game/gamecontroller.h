#ifndef SPACE_GAMECONTROLLER_H
#define SPACE_GAMECONTROLLER_H

#include "player.h"

namespace Space {

class GameController
{
public:
    GameController();
    virtual ~GameController();
    
private:
    PlayerList mPlayers;
};

}

#endif // CLASS SPACE_GAMECONTROLLER_H
