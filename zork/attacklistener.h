#ifndef ATTACKLISTENER_H
#define ATTACKLISTENER_H

#include "eventlistener.h"

// AttackListener.h
class Game;

// A Listener for Attack commans
class AttackListener : public EventListener
{
public:
    AttackListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

#endif // ATTACKLISTENER_H
