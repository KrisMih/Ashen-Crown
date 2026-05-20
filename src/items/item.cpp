#include <iostream>
#include "item.h"
#include "../entities/character.h"

Item::Item(const std::string& name, int value, bool tradeable)
    : name(name), value(value), tradeable(tradeable)
{

}

std::string Item::getName() const
{
    return this->name;
}

int Item::getValue() const
{
    return this->value;
}

bool Item::isTradeable() const
{
    return this->tradeable;
}

void Item::getDescription() const
{
    std::cout << this->name << " - " << this->value << "g\n";
}

Weapon::Weapon(const std::string& name, int value, bool tradeable, int ATKbonus, int MPbonus, int DEFbonus, const std::string allowedClass)
    : Item(name, value, tradeable), ATKbonus(ATKbonus), MPbonus(MPbonus), DEFbonus(DEFbonus), allowedClass(allowedClass)
{

}

int Weapon::getATKbonus() const
{
    return this->ATKbonus;
}

int Weapon::getMPbonus() const
{
    return this->MPbonus;
}

int Weapon::getDEFbonus() const
{
    return this->DEFbonus;
}

std::string Weapon::getAllowedClass() const
{
    return this->allowedClass;
}

Sword::Sword(const std::string& name, int value, bool tradeable, int ATKbonus, int DEFbonus)
    : Weapon(name, value, tradeable, ATKbonus, 0, DEFbonus, "Warrior")
{

}

void Sword::use(Character& target)
{

    if(target.getClassName() != this->allowedClass)
    {
        std::cout << target.getName() << " cannot equip " << this->name << "! (Warrior only)\n";
        return;
    }

    target.equipWeapon(this);
    std::cout << target.getName() << " equips " << this->name << "!\n";
}

void Sword::getDescription() const
{
    std::cout << this->name
              << " [ATK +" << this->ATKbonus
              << " DEF +" << this->DEFbonus
              << "] - " << this->value << "g | Class: Warrior\n";
}

Staff::Staff(const std::string& name, int value, bool tradeable, int MPbonus)
    : Weapon(name, value, tradeable, 0, MPbonus, 0, "Mage")
{

}

void Staff::use(Character& target)
{

    if(target.getClassName() != this->allowedClass)
    {
        std::cout << target.getName() << " cannot equip " << this->name << "! (Mage only)\n";
        return;
    }

    target.equipWeapon(this);
    std::cout << target.getName() << " equips " << this->name << "!\n";
}

void Staff::getDescription() const
{
    std::cout << this->name
              << " [MP +" << this->MPbonus
              << "] - " << this->value << "g | Class: Mage\n";
}

Dagger::Dagger(const std::string& name, int value, bool tradeable, int ATKbonus)
    : Weapon(name, value, tradeable, ATKbonus, 0, 0, "Rogue")
{

}

void Dagger::use(Character& target)
{

    if(target.getClassName() != this->allowedClass)
    {
        std::cout << target.getName() << " cannot equip " << this->name << "! (Rogue only)\n";
        return;
    }

    target.equipWeapon(this);
    std::cout << target.getName() << " equips " << this->name << "!\n";
}

void Dagger::getDescription() const
{
    std::cout << this->name
              << " [ATK +" << this->ATKbonus
              << "] - " << this->value << "g | Class: Rogue\n";
}

Armor::Armor(const std::string& name, int value, bool tradeable, int DEFbonus, const std::string& allowedClass)
    : Item(name, value, tradeable), DEFbonus(DEFbonus), allowedClass(allowedClass)
{
    
}

int Armor::getDEFbonus() const
{
    return this->DEFbonus;
}

std::string Armor::getAllowedClass() const
{
    return this->allowedClass;
}

LightArmor::LightArmor(const std::string& name, int value, bool tradeable, int DEFbonus)
    : Armor(name, value, tradeable, DEFbonus, "Mage")
{

}

void LightArmor::use(Character& target)
{
    if(target.getClassName() != this->allowedClass)
    {
        std::cout << target.getName() << " cannot equip " << this->name << "! (Mage only)\n";
        return;
    }

    target.equipArmor(this);
    std::cout << target.getName() << " equips " << this->name << "!\n";
}

void LightArmor::getDescription() const
{
    std::cout << this->name
              << " [DEF +" << this->DEFbonus
              << "] - " << this->value << "g | Class: Mage\n";
}

MediumArmor::MediumArmor(const std::string& name, int value, bool tradeable, int DEFbonus)
    : Armor(name, value, tradeable, DEFbonus, "Rogue")
{

}

void MediumArmor::use(Character& target)
{

    if(target.getClassName() != this->allowedClass)
    {
        std::cout << target.getName() << " cannot equip " << this->name << "! (Rogue only)\n";
        return;
    }

    target.equipArmor(this);
    std::cout << target.getName() << " equips " << this->name << "!\n";
}

void MediumArmor::getDescription() const
{
    std::cout << this->name
              << " [DEF +" << this->DEFbonus
              << "] - " << this->value << "g | Class: Rogue\n";
}

HeavyArmor::HeavyArmor(const std::string& name, int value, bool tradeable, int DEFbonus)
    : Armor(name, value, tradeable, DEFbonus, "Warrior")
{

}

void HeavyArmor::use(Character& target)
{

    if(target.getClassName() != this->allowedClass)
    {
        std::cout << target.getName() << " cannot equip " << this->name << "! (Warrior only)\n";
        return;
    }

    target.equipArmor(this);
    std::cout << target.getName() << " equips " << this->name << "!\n";
}

void HeavyArmor::getDescription() const
{
    std::cout << this->name
              << " [DEF +" << this->DEFbonus
              << "] - " << this->value << "g | Class: Warrior\n";
}

Potion::Potion(const std::string& name, int value, int healAmount)
    : Item(name, value, true), healAmount(healAmount)
{

}

void Potion::use(Character& target)
{
    target.heal(this->healAmount);
    std::cout << target.getName() << " drinks " << this->name
              << " and restores " << this->healAmount << " HP!\n";
}

void Potion::getDescription() const
{
    std::cout << this->name
              << " [+" << this->healAmount << " HP]"
              << " - " << this->value << "g\n";
}

int Potion::getHealAmount() const
{
    return this->healAmount;
}