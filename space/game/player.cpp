#include "player.h"

using namespace Space;

Player::Player(const String& name) : mName(name)
{

}

Player::~Player()
{

}

String Player::name() const
{
    return mName;
}
