#pragma once
#include "entity.h"
#include "../items/statuseffects.h"
#include <vector>
#include <string>

class Character;
class Item;

class Enemy : public Entity
{
    protected:
        int ATK;
        int DEF;
        int XPreward;
        int goldReward;
        int level;
        bool immuneToFire;
        bool immuneToPoison;
        bool immuneToCold;
        std::string description;
        Item * dropReward;
        float dropChance;
        std::vector<StatusEffect*> effects;

    public:
        Enemy(const std::string& name, int HP, int ATK, int DEF, int XPreward, int goldReward, const std::string& description);

        int getATK() const;

        int getDEF() const;

        int getXPreward() const;

        int getGoldReward() const;

        int getLevel() const;

        bool isImmuneToPoison() const;

        bool isImmuneToFire() const;
        
        bool isImmuneToCold() const;

        bool isStunned() const;

        Item * getDropReward() const;

        float getDropChance() const;

        std::string getDescription() const;

        virtual void attack(Entity& target) = 0;

        void addEffect(StatusEffect* effect);

        void processEffects();

        void displayStatus() const override;

        virtual ~Enemy();
};

class Goblin : public Enemy
{
    public:
        Goblin();

        void attack(Entity& target) override;
};

class Skeleton : public Enemy
{
    public:
        Skeleton();

        void attack(Entity& target) override;
};

class Orc : public Enemy
{
    public:
        Orc();

        void attack(Entity& target) override;
};

class Dragon : public Enemy
{
    private:
        int turnCount;
        int fireDMG;

    public:
        Dragon();

        void attack(Entity& target) override;
    
    private:
        void fireBreath(Entity& target);
};


class FallenKing : public Enemy
{
    private:
        int turnCount;
        int phase;

    public:
        FallenKing();

        void attack(Entity& target) override;

    private:
        void soulRend(Entity& target);
        
        void crownOfAshes(Entity& target);
};