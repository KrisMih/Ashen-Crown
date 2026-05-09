#pragma once
#include <vector>

class Item;
class Character;

class Inventory
{
    private:
        std::vector<Item*> items;
        int maxSize;

    public:
        Inventory(int maxSize = 10);

        bool addItem(Item * item);

        void removeItem(int index);

        void useItem(int index, Character& target);

        void getDescription() const;

        Item * getItem(int index) const;

        int getSize() const;

        bool isFull() const;

        ~Inventory();
};