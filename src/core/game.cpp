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

    Shop* rogueShop = new Shop("Shady Dealer");
    rogueShop->addItem(new Dagger("Shadow Dagger", 60, true, 14));
    rogueShop->addItem(new MediumArmor("Leather Vest", 70, true, 8));
    rogueShop->addItem(new Potion("Health Potion", 20, 30));

    Shop* mageShop = new Shop("Arcane Library");
    mageShop->addItem(new Staff("Oak Staff", 55, true, 18));
    mageShop->addItem(new LightArmor("Silk Robe", 65, true, 6));
    mageShop->addItem(new Potion("Health Potion", 20, 30));

    Shop* midShop = new Shop("Blacksmith");
    midShop->addItem(new Sword("Iron Sword", 50, true, 12, 3));
    midShop->addItem(new HeavyArmor("Iron Plate", 80, true, 10));
    midShop->addItem(new Dagger("Steel Dagger", 45, true, 10));
    midShop->addItem(new Staff("Battle Staff", 45, true, 12));
    midShop->addItem(new Potion("Health Potion", 20, 30));

    Shop* lateShop = new Shop("Wandering Merchant");
    lateShop->addItem(new Potion("Large Potion", 50, 80));
    lateShop->addItem(new Potion("Mega Potion", 100, 150));
    lateShop->addItem(new Sword("Steel Sword", 120, true, 20, 5));
    lateShop->addItem(new Dagger("Venom Dagger", 110, true, 18));
    lateShop->addItem(new Staff("Crystal Staff", 110, true, 22));

    Room* start         = new Room("Ashenvale Village",
        "A quiet village at the edge of a dark forest.");
    Room* shadyAlley    = new Room("Shady Alley",
        "A dark alley behind the village.",
        nullptr, rogueShop);
    Room* arcaneLibrary = new Room("Arcane Library",
        "Dusty shelves filled with spell books.",
        nullptr, mageShop);
    Room* forest1       = new Room("Dark Forest",
        "Twisted trees block the moonlight.",
        new Goblin());
    Room* clearing      = new Room("Forest Clearing",
        "A clearing with an old well.",
        nullptr, startShop);
    Room* forest2       = new Room("Deep Forest",
        "The trees grow darker and more twisted.",
        new Goblin());
    Room* forest3       = new Room("Haunted Woods",
        "Strange lights flicker between the trees.",
        new Goblin());
    Room* forest4       = new Room("Misty Forest",
        "Thick fog obscures your vision.",
        new Goblin());
    Room* forest5       = new Room("Cursed Grove",
        "The trees here look like twisted faces.",
        new Goblin());
    Room* ruins1        = new Room("Ancient Ruins",
        "Crumbling stone walls covered in vines.",
        new Skeleton());
    Room* graveyard     = new Room("Forgotten Graveyard",
        "Rows of tombstones stretch into the darkness.",
        new Skeleton());
    Room* chapel        = new Room("Ruined Chapel",
        "A desecrated place of worship.",
        new Skeleton());
    Room* ruins2        = new Room("Collapsed Tower",
        "A tower that once stood tall, now in ruins.",
        new Skeleton());
    Room* mountainPass  = new Room("Mountain Pass",
        "A narrow path through the mountains.",
        new Orc());
    Room* midShopRoom   = new Room("Blacksmith's Forge",
        "The heat from the forge warms the room.",
        nullptr, midShop);
    Room* cave1         = new Room("Mountain Cave",
        "A dark cave reeking of death.",
        new Orc());
    Room* orcCamp       = new Room("Orc Camp",
        "A crude camp with fire pits and bones.",
        new Orc());
    Room* orcStronghold = new Room("Orc Stronghold",
        "The lair of the orc warlord.",
        new Orc());
    Room* lateShopRoom  = new Room("Abandoned Outpost",
        "A crumbling outpost with a lone merchant.",
        nullptr, lateShop);
    Room* dragonPass    = new Room("Dragon's Pass",
        "Scorch marks cover the walls.",
        new Dragon());
    Room* dragonLair    = new Room("Dragon's Lair",
        "Scorched walls and piles of gold.",
        new Dragon());
    Room* throneRoom    = new Room("Throne Room",
        "The seat of the Fallen King. Darkness fills the air.",
        new FallenKing());

    start->setNPC("Elder Aldric", "Traveller, beware the forest. The Fallen King's shadow grows.");
    ruins1->setNPC("Ghost", "The king was not always evil. Something corrupted him...");
    lateShopRoom->setNPC("Scout", "Beyond here lies the Dragon's Pass. Prepare yourself.");

    start->addExit("north", forest1);
    start->addExit("east", clearing);
    start->addExit("west", shadyAlley);
    start->addExit("south", arcaneLibrary);

    shadyAlley->addExit("east", start);

    arcaneLibrary->addExit("north", start);

    clearing->addExit("west", start);
    clearing->addExit("north", forest3);

    forest1->addExit("south", start);
    forest1->addExit("north", forest2);
    forest1->addExit("east", forest4);

    forest2->addExit("south", forest1);
    forest2->addExit("north", ruins1);

    forest3->addExit("south", clearing);
    forest3->addExit("north", forest5);

    forest4->addExit("west", forest1);
    forest4->addExit("north", ruins2);

    forest5->addExit("south", forest3);
    forest5->addExit("east", ruins1);

    ruins1->addExit("south", forest2);
    ruins1->addExit("west", forest5);
    ruins1->addExit("east", graveyard);

    graveyard->addExit("west", ruins1);
    graveyard->addExit("north", chapel);

    chapel->addExit("south", graveyard);
    chapel->addExit("east", ruins2);

    ruins2->addExit("west", chapel);
    ruins2->addExit("south", forest4);
    ruins2->addExit("north", mountainPass);

    mountainPass->addExit("south", ruins2);
    mountainPass->addExit("north", midShopRoom);

    midShopRoom->addExit("south", mountainPass);
    midShopRoom->addExit("north", cave1);
    midShopRoom->addExit("east", orcCamp);

    cave1->addExit("south", midShopRoom);
    cave1->addExit("north", orcStronghold);

    orcCamp->addExit("west", midShopRoom);
    orcCamp->addExit("north", orcStronghold);

    orcStronghold->addExit("south", cave1);
    orcStronghold->addExit("north", lateShopRoom);

    lateShopRoom->addExit("south", orcStronghold);
    lateShopRoom->addExit("north", dragonPass);

    dragonPass->addExit("south", lateShopRoom);
    dragonPass->addExit("north", dragonLair);

    dragonLair->addExit("south", dragonPass);
    dragonLair->addExit("north", throneRoom);

    throneRoom->addExit("south", dragonLair);

    this->allRooms.push_back(start);
    this->allRooms.push_back(shadyAlley);
    this->allRooms.push_back(arcaneLibrary);
    this->allRooms.push_back(forest1);
    this->allRooms.push_back(clearing);
    this->allRooms.push_back(forest2);
    this->allRooms.push_back(forest3);
    this->allRooms.push_back(forest4);
    this->allRooms.push_back(forest5);
    this->allRooms.push_back(ruins1);
    this->allRooms.push_back(graveyard);
    this->allRooms.push_back(chapel);
    this->allRooms.push_back(ruins2);
    this->allRooms.push_back(mountainPass);
    this->allRooms.push_back(midShopRoom);
    this->allRooms.push_back(cave1);
    this->allRooms.push_back(orcCamp);
    this->allRooms.push_back(orcStronghold);
    this->allRooms.push_back(lateShopRoom);
    this->allRooms.push_back(dragonPass);
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
                std::cout << "\n\033[1;33m═══ INVENTORY ═══\033[0m\n";
                this->player->getInventory()->getDescription();
                std::cout << "Choose item (0 to cancel): ";

                int itemChoice = 0;
                std::cin >> itemChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if(itemChoice != 0)
                {
                    this->player->getInventory()->useItem(itemChoice - 1, *this->player);
                }
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

        bool wasStunned = enemy->isStunned();  

        enemy->processEffects();             

        if(!enemy->isAlive())
        {
            break;
        }

        if(wasStunned)                       
        {

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