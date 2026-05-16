#include <iostream>
#include "statuseffects.h"
#include "../entities/entity.h"

StatusEffect::StatusEffect(const std::string& effectName, int duration, int damage)
    :effectName(effectName), duration(duration), damage(damage)
{

}

std::string StatusEffect::getEffectName() const
{
    return this->effectName;
}

int StatusEffect::getDuration() const
{
    return this->duration;
}

int StatusEffect::getDamage() const
{
    return this->damage;
}

void StatusEffect::tick()
{

    if(this->duration > 0)
    {
        this->duration--;
    }

}

bool StatusEffect::isExpired() const
{
    return this->duration <= 0;
}

Poison::Poison(int stacks)
    : StatusEffect("Poison", 3, 5 * stacks), stackCount(stacks)
{

}

void Poison::apply(Entity& target)
{
    std::cout << "\033[32m[Poison] " << target.getName()
              << " takes " << this->damage << " poison damage! ("
              << this->duration << " turns left)\033[0m\n";
    target.takeDamage(this->damage);
    this->tick();
}

Burn::Burn(int intensity)
    : StatusEffect("Burn", 3, 8 * intensity), burnIntensity(intensity)
{

}

void Burn::apply(Entity& target)
{
    std::cout << "\033[31m[Burn] " << target.getName()
              << " takes " << this->damage << " burn damage! ("
              << this->duration << " turns left)\033[0m\n";
    target.takeDamage(this->damage);
    this->tick();
}

Stun::Stun()
    : StatusEffect("Stun", 1, 0)
{

}

void Stun::apply(Entity& target)
{
    std::cout << "\033[33m[Stun] " << target.getName()
              << " is stunned and cannot act!\033[0m\n";
    this->tick();
}

bool Stun::isStunned() const
{
    return this->duration > 0;
}

Freeze::Freeze()
    : StatusEffect("Freeze", 2, 3)
{

}

void Freeze::apply(Entity& target)
{
    std::cout << "\033[1;36m[Freeze] " << target.getName()
              << " is frozen and takes " << this->damage << " cold damage! ("
              << this->duration << " turns left)\033[0m\n";
    target.takeDamage(this->damage);
    this->tick();
}

bool Freeze::isFrozen() const
{
    return this->duration > 0;
}