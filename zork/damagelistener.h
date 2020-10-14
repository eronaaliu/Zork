#ifndef DAMAGELISTENER_H
#define DAMAGELISTENER_H

#include "eventlistener.h"

// DamageListener.h
class Game;

// A listener for Damage command
class DamageListener : public EventListener
{
public:
    DamageListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};


#endif // DAMAGELISTENER_H
