#pragma once
#include <vector>
#include <string>

class Item;
class Character;

class Shop
{
    private:
        std::string shopName;
        std::vector<Item*> stock;

    public:
        Shop(const std::string& shopName);

        void addItem(Item* item);

        void buy(int index, Character& buyer);

        void sell(int inventoryIndex, Character& seller);

        void display() const;

        void open(Character& player);

        ~Shop();
};