#pragma once
#include <string>

class Entity;

class StatusEffect
{
    protected:
        std::string effectName;
        int duration;
        int damage;

    public:
        StatusEffect(const std::string& effectName, int duration, int damage);

        std::string getEffectName() const;

        int getDuration() const;

        int getDamage() const;

        virtual void apply(Entity& target) = 0;

        void tick();

        bool isExpired() const;

        virtual ~StatusEffect() = default;
};

class Poison : public StatusEffect
{
    private:
        int stackCount;

    public:
        Poison(int stacks = 1);

        void apply(Entity& target) override;
};

class Burn : public StatusEffect
{
    private:
        int burnIntensity;

    public:
        Burn(int intensity = 1);

        void apply(Entity& target) override;
};

class Stun : public StatusEffect
{
    public:
        Stun();

        void apply(Entity& target) override;

        bool isStunned() const;
};

class Freeze : public StatusEffect
{
    public:
        Freeze();

        void apply(Entity& target) override;

        bool isFrozen() const;
};