#include <iostream>
#include "character.h"

Character::Character(const std::string& name, int HP, int ATK, int DEF, int MP)
    :Entity(name, HP), ATK(ATK), DEF(DEF), MP(MP), level(1), gold(0), XP(0), inventory(nullptr), equippedWeapon(nullptr), equippedArmor(nullptr)
{

}

int Character::getLevel() const
{
    return this->level;
}

int Character::getXP() const
{
    return this->XP;
}

int Character::getATK() const
{
    return this->ATK;
}

int Character::getDEF() const
{
    return this->DEF;
}

int Character::getMP() const
{
    return this->MP;
}

int Character::getGold() const
{
    return this->gold;
}

void Character::gainXP(int amount)
{
    this->XP += amount;
}

void Character::gainGold(int amount)
{
    this->gold += amount;
}

void Character::spendGold(int amount)
{

    if(this->gold < amount)
    {
        throw std::invalid_argument("Insufficient amount of gold! You can't buy this!");
    }

    this->gold -= amount;
}

void Character::levelUp()
{
    if(this->XP >= 1000)
    {
        this->level++;
        this->XP -= 1000;
    }

}

void Character::equipWeapon(Weapon * weapon)
{
    this->equippedWeapon = weapon;
}

void Character::unequipWeapon()
{
    this->equippedWeapon = nullptr;
}

void Character::equipArmor(Armor * armor)
{
    this->equippedArmor = armor;
}

void Character::unequipArmor()
{
    this->equippedArmor = nullptr;
}

void Character::addEffect(StatusEffect * effect)
{
    this->effects.push_back(effect);
}

void Character::processEffects()
{
    //Will be implemented after proper declaration of 'StatusEffects'
}

bool Character::isStunned() const
{

    /* for(int i = 0; i < this->effects.size(); i++)
    {
        if(this->effects[i] == STUN) //use 'STUN' until a proper 'StatusEffect' is implemented
        {
            return true;
        }

    } */ //for the moment it will be commented until 'StatusEffect' is implemented
 
    return false;
}

void Character::displayStatus() const
{
     std::cout << this->name << " — HP: " << this->HP << "/" << this->maxHP << "\n" << " - Level: " << this->level << " - XP: " << this->XP << " - Gold: " << this->gold;
}

void Character::showStats() const
{
    std::cout << "Name: " << this->name << "\n";
    std::cout << "Class: " << this->getClassName() << "\n";
    std::cout << "Level: " << this->level << "\n";
    std::cout << "XP: " << this->XP << "/1000\n";
    std::cout << "HP: " << this->HP << "/" << this->maxHP << "\n";
    std::cout << "ATK: " << this->ATK << "\n";
    std::cout << "DEF: " << this->DEF << "\n";
    std::cout << "MP: " << this->MP << "\n";
    std::cout << "Gold: " << this->gold << "\n";
}

Character::~Character()
{

    for(int i = 0; i < this->effects.size(); i++)
    {
        delete this->effects[i];
    }

    delete this->inventory;
    this->equippedWeapon = nullptr;
    this->equippedArmor = nullptr;
}