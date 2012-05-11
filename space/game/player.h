#ifndef SPACE_PLAYER_H
#define SPACE_PLAYER_H

#include <core/types.h>

namespace Space {

class Player
{
public:
    Player(const String& name);
    ~Player();
    
    String name() const;
    
private:
    String mName;
};

typedef List<Player>::type PlayerList;

}

#endif // SPACE_PLAYER_H
