#include <iostream>
#include "inventory.h"
#include "item.h"
#include "../entities/character.h"

Inventory::Inventory(int maxSize)
    :maxSize(maxSize)
{
}

bool Inventory::addItem(Item * item)
{
    
    if(this->isFull())
    {
        std::cout << "Inventory is full" << '\n';
        return false;
    }

    this->items.push_back(item);
    return true;
}

void Inventory::removeItem(int index)
{
    delete this->items[index];
    this->items.erase(this->items.begin() + index);
}

void Inventory::useItem(int index, Character& target)
{
    if(index < 0 || index >= this->items.size())
    {
        std::cout << "Invalid index!" << '\n';
        return;
    }

    Item* item = this->items[index];

    Potion* potion = dynamic_cast<Potion*>(item);

    if(potion != nullptr)
    {
        item->use(target);
        delete this->items[index];
        this->items.erase(this->items.begin() + index);
        return;
    }

    Weapon* weapon = dynamic_cast<Weapon*>(item);

    if(weapon != nullptr)
    {
        
        if(weapon->getAllowedClass() != target.getClassName())
        {
            std::cout << "\033[1;31mThis weapon is for " << weapon->getAllowedClass() << " only!\033[0m\n";
            return;
        }

        item->use(target);
        this->items.erase(this->items.begin() + index);
        return;
    }

    Armor* armor = dynamic_cast<Armor*>(item);

    if(armor != nullptr)
    {

        if(armor->getAllowedClass() != target.getClassName())
        {
            std::cout << "\033[1;31mThis armor is for " << armor->getAllowedClass() << " only!\033[0m\n";
            return;
        }

        item->use(target);
        this->items.erase(this->items.begin() + index);
        return;
    }
}

void Inventory::getDescription() const
{

    if(this->items.empty())
    {
        std::cout << "Inventory is empty!\n";
        return;
    }

    for(int i = 0; i < this->items.size(); i++)
    {
        std::cout << i + 1 << ". ";
        this->items[i]->getDescription();
    }

}

Item * Inventory::getItem(int index) const
{
    return this->items[index];
}

int Inventory::getSize() const
{
    return this->items.size();
}

bool Inventory::isFull() const
{
    return this->items.size() >= this->maxSize;
}

Inventory::~Inventory()
{
    
    for(int i = 0; i < this->items.size(); i++)
    {
        delete this->items[i];
    }

}