#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include <iostream>
// EventListener.h
/** Parent class of all listeners. (It is abstract and can't be instantiated) */
class EventListener
{
public:
    // "void *" is a generic pointer to anything!
    // 10x worse than regular pointers in potential problems
    virtual void run(void *args) = 0;
    /*******DESTRUCTOR**********/
    virtual ~EventListener(){
       // std::cout << "Event Listener Destructor Called" << std::endl;
    }
};

#endif // EVENTLISTENER_H
