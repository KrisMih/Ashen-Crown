#pragma once
#include <string>

class Entity
{
    protected:
        std::string name;
        int HP;
        int maxHP;

    public:
        Entity(const std::string& name, int HP);
    
        std::string getName() const;

        int getHP() const;

        int getMaxHP() const;

        bool isAlive() const;

        void takeDamage(int amount);

        void heal(int amount);

        virtual void attack(Entity& target) = 0;

        virtual void displayStatus() const;

        virtual ~Entity() = default;
};