#include <iostream>
#include "shop.h"
#include "../items/item.h"
#include "../items/inventory.h"
#include "../entities/character.h"

Shop::Shop(const std::string& shopName)
    : shopName(shopName)
{

}

void Shop::addItem(Item* item)
{
    this->stock.push_back(item);
}

void Shop::display() const
{
    std::cout << "\n\033[1;33m═══ " << this->shopName << " ═══\033[0m\n";

    if(this->stock.empty())
    {
        std::cout << "  The shop is empty.\n";
        return;
    }

    for(int i = 0; i < this->stock.size(); i++)
    {
        std::cout << "  " << (i + 1) << ". ";
        this->stock[i]->getDescription();
    }

    std::cout << "\n";
}

void Shop::buy(int index, Character& buyer)
{

    if(index < 1 || index > this->stock.size())
    {
        std::cout << "Invalid item!\n";
        return;
    }

    Item* item = this->stock[index - 1];

    if(!item->isTradeable())
    {
        std::cout << "This item cannot be bought!\n";
        return;
    }

    if(buyer.getGold() < item->getValue())
    {
        std::cout << "Not enough gold! You need "
                  << item->getValue() << "g but have "
                  << buyer.getGold() << "g\n";
        return;
    }

    buyer.spendGold(item->getValue());
    buyer.getInventory()->addItem(item);
    this->stock.erase(this->stock.begin() + (index - 1));

    std::cout << "\033[1;32mYou bought " << item->getName()
              << " for " << item->getValue() << "g!\033[0m\n";
}

void Shop::sell(int inventoryIndex, Character& seller)
{
    Item* item = seller.getInventory()->getItem(inventoryIndex - 1);

    if(item == nullptr)
    {
        std::cout << "Invalid item!\n";
        return;
    }

    if(!item->isTradeable())
    {
        std::cout << "This item cannot be sold!\n";
        return;
    }

    int sellPrice = item->getValue() / 2;
    seller.gainGold(sellPrice);
    seller.getInventory()->removeItem(inventoryIndex - 1);

    std::cout << "\033[1;32mYou sold " << item->getName()
              << " for " << sellPrice << "g!\033[0m\n";
}

void Shop::open(Character& player)
{
    int choice = 0;

    while(true)
    {
        std::cout << "\n\033[1;33m═══ " << this->shopName << " ═══\033[0m\n";
        std::cout << "Gold: \033[1;33m" << player.getGold() << "g\033[0m\n\n";
        std::cout << "  1. Buy\n";
        std::cout << "  2. Sell\n";
        std::cout << "  3. Leave\n";
        std::cout << "> ";
        std::cin >> choice;

        if(choice == 1)
        {
            this->display();
            std::cout << "Choose item (0 to cancel): ";
            int itemChoice = 0;
            std::cin >> itemChoice;

            if(itemChoice != 0)
            {
                this->buy(itemChoice, player);
            }

        }

        else if(choice == 2)
        {
            std::cout << "\nYour inventory:\n";
            player.getInventory()->getDescription();
            std::cout << "Choose item to sell (0 to cancel): ";
            int itemChoice = 0;
            std::cin >> itemChoice;

            if(itemChoice != 0)
            {
                this->sell(itemChoice, player);
            }

        }

        else if(choice == 3)
        {
            std::cout << "You leave the shop.\n";
            break;
        }

        else
        {
            std::cout << "Invalid choice!\n";
        }

    }

}

Shop::~Shop()
{

    for(int i = 0; i < this->stock.size(); i++)
    {
        delete this->stock[i];
    }

}