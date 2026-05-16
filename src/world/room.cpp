#include <iostream>
#include "room.h"
#include "../entities/enemy.h"
#include "shop.h"

Room::Room(const std::string& name, const std::string& description, Enemy* enemy, Shop* shop)
    : name(name), description(description), enemy(enemy), shop(shop)
{

}

void Room::addExit(const std::string& direction, Room* room)
{
    this->exits[direction] = room;
}

void Room::setNPC(const std::string& name, const std::string& dialogue)
{
    this->npcName = name;
    this->npcDialogue = dialogue;
}

Room* Room::getExit(const std::string& direction) const
{
    auto it = this->exits.find(direction);

    if(it != this->exits.end())
    {
        return it->second;
    }

    return nullptr;
}

Enemy* Room::getEnemy() const
{
    return this->enemy;
}

Shop* Room::getShop() const
{
    return this->shop;
}

std::string Room::getName() const
{
    return this->name;
}

std::string Room::getDescription() const
{
    return this->description;
}

bool Room::hasNPC() const
{
    return !this->npcName.empty();
}

bool Room::hasEnemy() const
{
    return this->enemy != nullptr && this->enemy->isAlive();
}

bool Room::hasShop() const
{
    return this->shop != nullptr;
}

void Room::describe() const
{
    std::cout << "\n\033[1;33m═══ " << this->name << " ═══\033[0m\n";
    std::cout << this->description << "\n\n";

    if(this->hasEnemy())
    {
        std::cout << "\033[1;31m[!] " << this->enemy->getName()
                  << " is here!\033[0m\n";
    }

    if(this->hasShop())
    {
        std::cout << "\033[1;32m[S] There is a shop here.\033[0m\n";
    }

    if(this->hasNPC())
    {
        std::cout << "\033[1;36m[N] " << this->npcName << " is here.\033[0m\n";
    }

    std::cout << "\nExits: ";

    if(this->exits.empty())
    {
        std::cout << "none";
    }

    else
    {

        for(auto& exit : this->exits)
        {
            std::cout << "[" << exit.first << "] ";
        }

    }

    std::cout << "\n";
}

void Room::clearEnemy()
{
    delete this->enemy;
    this->enemy = nullptr;
}

Room::~Room()
{
    delete this->enemy;
}