#include <iostream>
#include "classes.h"
#include "enemy.h"
#include "../items/statuseffects.h"
#include <algorithm>

Warrior::Warrior(const std::string& name)
    : Character(name, 120, 15, 10, 20), rage(0)
{

}

std::string Warrior::getClassName() const
{
    return "Warrior";
}

void Warrior::levelUp()
{
    Character::levelUp();
    this->maxHP += 20;
    this->HP = this->maxHP;
    this->ATK += 5;
    this->DEF += 4;
    this->MP += 5;
}

void Warrior::showSkills() const
{
    std::cout << "\033[1;31m  Skills (Warrior):\033[0m\n";
    std::cout << "  1. Shield Bash  — damage + stun        [Lv.1] [5 MP]\n";

    if(this->level >= 3)
    {
        std::cout << "  2. Whirlwind    — heavy damage          [Lv.3] [15 MP]\n";
    }

    if(this->level >= 5)
    {
        std::cout << "  3. Berserker    — 2x ATK                [Lv.5] [25 MP]\n";
    }

}

void Warrior::useSkill(Enemy& target, int skillIndex)
{

    if(skillIndex == 1)
    {
        this->shieldBash(target);
        return;
    }

    if(skillIndex == 2 && this->level >= 3)
    {
        this->whirlwind(target);
        return;
    }

    if(skillIndex == 3 && this->level >= 5)
    {
        this->berserker(target);
        return;
    }

    else
    {
        throw std::invalid_argument("You can't use this skill, yet!");
    }

}

void Warrior::shieldBash(Enemy& target)
{

    if(this->MP < 5) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }

    this->MP -= 5;
    int dmg = this->ATK + 10;
    std::cout << "\033[1;31m⚔ Shield Bash!\033[0m " << this->name
              << " slams " << target.getName() << " for " << dmg << " damage!\n";
    target.takeDamage(dmg);
    target.addEffect(new Stun()); 
}

void Warrior::whirlwind(Enemy& target)
{

    if(this->MP < 15) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }

    this->MP -= 15;
    int dmg = this->ATK + 25;
    std::cout << "\033[1;31m🌀 Whirlwind!\033[0m " << this->name
              << " spins for " << dmg << " damage!\n";
    target.takeDamage(dmg);
}

void Warrior::berserker(Enemy& target)
{

    if(this->MP < 25) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }

    this->MP -= 25;
    int dmg = this->ATK * 2;
    std::cout << "\033[1;31m💢 Berserker!\033[0m " << this->name
              << " deals " << dmg << " massive damage!\n";
    target.takeDamage(dmg);
}

Mage::Mage(const std::string& name)
    : Character(name, 80, 8, 5, 80), spellPower(20)
{

}

std::string Mage::getClassName() const
{
    return "Mage";
}

void Mage::levelUp()
{
    Character::levelUp();
    this->maxHP += 10;
    this->HP = this->maxHP;
    this->ATK += 2;
    this->DEF += 2;
    this->MP += 20;
    this->spellPower += 5;
}

void Mage::showSkills() const
{
    std::cout << "\033[1;34m  Skills (Mage):\033[0m\n";
    std::cout << "  1. Fireball     — fire damage + burn    [Lv.1] [15 MP]\n";

    if(this->level >= 3)
    {
        std::cout << "  2. Ice Blast    — cold damage + stun    [Lv.3] [20 MP]\n";
    }

    if(this->level >= 5)
    {
        std::cout << "  3. Thunderstorm — massive damage        [Lv.5] [40 MP]\n";
    }

}

void Mage::useSkill(Enemy& target, int skillIndex)
{

    if(skillIndex == 1) 
    { 
        fireball(target); 
        return; 
    }

    if(skillIndex == 2 && this->level >= 3) 
    { 
        iceBlast(target); 
        return; 
    }

    if(skillIndex == 3 && this->level >= 5) 
    { 
        thunderstorm(target); 
        return; 
    }

    else
    {
        throw std::invalid_argument("You can't use this skill, yet!");
    }

}

void Mage::fireball(Enemy& target)
{

    if(this->MP < 15) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }

    this->MP -= 15;

    if(target.isImmuneToFire())
    {
        std::cout << target.getName() << " is immune to fire!\n";
        return;
    }

    int dmg = this->spellPower + 25;
    std::cout << "\033[1;31m🔥 Fireball!\033[0m " << this->name
              << " hurls a fireball for " << dmg << " damage!\n";
    target.takeDamage(dmg);
    target.addEffect(new Burn(1));
}

void Mage::iceBlast(Enemy& target)
{

    if(this->MP < 20) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }

    this->MP -= 20;

    if(target.isImmuneToCold())
    {
        std::cout << target.getName() << " is immune to cold!\n";
        return;
    }

    int dmg = this->spellPower + 35;
    std::cout << "\033[1;36m❄ Ice Blast!\033[0m " << this->name
              << " freezes " << target.getName() << " for " << dmg << " damage!\n";
    target.takeDamage(dmg);
    target.addEffect(new Stun());
}

void Mage::thunderstorm(Enemy& target)
{

    if(this->MP < 40) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }

    this->MP -= 40;
    int dmg = this->spellPower + 70;
    std::cout << "\033[1;33m⚡ Thunderstorm!\033[0m Lightning strikes "
              << target.getName() << " for " << dmg << " damage!\n";
    target.takeDamage(dmg);
}

Rogue::Rogue(const std::string& name)
    : Character(name, 90, 12, 7, 50), critChance(0.25f), stealth(false)
{

}

std::string Rogue::getClassName() const
{
    return "Rogue";
}

void Rogue::levelUp()
{
    Character::levelUp();
    this->maxHP += 15;
    this->HP = this->maxHP;
    this->ATK += 4;
    this->DEF += 3;
    this->MP += 10;
    this->critChance += 0.05f;
}

void Rogue::showSkills() const
{
    std::cout << "\033[1;35m  Skills (Rogue):\033[0m\n";
    std::cout << "  1. Backstab     — 3x damage             [Lv.1] [10 MP]\n";

    if(this->level >= 3)
    {
        std::cout << "  2. Poison Blade — damage + poison       [Lv.3] [15 MP]\n";
    }

    if(this->level >= 5)
    {
        std::cout << "  3. Shadow Step  — 2x damage + evade     [Lv.5] [20 MP]\n";
    }

}

void Rogue::useSkill(Enemy& target, int skillIndex)
{

    if(skillIndex == 1) 
    { 
        backstab(target); 
        return; 
    }

    if(skillIndex == 2 && this->level >= 3) 
    { 
        poisonBlade(target); 
        return; 
    }

    if(skillIndex == 3 && this->level >= 5) 
    { 
        shadowStep(target); 
        return; 
    }

    else
    {
        throw std::invalid_argument("You can't use this skill, yet!");
    }
    
}

void Rogue::backstab(Enemy& target)
{

    if(this->MP < 10) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }
    
    this->MP -= 10;
    int dmg = this->ATK * 3;
    std::cout << "\033[1;35m🗡 Backstab!\033[0m " << this->name
              << " strikes from the shadows for " << dmg << " damage!\n";
    target.takeDamage(dmg);
}

void Rogue::poisonBlade(Enemy& target)
{

    if(this->MP < 15) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }

    this->MP -= 15;

    if(target.isImmuneToPoison())
    {
        std::cout << target.getName() << " is immune to poison!\n";
        return;
    }

    int dmg = this->ATK + 15;
    std::cout << "\033[1;32m☠ Poison Blade!\033[0m " << this->name
              << " coats their blade in poison for " << dmg << " damage!\n";
    target.takeDamage(dmg);
    target.addEffect(new Poison(2));
}

void Rogue::shadowStep(Enemy& target)
{

    if(this->MP < 20) 
    { 
        std::cout << "Not enough MP!\n"; 
        return; 
    }

    this->MP -= 20;
    int dmg = this->ATK * 2 + 20;
    std::cout << "\033[1;35m👤 Shadow Step!\033[0m " << this->name
              << " vanishes and reappears for " << dmg << " damage!\n";
    target.takeDamage(dmg);
}