#include <iostream>
#include "entity.h"

Entity::Entity(const std::string& name, int HP)
    :name(name), HP(HP), maxHP(HP)
{

}

std::string Entity::getName() const
{
    return this->name;
}

int Entity::getHP() const
{
    return this->HP;
}

int Entity::getMaxHP() const
{
    return this->maxHP;
}

bool Entity::isAlive() const
{
    return this->HP > 0;
}

void Entity::takeDamage(int amount)
{
    this->HP -= amount;

    if(this->HP < 0)
    {
        this->HP = 0;
    }

}

void Entity::heal(int amount)
{
    this->HP += amount;

    if(this->HP > this->maxHP)
    {
        this->HP = this->maxHP;
    }

}

void Entity::displayStatus() const
{
    std::cout << this->name << " — HP: " << this->HP << "/" << this->maxHP << "\n";
}