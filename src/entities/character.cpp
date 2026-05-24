#include <iostream>
#include "character.h"
#include "../items/inventory.h"
#include "../items/item.h"
#include "../items/statuseffects.h"


Character::Character(const std::string& name, int HP, int ATK, int DEF, int MP, int maxMP, float critChance)
    :Entity(name, HP), level(1), XP(0), ATK(ATK), DEF(DEF), MP(MP), maxMP(maxMP), gold(0), critChance(critChance), inventory(nullptr), equippedWeapon(nullptr), equippedArmor(nullptr)
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

int Character::getMaxMP() const
{
    return this->maxMP;
}

int Character::getGold() const
{
    return this->gold;
}

Weapon * Character::getEquippedWeapon() const
{
    return this->equippedWeapon;
}

Armor * Character::getEquippedArmor() const
{
    return this->equippedArmor;
}

void Character::setStats(int HP, int maxHP, int level, int XP, int gold, int ATK, int DEF, int MP, int maxMP)
{
    this->HP = HP;
    this->maxHP = maxHP;
    this->level = level;
    this->XP = XP;
    this->gold = gold;
    this->ATK = ATK;
    this->DEF = DEF;
    this->MP = MP;
    this->maxMP = maxMP;
}

Inventory * Character::getInventory() const
{
    return this->inventory;
}

void Character::initInventory()
{
    this->inventory = new Inventory(10);
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

void Character::equipWeapon(Weapon* weapon)
{

    if(this->equippedWeapon != nullptr)
    {
        this->ATK -= this->equippedWeapon->getATKbonus();
        this->DEF -= this->equippedWeapon->getDEFbonus();
        this->MP  -= this->equippedWeapon->getMPbonus();
    }

    this->equippedWeapon = weapon;

    if(weapon != nullptr)
    {
        this->ATK += weapon->getATKbonus();
        this->DEF += weapon->getDEFbonus();
        this->MP  += weapon->getMPbonus();
    }
    
}

void Character::unequipWeapon()
{

    if(this->equippedWeapon != nullptr)
    {
        this->ATK -= this->equippedWeapon->getATKbonus();
        this->DEF -= this->equippedWeapon->getDEFbonus();
        this->MP  -= this->equippedWeapon->getMPbonus();
    }

    this->equippedWeapon = nullptr;
}

void Character::equipArmor(Armor* armor)
{

    if(this->equippedArmor != nullptr)
    {
        this->DEF -= this->equippedArmor->getDEFbonus();
    }

    this->equippedArmor = armor;

    if(armor != nullptr)
    {
        this->DEF += armor->getDEFbonus();
    }

}

void Character::unequipArmor()
{

    if(this->equippedArmor != nullptr)
    {
        this->DEF -= this->equippedArmor->getDEFbonus();
    }

    this->equippedArmor = nullptr;
}

void Character::addEffect(StatusEffect * effect)
{
    this->effects.push_back(effect);
}

void Character::processEffects()
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

bool Character::isStunned() const
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

    std::cout << "\nEquipped:\n";

    if(this->equippedWeapon != nullptr)
    {
        std::cout << "  Weapon: ";
        this->equippedWeapon->getDescription();
    }

    else
    {
        std::cout << "  Weapon: None\n";
    }

    if(this->equippedArmor != nullptr)
    {
        std::cout << "  Armor: ";
        this->equippedArmor->getDescription();
    }

    else
    {
        std::cout << "  Armor: None\n";
    }

}

void Character::attack(Entity& target)
{
    int dmg = std::max(1, this->ATK - 2);

    float roll = (float)(rand() % 100) / 100.0f;

    if(roll < this->critChance)
    {
        dmg *= 2;
        std::cout << "\033[1;33m★ CRITICAL HIT! ★\033[0m ";
    }

    std::cout << this->name << " attacks " << target.getName()
              << " for " << dmg << " damage!\n";
    target.takeDamage(dmg);
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