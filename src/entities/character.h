#pragma once
#include <string>
#include <vector>
#include "entity.h"

class Enemy;
class StatusEffect;
class Inventory;
class Weapon;
class Armor;

class Character : public Entity
{
    protected:
        int level;
        int XP;
        int ATK;
        int DEF;
        int MP;
        int gold;

    private:
        Inventory * inventory;
        Weapon * equippedWeapon;
        Armor * equippedArmor;
        std::vector<StatusEffect*> effects;

    public:
        Character(const std::string& name, int HP, int ATK, int DEF,int MP);

        int getLevel() const;

        int getXP() const;

        int getATK() const;

        int getDEF() const;

        int getMP() const;

        int getGold() const;

        void gainXP(int amount);

        void gainGold(int amount);

        void spendGold(int amount);

        void levelUp();

        void equipWeapon(Weapon * weapon);

        void unequipWeapon();

        void equipArmor(Armor * armor);

        void unequipArmor();

        void addEffect(StatusEffect * effect);

        void processEffects();

        bool isStunned() const;

        void displayStatus() const override;

        void showStats() const;

        virtual void useSkill(Enemy& target, int skillIndex) = 0;

        virtual void showSkills() const = 0;

        virtual std::string getClassName() const = 0;

        virtual ~Character();
};