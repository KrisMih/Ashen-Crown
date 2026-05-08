#pragma once
#include <string>

class Character;

class Item
{
    protected:
        std::string name;
        int value;
        bool tradeable;

    public:
        Item(const std::string name, int value, bool tradeable);

        std::string getName() const;

        int getValue() const;

        bool isTradeable() const;

        virtual void use(Character& target) = 0;

        virtual void getDescription() const;

        virtual ~Item() = default;
};

class Weapon : public Item
{
    protected:
        int ATKbonus;
        int MPbonus;
        int DEFbonus;
        std::string allowedClass;

    public:
        Weapon(const std::string& name, int value, bool tradeable,int ATKbonus, int MPbonus, int DEFbonus, const std::string allowedClass);

        int getATKbonus() const;

        int getMPbonus() const;

        int getDEFbonus() const;

        std::string getAllowedClass() const;

        virtual void use(Character& target) = 0;

        virtual void getDescription() const = 0;

        virtual ~Weapon() = default;
};

class Sword : public Weapon
{
    public:
        Sword(const std::string& name, int value, bool tradeable,int ATKbonus, int DEFbonus);

        void use(Character& target) override;

        void getDescription() const override;
};

class Staff : public Weapon
{
    public:
        Staff(const std::string& name, int value, bool tradeable,int MPbonus);

        void use(Character& target) override;

        void getDescription() const override;
};

class Dagger : public Weapon
{
    public:
        Dagger(const std::string& name, int value, bool tradeable,int ATKBonus);

        void use(Character& target) override;
        void getDescription() const override;
};

class Armor : public Item
{
    protected:
        int DEFbonus;
        std::string allowedClass;

    public:
        Armor(const std::string& name, int value, bool tradeable, int DEFbonus, const std::string& allowedClass);

        int getDEFbonus() const;

        std::string getAllowedClass() const;

        virtual void use(Character& target) = 0;

        virtual void getDescription() const = 0;

        virtual ~Armor() = default;
};

class LightArmor : public Armor
{
    public:
        LightArmor(const std::string& name, int value, bool tradeable, int DEFbonus);

        void use(Character& target) override;

        void getDescription() const override;
};

class MediumArmor : public Armor
{
        public:
            MediumArmor(const std::string& name, int value, bool tradeable, int DEFbonus);

            void use(Character& target) override;

            void getDescription() const override;
};

class HeavyArmor : public Armor
{
    public:
        HeavyArmor(const std::string& name, int value, bool tradeable, int DEFbonus);

        void use(Character& target) override;

        void getDescription() const override;
};

class Potion : public Item
{
    private:
        int healAmount;

    public:
        Potion(const std::string& name, int value, int healAmount);

        void use(Character& target) override;
        
        void getDescription() const override;

        int getHealAmount() const;
};