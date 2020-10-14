#include "enemy.h"

/*******Cascading*Constructors*Destructors*****************/
Enemy::Enemy(string name) : Character(name){
    this->name = name;
    //cout << "Enemy Constructor called" << endl;
}

Enemy::~Enemy(){
    //cout << "Enemy Destructor called" << endl;
}

void Enemy::setDangerLevel(string dangerLevel){
    this->dangerLevel = dangerLevel;
}

string Enemy::getName(){
    return name;
}

string Enemy::getDangerLevel(){
    return dangerLevel;
}
