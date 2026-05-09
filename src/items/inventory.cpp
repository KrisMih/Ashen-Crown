#include <iostream>
#include "inventory.h"
#include "item.h"

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
    
    this->items[index]->use(target);
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