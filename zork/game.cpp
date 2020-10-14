#include<ctime>
#include<iostream>
#include<unordered_set>

#include "game.h"
#include "eventmanager.h"
#include "room.h"
#include "item.h"
#include "character.h"

//commands
#include "golistener.h"
#include "maplistener.h"
#include "infolistener.h"
#include "restartlistener.h"
#include "teleportlistener.h"
#include "exitlistener.h"
#include "attacklistener.h"

//state changes
#include "characterdeathlistener.h"
#include "enterroomlistener.h"
#include "victorylistener.h"
#include "defeatlistener.h"
#include "takelistener.h"
#include "damagelistener.h"
#include "hintlistener.h"


/*
 *
 *1. Destructors -> game.cpp /h
 *               -> character.cpp /h
 *               -> room.cpp /h
 *               -> eventmanager.cpp /h
 *
 *2. Inheritance (including virtual methods) and cascading constructors
 *               -> enemy.h inherits character.h, virtual methods in character.h
 *               -> character.cpp
 *               -> enemy.cpp
 *
 *3. Templates -> game.h
 *
 *4. Unary operator overloading ->character.h, can be seen in use in game.cpp
 *
 *5. Binary operator overloading ->character.h, can be seen in use in game.cpp
 *
 *6. Friends -> character.h, game is friend, can be seen in use in game.cpp (player.health etc.)
 *
 *7. Virtual functions and polymorphism-> character.h, seen in use in game.cpp
 *
 *8. Abstract classes and pure virtual functions ->abstract.h and derived.h, used in game.cpp
 *
 *9. Initializer list-> character.cpp
 *
 *10. Dynamic and static dispatch -> game.cpp x2 ->for virtual function and for overriden function
 *
 */

/****************Initializer list of enemies and character********* **************/
Game::Game() : scorpion("scorpion"), ghoul("ghoul"), player("hero")
{
    srand(time(nullptr));

    // Commands
    EventManager::getInstance().listen("go",        new GoListener(this));
    EventManager::getInstance().listen("map",       new MapListener(this));
    EventManager::getInstance().listen("info",      new InfoListener(this));
    EventManager::getInstance().listen("restart",   new RestartListener(this));
    EventManager::getInstance().listen("teleport",  new TeleportListener(this));
    EventManager::getInstance().listen("exit",      new ExitListener(this));
    EventManager::getInstance().listen("take",      new TakeListener(this)); //Take
    EventManager::getInstance().listen("hint",      new HintListener(this)); //hint
    EventManager::getInstance().listen("attack",    new AttackListener(this)); //Attack

    // State changes
    EventManager::getInstance().listen("characterDeath", new CharacterDeathListener(this));
    EventManager::getInstance().listen("enterRoom",      new EnterRoomListener(this));
    EventManager::getInstance().listen("victory",        new VictoryListener(this));
    EventManager::getInstance().listen("defeat",         new DefeatListener(this));
    EventManager::getInstance().listen("damage",         new DamageListener(this)); //Damage for Cursed Item

    rooms.push_back(new Room("A",this)); // 0
    rooms.push_back(new Room("B",this)); // 1
    rooms.push_back(new Room("C",this)); // 2
    rooms.push_back(new Room("D",this)); // 3
    rooms.push_back(new Room("E",this)); // 4
    rooms.push_back(new Room("F",this)); // 5
    rooms.push_back(new Room("G",this)); // 6
    rooms.push_back(new Room("H",this)); // 7
    rooms.push_back(new Room("I",this)); // 8
    rooms.push_back(new Room("J",this)); // 9

    //                 N         E         S         W
    rooms[0]->setExits(rooms[4], rooms[2], rooms[7], rooms[1]);
    rooms[1]->setExits(nullptr,  rooms[0], nullptr,  nullptr);
    rooms[2]->setExits(nullptr,  nullptr,  nullptr,  rooms[0]);
    rooms[3]->setExits(nullptr,  rooms[4], nullptr,  nullptr);
    rooms[4]->setExits(nullptr,  rooms[5], rooms[0], rooms[3]);
    rooms[5]->setExits(nullptr,  nullptr,  nullptr,  rooms[4]);
    rooms[6]->setExits(nullptr,  rooms[7], nullptr,  nullptr);
    rooms[7]->setExits(rooms[0], rooms[8], rooms[9], rooms[6]);
    rooms[8]->setExits(nullptr,  nullptr,  nullptr,  rooms[7]);
    rooms[9]->setExits(rooms[7], nullptr,  nullptr,  nullptr);

    rooms[8]->addItemsToRoom(new item("key"));
    rooms[5]->addItemsToRoom(new item("potion"));
    rooms[1]->addItemsToRoom(new item("curseditem"));
    rooms[3]->addItemsToRoom(new item("antidote"));

    reset();
}

/*******1. Destructors******/
Game::~Game(){
   cout << "End game destructor called" << endl;
   for(auto p : rooms){
       delete p; //delete pointers to avoid memory leak
   }
   rooms.clear(); //then we clear vector
}

//take command
void Game::reset(bool show_update)
{
    gameOver = false;

    player.setCurrentRoom(rooms[0]);
    player.setHealth(100);
    player.setStamina(100);

    ghoul.setCurrentRoom(rooms[8]);
    ghoul.setHealth(100);
    ghoul.setDangerLevel("High");

    scorpion.setCurrentRoom(rooms[3]);
    scorpion.setHealth(50);
    scorpion.setStamina(50);
    scorpion.setDangerLevel("Medium");

    player.setRoomCount(0);

    d.hello();

    if (show_update) {
        update_screen();
    }
}

void Game::setOver(bool over)
{
    /*reseting items once game is over*/
    this->gameOver = over;
    if(this->gameOver == true){
        if(player.checkItems("key")){
        player.removeItemFromList("key");
        rooms[8]->addItemsToRoom(new item("key"));
        }
        if(player.checkItems("potion")){
        player.removeItemFromList("potion");
        rooms[5]->addItemsToRoom(new item("potion"));
        }
        if(player.checkItems("curseditem")){
        player.removeItemFromList("curseditem");
        rooms[1]->addItemsToRoom(new item("curseditem"));
        }
    }
}

void Game::map()
{
    cout << "\n______MAP______" << endl;
    cout << "*-" << rooms[3]->printName() << "-" << rooms[4]->printName() << "-" << rooms[5]->printName() << "-*" << endl;
    cout << "* " << "   " << "  |     " << " *" << endl;
    cout << "*-" << rooms[1]->printName() << "-" << rooms[0]->printName() << "-" << rooms[2]->printName() << "-*" << endl;
    cout << "* " << "   " << "  |     " << " *" << endl;
    cout << "*-" << rooms[6]->printName() << "-" << rooms[7]->printName() << "-" << rooms[8]->printName() << "-*" << endl;
    cout << "* " << "   " << "  |     " << " *" << endl;
    cout << "*-" << "    " << rooms[9]->printName() <<"    -*"<< endl;

    /*-D---E---F- *
    *      |      *
    * {B}-(A)--C- *
    *      |      *
    * -G---H--!I! *
    *      |      *
    *     -J-     */
}

void Game::hint(){
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "HINT" << endl;
    cout << "->The key is located in the ghouls lair, you cannot leave the room so long as he is alive.\n";
    cout << "->Once you have the antidote, run for victory to room J!\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void Game::info()
{
    cout << "Available commands:" << endl;
    cout << " - go <direction>"   << endl;
    cout << " - teleport"         << endl;
    cout << " - map"              << endl;
    cout << " - info"             << endl;
    cout << " - take"             << endl;
    cout << " - attack"           << endl;
}

void Game::go(string direction)
{   /**************Friend Character: priv data*****************/
    Room *next = player.currentRoom->getExit(direction);

    //locked room D
    if(next == rooms[3] && player.checkItems("key") == false){  //ADDED
        cout << "\nYou cannot enter room D without a key!";
        player.setStamina(player.stamina+1);
        next = player.currentRoom;
    }else if(next == rooms[3] && player.checkItems("key") == true){
        player.setCurrentRoom(next);
    }

    //Antidote in room D, cannot escape without it
    if(next == rooms[9] && player.checkItems("antidote") == false){
        cout << "You cannot leave without the antidote!";
        player.setStamina(player.stamina+1);
        next = player.currentRoom;
    }else if(next == rooms[9] && player.checkItems("antidote") == true){
        player.setCurrentRoom(next);
    }

    //Ghoul details in room I
    if(ghoul.getHealth() != 0 && (player+ghoul)){
        cout << "\nThe ghoul will not let you leave, you must defeat him and then take the key\n";
        player.setStamina(player.stamina+1);
        EventManager::getInstance().trigger("damage");
        next = ghoul.getCurrentRoom();
    }

    //Adjacent scorpion movement//
    if(scorpion.getHealth() != 0 && scorpion.getStamina() != 0 && next != nullptr && (player.currentRoom != rooms[8] || next == rooms[7])){
        string directions[] = {"north", "east", "south", "west"};
        Room *adjacentRoom = nullptr;
        while(adjacentRoom == nullptr){
            adjacentRoom = scorpion.getCurrentRoom()->getExit(directions[rand()%directions->size()]);
        }
        scorpion.setCurrentRoom(adjacentRoom);
        --scorpion;
    }

    //Player movement//
    if (next != nullptr) {
        player.setCurrentRoom(next);
        roomVisitAttemptIncrement();
        /**4. Unary operator overloading**/
        --player;
        EventManager::getInstance().trigger("enterRoom", next);
    }else{
        cout << "\nYou hit a wall" << endl;
    }

}

void Game::attack(string name){
    if(name == "scorpion"){
       EventManager::getInstance().trigger("attack");
    }else if(name == "ghoul"){
       EventManager::getInstance().trigger("attack");
    }
}

void Game::take(string itemName) //TAKE CREATED
{
    item *itemN = player.currentRoom->takeItem(itemName); //removed from room
    if(itemN != NULL){
        player.addItems(itemN); //added to inventory
        cout << "\nYou have taken: " << itemName << endl;
        if(itemName == "key"){
            cout << "You now possess the key to retrieve the antidote and escape!\n";
        }else if(itemName == "curseditem"){
             cout << "You have received 20 damage" << endl;
             EventManager::getInstance().trigger("damage");
        }else if(itemName == "antidote"){
            cout<< "You have been healed of all injury!";
             player.setHealth(100);
        }
    }else{
        cout << "\n...\n";
    }

}

void Game::teleport()
{
    int selected = rand() % rooms.size();

    if(rooms[selected] != rooms[9]){
        player.setCurrentRoom(rooms[selected]);
        player.setStamina(player.stamina - 50);
        EventManager::getInstance().trigger("enterRoom", rooms[selected]);
    }else{
        player.setCurrentRoom(player.currentRoom);
    }
}

bool Game::is_over()
{
    return gameOver;
}

Character &Game::getPlayer()
{
    return player;
}
Enemy &Game::getScorpion()
{
    return scorpion;
}
Enemy &Game::getGhoul()
{
    return ghoul;
}

void Game::roomVisitAttemptIncrement(){
    for(int i = 1; i <= player.health - player.health+1; i++){
        ++player;
        player.noOfRoomVisitAttempts();
    }
}

/**10. Dynamic and static dispatch**/
void Game::ghoulDetails(){
    p=&ghoul;           //if announcement not virtual in character, would print player info
    p->announcement();
    cout << "Name: " << ghoul.getName() << " HP: " << ghoul.getHealth() << " Danger: " << ghoul.getDangerLevel();
}

void Game::scorpionDetails(){
    p=&scorpion;        //if announcement not virtual in character, would print player info
    p->announcement();
    cout << "Name: " << scorpion.getName() << " HP: " << scorpion.getHealth() << " Stamina: " << scorpion.getStamina() << " Danger: " << scorpion.getDangerLevel();
}

void Game::healthStatus(){
    if(player.health == 100){
        p=&player;
        p->announcement();
    }else if(player.health < 100 && player.health > 20){
        cout << "\nStatus: injured!\n";
    }else if(player.health <= 20){
        cout << "\nStatus: severely injured, only the antidote can save you!\n";
    }
}

void Game::update_screen()
{
    if (!gameOver) {
        Room *currentRoom = player.currentRoom;

        /**10. Dynamic and static dispatch**/
        if((player + scorpion) && scorpion.getHealth() != 0){
            scorpionDetails();
            EventManager::getInstance().trigger("damage");
        }else if((player + scorpion) && scorpion.getHealth() == 0){
            cout << "\nThere is a dead scorpion that you killed laying in this room";
        }

        /**5. Binary operator overloading**/
        if((player + ghoul) && ghoul.getHealth() !=0){
            ghoulDetails();
            EventManager::getInstance().trigger("damage");
        }else if((player + ghoul) && ghoul.getHealth() == 0){
            cout << "\nThere is a dead ghoul that you killed laying in this room";
        }

        cout << endl;

        cout << "Name: " << player.name << " HP: " << player.health << " ST: " << player.stamina << endl;
        cout << "You are in " << currentRoom->getName() << endl;
        cout << player.currentRoom->displayItems() <<endl;

        healthStatus();

        cout << "Exits:";
        if (currentRoom->getExit("north") != nullptr) { cout << " north"; }
        if (currentRoom->getExit("east")  != nullptr) { cout << " east";  }
        if (currentRoom->getExit("south") != nullptr) { cout << " south"; }
        if (currentRoom->getExit("west")  != nullptr) { cout << " west";  }
        cout << "\n*----------------------------------------*" << endl;
        map();

    } else {
        cout << "Type \"restart\" or \"exit\"." << endl;
    }
}
