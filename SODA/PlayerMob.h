#pragma once
#include <iostream>

class Entity abstract
{
protected:
	float health;
	float damage;
	int gold;

	Entity(
		float _health,
		float _damage,
		int _gold
	) :
		health(_health),
		damage(_damage),
		gold(_gold)
	{};

public:
	bool IsAlive() { return health > 0; }

};

class Mob : private Entity
{
private:
	char sym;
	std::string* name;
	const char* says;

	Mob(
		char _sym,
		const char _says[],
		float _health,
		float _damage,
		int _gold
	) :
		Entity(_health, _damage, _gold),
		sym(_sym),
		says(_says)
	{};

	static Mob Mobs[3];

	static std::string* AddNameAndNum(const char* name, unsigned int num)
	{
		return new std::string(std::string(name) + std::to_string(num));
	}

public:
	Mob(const Mob& mob) :
		Entity(mob.health, mob.damage, mob.gold),
		sym(mob.sym),
		says(mob.says)
	{
		if (mob.name)
			this->name = new std::string(*mob.name);
	}

	static Mob GetNew()
	{
		Mob& mob = Mobs[rand() % 3];

		static unsigned int slimy_s = 0;
		static unsigned int orcy_s = 0;
		static unsigned int dragy_s = 0;

		switch (mob.sym)
		{
		case 's':
			mob.name = AddNameAndNum("Slimy ", ++slimy_s);
			break;
		case 'o':
			mob.name = AddNameAndNum("Orcy ", ++orcy_s);
			break;
		case 'd':
			mob.name = AddNameAndNum("Dragy ", ++dragy_s);
			break;
		}

		return mob;
	}

	static const char* SlimeHealText[3];
	static const char* OrcHealText[3];
	static const char* DragonHealText[3];

	static const float SlimeHealMax[3];
	static const float OrcHealMax[3];
	static const float DragonHealMax[3];

	bool GetHit(float hits);

	std::string GetName()
	{
		return *name;
	}

	int GetGold()
	{
		return gold;
	}

	float GetDamage()
	{
		return damage;
	}

	char GetSym();

	float GetHealth();

	using Entity::IsAlive;

	void Print()
	{
		std::cout <<
			sym << ": " << says << '\n' <<
			"His name is " << *name << '\n' <<
			"He have " << health << " health and deals up to " << damage << " damage\n";
	}

	~Mob()
	{
		delete name;
	}

};

class Player : private Entity
{
private:
	int lvl = 1;
	bool poisened = false;
	int sword_breaks = 0;

public:
	Player() : Entity(25.0f, 1.0f, 0) {}

	bool GetHit(float hits);

	float AddHealth(float heal);

	int GetGold();

	void AddGold(int gold);

	int GetLvl();

	float GetDamage();

	using Entity::IsAlive;

	int IncLvl();

	void Poisen();

	bool IsPoisened();

	void UnPoisen();

	void BreakSword();

	int GetSwordBreaks();

	void RepearSword();

	void Print();

};
