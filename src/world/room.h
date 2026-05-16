#pragma once
#include <string>
#include <map>

class Enemy;
class Shop;

class Room
{
    private:
        std::string name;
        std::string description;
        Enemy* enemy;
        Shop* shop;
        std::string npcName;
        std::string npcDialogue;
        std::map<std::string, Room*> exits;

    public:
        Room(const std::string& name, const std::string& description, Enemy* enemy = nullptr, Shop* shop = nullptr);

        void addExit(const std::string& direction, Room* room);

        void setNPC(const std::string& name, const std::string& dialogue);

        Room* getExit(const std::string& direction) const;

        Enemy* getEnemy() const;

        Shop* getShop() const;

        std::string getName() const;

        std::string getDescription() const;

        bool hasNPC() const;

        bool hasEnemy() const;

        bool hasShop() const;

        void describe() const;

        void clearEnemy();

        ~Room();
};