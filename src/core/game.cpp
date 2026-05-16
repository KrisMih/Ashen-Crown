#include <iostream>
#include <fstream>
#include <sstream>
#include "game.h"
#include "../entities/classes.h"
#include "../entities/enemy.h"
#include "../world/room.h"
#include "../world/shop.h"
#include "../items/item.h"
#include "../items/inventory.h"


Game::Game()
    : player(nullptr), currentRoom(nullptr), running(false)
{

}

Game::~Game()
{
    delete this->player;

    for(int i = 0; i < this->allRooms.size(); i++)
    {
        delete this->allRooms[i];
    }

}

void Game::buildWorld()
{
    Shop* startShop = new Shop("Merchant's Stall");
    startShop->addItem(new Potion("Health Potion", 20, 30));
    startShop->addItem(new Potion("Large Potion", 50, 80));

    Shop* midShop = new Shop("Blacksmith");
    midShop->addItem(new Sword("Iron Sword", 50, true, 12, 3));
    midShop->addItem(new HeavyArmor("Iron Plate", 80, true, 10));
    midShop->addItem(new Potion("Health Potion", 20, 30));

    Room* start = new Room("Ashenvale Village",
        "A quiet village at the edge of a dark forest.");
    Room* forest = new Room("Dark Forest",
        "Twisted trees block the moonlight.",
        new Goblin());
    Room* clearing = new Room("Forest Clearing",
        "A clearing with an old well. A merchant has set up camp here.",
        nullptr, startShop);
    Room* ruins = new Room("Ancient Ruins",
        "Crumbling stone walls covered in vines.",
        new Skeleton());
    Room* cave = new Room("Mountain Cave",
        "A dark cave reeking of death.",
        new Orc());
    Room* midShopRoom = new Room("Blacksmith's Forge",
        "The heat from the forge warms the room.",
        nullptr, midShop);
    Room* dragonLair  = new Room("Dragon's Lair",
        "Scorched walls and piles of gold.",
        new Dragon());
    Room* throneRoom = new Room("Throne Room",
        "The seat of the Fallen King. Darkness fills the air.",
        new FallenKing());

    start->setNPC("Elder Aldric", "Traveller, beware the forest. The Fallen King's shadow grows.");
    ruins->setNPC("Ghost", "The king was not always evil. Something corrupted him...");

    start->addExit("north", forest);
    start->addExit("east", clearing);
    forest->addExit("south", start);
    forest->addExit("north", ruins);
    clearing->addExit("west", start);
    clearing->addExit("north", cave);
    ruins->addExit("south", forest);
    ruins->addExit("east", cave);
    cave->addExit("south", clearing);
    cave->addExit("west", ruins);
    cave->addExit("north", midShopRoom);
    midShopRoom->addExit("south", cave);
    midShopRoom->addExit("north", dragonLair);
    dragonLair->addExit("south", midShopRoom);
    dragonLair->addExit("north", throneRoom);
    throneRoom->addExit("south", dragonLair);

    this->allRooms.push_back(start);
    this->allRooms.push_back(forest);
    this->allRooms.push_back(clearing);
    this->allRooms.push_back(ruins);
    this->allRooms.push_back(cave);
    this->allRooms.push_back(midShopRoom);
    this->allRooms.push_back(dragonLair);
    this->allRooms.push_back(throneRoom);

    this->currentRoom = start;
}

void Game::start()
{
    std::cout << "\033[1;31m";
    std::cout << "  ___        _                    ____                           \n";
    std::cout << " / _ \\      | |                  / ___|_ __ _____      ___ __  \n";
    std::cout << "| | | |_____| |__   ___ _ __    | |   | '__/ _ \\ \\ /\\ / / '_ \\ \n";
    std::cout << "| |_| |_____| '_ \\ / _ \\ '_ \\   | |___| | | (_) \\ V  V /| | | |\n";
    std::cout << " \\__\\_\\     |_| |_|\\___/_| |_|   \\____|_|  \\___/ \\_/\\_/ |_| |_|\n";
    std::cout << "\033[0m\n";
    std::cout << "\033[1;33m          ~ Ashen Crown ~\033[0m\n\n";

    int choice = 0;
    std::cout << "  1. New Game\n";
    std::cout << "  2. Load Game\n";
    std::cout << "  3. Quit\n";
    std::cout << "> ";
    std::cin >> choice;

    if(choice == 1)
    {
        std::string name;
        std::cout << "\nEnter your name: ";
        std::cin >> name;
        int classChoice = 0;
        std::cout << "\nChoose your class:\n";
        std::cout << "  1. Warrior (HP: 120 | ATK: 15 | DEF: 10 | MP: 20)\n";
        std::cout << "  2. Mage    (HP: 80  | ATK: 8  | DEF: 5  | MP: 80)\n";
        std::cout << "  3. Rogue   (HP: 90  | ATK: 12 | DEF: 7  | MP: 50)\n";
        std::cout << "> ";
        std::cin >> classChoice;

        if(classChoice == 1)
        {
            this->player = new Warrior(name);
        }

        else if(classChoice == 2)
        {
            this->player = new Mage(name);
        }

        else
        {
            this->player = new Rogue(name);
        } 

        this->player->initInventory();
        this->buildWorld();
        this->run();
    }

    else if(choice == 2)
    {

        if(!this->load())
        {
            std::cout << "No save file found!\n";
            this->start();
        }
        
        else
        {
            this->run();
        }

    }

    else
    {
        std::cout << "Goodbye!\n";
    }

}

void Game::run()
{
    this->running = true;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(this->running)
    {
        this->currentRoom->describe();
        this->player->displayStatus();

        if(this->currentRoom->hasEnemy())
        {
            Enemy* enemy = this->currentRoom->getEnemy();

            if(enemy->getLevel() >= this->player->getLevel() + 5)
            {
                std::cout << "\n\033[1;31m" << enemy->getName()
                          << " is too powerful! It attacks immediately!\033[0m\n";
                this->combat(this->currentRoom);
            }
        }

        std::cout << "\n> ";
        std::string cmd;
        std::getline(std::cin, cmd);
        this->processCommand(cmd);
    }
}

void Game::processCommand(const std::string& cmd)
{
    if(cmd == "north" || cmd == "south" || cmd == "east" || cmd == "west")
    {
        Room* next = this->currentRoom->getExit(cmd);

        if(next == nullptr)
        {
            std::cout << "You can't go that way!\n";
            return;
        }

        this->currentRoom = next;
    }

    else if(cmd == "fight")
    {

        if(!this->currentRoom->hasEnemy())
        {
            std::cout << "There is no enemy here!\n";
            return;
        }

        this->combat(this->currentRoom);
    }

    else if(cmd == "shop")
    {

        if(!this->currentRoom->hasShop())
        {
            std::cout << "There is no shop here!\n";
            return;
        }

        this->currentRoom->getShop()->open(*this->player);
    }

    else if(cmd == "talk")
    {

        if(!this->currentRoom->hasNPC())
        {
            std::cout << "There is no one to talk to!\n";
            return;
        }

        this->talkToNPC();
    }

    else if(cmd == "inventory")
    {
        this->handleInventory();
    }

    else if(cmd == "stats")
    {
        this->player->showStats();
    }

    else if(cmd == "save")
    {
        this->save();
        std::cout << "Game saved!\n";
    }

    else if(cmd == "quit")
    {
        this->running = false;
    }

    else
    {
        std::cout << "Unknown command. Try: north/south/east/west, fight, shop, talk, inventory, stats, save, quit\n";
    }

}

void Game::talkToNPC()
{
    std::cout << "\n\033[1;36m" << this->currentRoom->getDescription() << "\033[0m\n";
}

void Game::handleInventory()
{
    std::cout << "\n\033[1;33m═══ INVENTORY ═══\033[0m\n";
    this->player->getInventory()->getDescription();

    std::cout << "\n  1. Use item\n";
    std::cout << "  2. Drop item\n";
    std::cout << "  3. Back\n";
    std::cout << "> ";

    int choice = 0;
    std::cin >> choice;

    if(choice == 1)
    {
        std::cout << "Choose item: ";
        int index = 0;
        std::cin >> index;
        this->player->getInventory()->useItem(index - 1, *this->player);
    }

    else if(choice == 2)
    {
        std::cout << "Choose item to drop: ";
        int index = 0;
        std::cin >> index;
        this->player->getInventory()->removeItem(index - 1);
        std::cout << "Item dropped.\n";
    }

}

void Game::combat(Room* room)
{
    Enemy* enemy = room->getEnemy();

    std::cout << "\n\033[1;31m═══ COMBAT ═══\033[0m\n";
    std::cout << "You encounter " << enemy->getName() << "!\n";
    enemy->displayStatus();

    while(this->player->isAlive() && enemy->isAlive())
    {
        std::cout << "\n";
        this->player->displayStatus();
        enemy->displayStatus();

        this->player->processEffects();

        if(!this->player->isAlive())
        {
            break;
        }

        if(this->player->isStunned())
        {
            std::cout << "\033[1;33mYou are stunned and cannot act!\033[0m\n";
        }

        else
        {
            std::cout << "\n  1. Attack\n";
            std::cout << "  2. Skill\n";
            std::cout << "  3. Item\n";
            std::cout << "  4. Flee\n";
            std::cout << "> ";

            int choice = 0;
            std::cin >> choice;

            if(choice == 1)
            {
                this->player->attack(*enemy);
            }

            else if(choice == 2)
            {
                this->player->showSkills();
                std::cout << "Choose skill: ";
                int skillChoice = 0;
                std::cin >> skillChoice;

                try
                {
                    this->player->useSkill(*enemy, skillChoice);
                }

                catch(std::invalid_argument& e)
                {
                    std::cout << e.what() << "\n";
                }

            }

            else if(choice == 3)
            {
                this->handleInventory();
            }

            else if(choice == 4)
            {
                std::cout << "You flee from battle!\n";
                Room* south = this->currentRoom->getExit("south");

                if(south != nullptr)
                {
                    this->currentRoom = south;
                }

                return;
            }

        }

        if(!enemy->isAlive())
        {
            break;
        }

        enemy->processEffects();

        if(!enemy->isAlive())
        {
            break;
        }

        if(enemy->isStunned())
        {
            std::cout << "\033[1;33m" << enemy->getName()
                      << " is stunned and cannot act!\033[0m\n";
        }

        else
        {
            enemy->attack(*this->player);
        }

    }

    if(!this->player->isAlive())
    {
        std::cout << "\n\033[1;31mYou have been defeated...\033[0m\n";
        std::cout << "Game Over.\n";
        this->running = false;
        return;
    }

    if(!enemy->isAlive())
    {
        std::cout << "\n\033[1;32mVictory!\033[0m\n";
        this->player->gainXP(enemy->getXPreward());
        this->player->gainGold(enemy->getGoldReward());

        float roll = (float)(rand() % 100) / 100.0f;

        if(enemy->getDropReward() != nullptr && roll <= enemy->getDropChance())
        {
            std::cout << "\033[1;33m" << enemy->getName() << " dropped "
                      << enemy->getDropReward()->getName() << "!\033[0m\n";
            this->player->getInventory()->addItem(enemy->getDropReward());
        }

        this->player->levelUp();
        room->clearEnemy();
    }

}

void Game::save(const std::string& filename)
{
    std::ofstream file(filename);

    if(!file.is_open())
    {
        std::cout << "Could not save game!\n";
        return;
    }

    file << this->player->getClassName() << "\n";
    file << this->player->getName() << "\n";
    file << this->player->getHP() << "\n";
    file << this->player->getLevel() << "\n";
    file << this->player->getXP() << "\n";
    file << this->player->getGold() << "\n";
    file << this->currentRoom->getName() << "\n";

    file.close();
}

bool Game::load(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file.is_open())
    {
        return false;
    }

    std::string className, name, roomName;
    int HP, level, XP, gold;

    std::getline(file, className);
    std::getline(file, name);
    file >> HP >> level >> XP >> gold;
    file.ignore();
    std::getline(file, roomName);

    file.close();

    if(className == "Warrior")
    {
        this->player = new Warrior(name);
    }
    
    else if(className == "Mage")
    {
        this->player = new Mage(name);
    }

    else
    {
        this->player = new Rogue(name);
    }

    this->player->initInventory();
    this->buildWorld();

    for(int i = 0; i < this->allRooms.size(); i++)
    {

        if(this->allRooms[i]->getName() == roomName)
        {
            this->currentRoom = this->allRooms[i];
            break;
        }

    }

    std::cout << "Game loaded!\n";
    return true;
}