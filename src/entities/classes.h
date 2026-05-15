#pragma once
#include "character.h"

class Enemy;

class Warrior : public Character
{
    private:
        int rage;

    public:
        Warrior(const std::string& name);

        void useSkill(Enemy& target, int skillIndex) override;

        void showSkills() const override;

        void levelUp() override;

        std::string getClassName() const override;

        private:
            void shieldBash(Enemy& target);   

            void whirlwind(Enemy& target);
                
            void berserker(Enemy& target);
};

class Mage : public Character
{
    private:
        int spellPower;

    public:
        Mage(const std::string& name);

        void useSkill(Enemy& target, int skillIndex) override;

        void showSkills() const override;

        void levelUp() override;

        std::string getClassName() const override;

    private:
        void fireball(Enemy& target);  

        void iceBlast(Enemy& target);   

        void thunderstorm(Enemy& target);  
};

class Rogue : public Character
{
    private:
        float critChance;
        bool stealth;

    public:
        Rogue(const std::string& name);

        void useSkill(Enemy& target, int skillIndex) override;

        void showSkills() const override;

        void levelUp() override;

        std::string getClassName() const override;

    private:
        void backstab(Enemy& target); 

        void poisonBlade(Enemy& target);  

        void shadowStep(Enemy& target);   
};