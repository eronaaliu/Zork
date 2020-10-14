#ifndef DERIVED_H
#define DERIVED_H

#include "abstract.h"

using namespace std;

class derived : public abstract
{
public:
    derived();
    void hello() override{
        cout << "Welcome to: " << endl;
        cout<<" ___________ _____  _  __"<< endl;
        cout<<"|___  / __ \\|  __ \\| |/ /"<< endl;
        cout<<"   / / |  | | |__) | ' /"<< endl;
        cout<<"  / /| |  | |  _  /|  <  "<< endl;
        cout<<" / /_| |__| | |\\ \\ | . \\ "<< endl;
        cout<<"/_____\\____/|_| \\_\\|_|\\_\\"<< endl;
         cout << "*Enemies will attack you on sight, be very careful with your spelling, they dont care!" << endl;
         cout << "*A ghoul rests in his lair and a scorpion patrolling the coridors, both will attack you on sight" << endl;
         cout << "*There is an antidote that will replenish your health and save your people!\n*You cannot leave with out it!\n";
         cout << "*This antidote is located in the locked room D, you will need a key\n";
         cout << "Stuck? Type 'hint' for some extra help! " << endl;
    }
};

#endif // DERIVED_H
