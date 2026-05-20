#include <iostream>
#include <string>
#include "enemy.h"
#include "character.h"
#include "../items/statuseffects.h"
#include "entity.h"

Enemy::Enemy(const std::string& name, int HP, int ATK, int DEF, int XPreward, int goldReward, const std::string& description)
    :Entity(name, HP), ATK(ATK), DEF(DEF), XPreward(XPreward), goldReward(goldReward), description(description)
{

}

int Enemy::getATK() const
{
    return this->ATK;
}

int Enemy::getDEF() const
{
    return this->DEF;
}

int Enemy::getXPreward() const
{
    return this->XPreward;
}

int Enemy::getGoldReward() const
{
    return this->goldReward;
}

int Enemy::getLevel() const
{
    return this->level;
}

Item * Enemy::getDropReward() const
{
    return this->dropReward;
}

float Enemy::getDropChance() const
{
    return this->dropChance;
}

bool Enemy::isImmuneToPoison() const
{
    return this->immuneToPoison;
}

bool Enemy::isImmuneToFire() const
{
    return this->immuneToFire;
}

bool Enemy::isImmuneToCold() const
{
    return this->immuneToCold;
}

std::string Enemy::getDescription() const
{
    return this->description;
}

void Enemy::addEffect(StatusEffect* effect)
{
    this->effects.push_back(effect);
}

void Enemy::processEffects()
{

    for(int i = 0; i < this->effects.size(); i++)
    {
        this->effects[i]->apply(*this);
    }

    for(int i = this->effects.size() - 1; i >= 0; i--)
    {

        if(this->effects[i]->isExpired())
        {
            delete this->effects[i];
            this->effects.erase(this->effects.begin() + i);
        }

    }

}

bool Enemy::isStunned() const
{

    for(int i = 0; i < this->effects.size(); i++)
    {
        Stun* stun = dynamic_cast<Stun*>(this->effects[i]);

        if(stun && stun->isStunned()) 
        {
            return true;
        }

        Freeze* freeze = dynamic_cast<Freeze*>(this->effects[i]);

        if(freeze && freeze->isFrozen()) 
        {
            return true;
        }

    }
    
    return false;
}

void Enemy::displayStatus() const
{
    std::cout << this->name << " — HP: " << this->HP << "/" << this->maxHP
              << " | ATK: " << this->ATK << " | DEF: " << this->DEF
              << " | Level: " << this->level << "\n";
    std::cout << this->description << "\n";
    std::cout << "Immunities: ";
    bool hasImmunity = false;

    if(this->immuneToFire)
    { 
        std::cout << "[Fire] ";   
        hasImmunity = true; 
    }

    if(this->immuneToPoison) 
    { 
        std::cout << "[Poison] "; 
        hasImmunity = true; 
    }

    if(this->immuneToCold)   
    { 
        std::cout << "[Cold] ";   
        hasImmunity = true; 
    }

    if(!hasImmunity)         
    { 
        std::cout << "None"; 
    }

    std::cout << "\n";
}

Enemy::~Enemy()
{
    delete this->dropReward;

    for(int i = 0; i < this->effects.size(); i++)
    {
        delete this->effects[i];
    }

}

Goblin::Goblin()
    :Enemy("Goblin", 25, 6, 3, 80, 10, "A small, but vicious creature.")
{
    this->level = 1;
    this->dropChance = 0.5f;
    this->dropReward = nullptr;
    this->immuneToFire   = false;
    this->immuneToPoison = false;
    this->immuneToCold   = false;
}

void Goblin::attack(Entity& target)
{
    Character& character = dynamic_cast<Character&>(target);
    int damage = std::max(1, this->ATK - character.getDEF() / 3);
    std::cout << this->name << " scratches " << target.getName()
              << " for " << damage << " damage!\n";
    target.takeDamage(damage);

    if(this->HP > this->maxHP / 2)
    {
        int damage2 = std::max(1, damage / 2);
        std::cout << this->name << " scratches again for " << damage2 << " damage!\n";
        target.takeDamage(damage2);
    }

}

Skeleton::Skeleton()
    : Enemy("Skeleton", 35, 9, 4, 120, 15, "An undead warrior immune to poison.")
{
    this->level = 1;
    this->dropChance = 0.4f;
    this->dropReward = nullptr;
    this->immuneToFire   = false;
    this->immuneToPoison = true;
    this->immuneToCold   = false;
}

void Skeleton::attack(Entity& target)
{
    Character& character = dynamic_cast<Character&>(target);
    int damage = std::max(1, this->ATK - character.getDEF() / 3);
    std::cout << this->name << " slashes " << target.getName()
              << " for " << damage << " damage!\n";
    target.takeDamage(damage);
}


Orc::Orc()
    : Enemy("Orc", 80, 15, 12, 250, 50, "A brutish warrior with thick hide.")
{
    this->level = 3;
    this->dropChance = 0.5f;
    this->dropReward = nullptr;
    this->immuneToFire   = false;
    this->immuneToPoison = false;
    this->immuneToCold   = false;
}

void Orc::attack(Entity& target)
{
    Character& character = dynamic_cast<Character&>(target);
    int damage = std::max(1, this->ATK - character.getDEF() / 3);
    std::cout << this->name << " smashes " << target.getName()
              << " for " << damage << " damage!\n";
    target.takeDamage(damage);
}

Dragon::Dragon()
    : Enemy("Dragon", 150, 28, 8, 600, 150, "An ancient beast wreathed in fire."), turnCount(0), fireDMG(45)
{
    this->level = 4;
    this->dropChance = 1.0f;
    this->dropReward = nullptr;
    this->immuneToFire   = true;
    this->immuneToPoison = false;
    this->immuneToCold   = false;
}

void Dragon::attack(Entity& target)
{
    Character& character = dynamic_cast<Character&>(target);
    this->turnCount++;

    if(this->turnCount % 3 == 0)
    {
        this->fireBreath(target);
    }

    else
    {
        int damage = std::max(1, this->ATK - character.getDEF() / 3);
        std::cout << this->name << " claws " << target.getName()
                  << " for " << damage << " damage!\n";
        target.takeDamage(damage);
    }

}

void Dragon::fireBreath(Entity& target)
{
    std::cout << "\033[1;31m" << this->name << " breathes fire at "
              << target.getName() << " for " << this->fireDMG << " damage!\033[0m\n";
    target.takeDamage(this->fireDMG);
}

FallenKing::FallenKing()
    : Enemy("The Fallen King", 500, 40, 15, 1000, 500, "The corrupted ruler of Ashen Crown. He commands fire, ice and darkness."),
      turnCount(0), phase(1)
{
    this->level = 5;
    this->dropChance = 1.0f;
    this->dropReward = nullptr;
    this->immuneToFire   = false;
    this->immuneToPoison = false;
    this->immuneToCold   = false;
}

void FallenKing::attack(Entity& target)
{
    Character& character = dynamic_cast<Character&>(target);
    this->turnCount++;

    if(this->HP < this->maxHP / 2 && this->phase == 1)
    {
        this->phase = 2;
        std::cout << "\n\033[1;31mThe Fallen King roars! He enters Phase 2!\033[0m\n\n";
        this->ATK += 15;
    }

    if(this->turnCount % 3 == 0)
    {
        this->soulRend(target);
    }

    else if(this->phase == 2 && this->turnCount % 2 == 0)
    {
        this->crownOfAshes(target);
    }

    else
    {
        int damage = std::max(1, this->ATK - character.getDEF() / 3);
        std::cout << this->name << " strikes " << target.getName()
                  << " for " << damage << " damage!\n";
        target.takeDamage(damage);
    }

}

void FallenKing::soulRend(Entity& target)
{
    int dmg = this->ATK + 25;
    std::cout << "\033[1;35mSoul Rend!\033[0m " << this->name
              << " tears at " << target.getName()
              << "'s soul for " << dmg << " damage!\n";
    target.takeDamage(dmg);
}

void FallenKing::crownOfAshes(Entity& target)
{
    int dmg = this->ATK + 40;
    std::cout << "\033[1;31mCrown of Ashes!\033[0m The Fallen King unleashes ash and fire for "
              << dmg << " damage!\n";
    target.takeDamage(dmg);
}