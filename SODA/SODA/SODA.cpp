#include "stdafx.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

COORD Coord(__int16 x, __int16 y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	return c;
}


class Console
{
private:
	static HANDLE out_handle;

	Console() = delete;

public:

	static void MoveTo(COORD c)
	{
		SetConsoleCursorPosition(out_handle, c);
	}

	static void MoveTo(__int16 x, __int16 y)
	{
		return MoveTo(Coord(x, y));
	}

	static void Clear(COORD from, COORD to)
	{
		if (from.Y > to.Y) return;
		MoveTo(from);
		std::cout << std::string(
			to.X - from.X +
			80 * (to.Y - from.Y),
			' '
		);
	}

	static void Clear()
	{
		/**/
		system("cls");
		/**
		Clear(Coord(0, 0), Coord(79, 299));
		MoveTo(Coord(0, 0));
		return;
		/**/
	}

};


class Entity
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

class Mob : public Entity
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
		Mob mob = Mobs[rand() % 3];

		static unsigned int slimy_s = 0;
		static unsigned int orcy_s = 0;
		static unsigned int dragy_s = 0;

		switch (mob.sym)
		{
		case 's':
		{
			mob.name = AddNameAndNum("slimy ", ++slimy_s);
			break;
		}
		case 'o':
		{
			mob.name = AddNameAndNum("orcy ", ++orcy_s);
			break;
		}
		case 'd':
		{
			mob.name = AddNameAndNum("dragy ", ++dragy_s);
			break;
		}
		}

		return mob;
	}

	bool GetHit(float hits)
	{
		health -= hits;
		return (health <= 0);
	}

	std::string* GetName()
	{
		return name;
	}

	int GetGold()
	{
		return gold;
	}

	float GetDamage()
	{
		return damage;
	}

	void Print()
	{
		std::cout <<
			sym << ": " << says << '\n' <<
			"His name is " << *name << '\n' <<
			"He has " << health << " health and deals up to " << damage << " damage\n";
	}

	~Mob()
	{
		delete name;
	}

};

class Player : private Entity
{
private:
	int lvl;

	void GetHit(Mob& mob)
	{
		float hits = mob.GetDamage() * (float(rand()) / RAND_MAX);
		std::cout << *mob.GetName() << " hit you with " << hits << " damage\n";
		health -= hits;
		if (health <= 0)
		{
			std::cout <<
				"You died.\n" <<
				"Last thing you remember was " << gold << " gold, you will not have opportunity to spend...\n" <<
				"Press Enter to exit";
			std::cin.ignore(MAXLONGLONG, '\n');
			exit(0);
		}
	}

public:
	Player() : Entity(25.0f, 1.0f, 0), lvl(1) {}

	using Entity::IsAlive;

	int IncLvl()
	{
		++lvl;
		if (lvl == 20)
		{
			std::cout <<
				"You reached lvl 20!\n" <<
				"With that - you won the game, carrying home "<< gold <<" gold\n"
				"y: continue\n" <<
				"every thing else: exit\n";
			char act;
			std::cin >> act;
			if (act != 'y')
				exit(0);
			std::cin.ignore(MAXLONGLONG, '\n');
		}
		++damage;
		return lvl;
	}

	void Atack(Mob& mob)
	{
		float hits = this->damage * (float(rand()) / RAND_MAX);
		std::cout << "You hit " << *mob.GetName() << " with " << hits << " damage\n";
		if (mob.GetHit(hits))
		{
			float regen = (25.0f - health) * (float(rand()) / RAND_MAX);
			std::cout <<
				"You killed " << *mob.GetName() << ", what a monster...\n" <<
				"You carve it and found " << mob.GetGold() << " gold inside (wtf?!)\n" <<
				"Your lvl is not " << IncLvl() << '\n' <<
				*mob.GetName() << " was tasty, it restored you " << regen << " health";
			this->gold += mob.GetGold();
			this->health += regen;
		}
		else
			GetHit(mob);
		std::cin.ignore(MAXLONGLONG, '\n');
	}

	bool RunFrom(Mob& mob)
	{
		if (rand() % 2 == 0)
		{
			std::cout << "You successfully ran from " << *mob.GetName() << "\n";
			std::cin.ignore(MAXLONGLONG, '\n');
			return true;
		}
		else
		{
			std::cout << "You can't run from your problems! This time was no exception...\n";
			GetHit(mob);
			std::cin.ignore(MAXLONGLONG, '\n');
			return false;
		}
	}

	void Print()
	{
		std::cout <<
			"Your lvl is " << lvl << '\n' <<
			"Your health is " << health << '\n' <<
			"You have " << gold << " gold\n";
	}
};


class Game
{
public:
	static int GetAct()
	{
		std::cout << "\nChose what to do:\n";
		std::cout << "f/1: Fight\n";
		std::cout << "r/2: Run\n";
		char act;
		std::cin >> act;
		std::cin.ignore(MAXLONGLONG, '\n');
		switch (act)
		{
		case '1':
		case 'f':
			return 1;
		case '2':
		case 'r':
			return 2;
		default:
			return 0;
		}
	}

};


#pragma region static init

HANDLE Console::out_handle = GetStdHandle(STD_OUTPUT_HANDLE);


Mob Mob::Mobs[3] = {
	//	symbol	says																																									health	damage	gold
	Mob('s',	"You entered a large dungeon room, and saw a pile of goo. It is moving to you,like slime would do",																	5.0f,	1.0f,	5),
	Mob('o',	"You walked along an abandoned mineshaft when a pickax came flying out of the darkness. You barely dodged it. Immediately after it the orc jumped out",					25.0f,	4.0f,	20),
	Mob('d',	"You entered a huge cave. You found big stone in the midle. When you climbed\nup on it to look around - the stone began to pour fire on you. Oooops, it was a dragon",	100.0f,	4.5f,	500)
};

#pragma endregion


int main()
{
	auto f = Coord;
	
	srand(int(time(0)));
	rand();

	/**/
	std::cout << "Hello Player, press Enter to start:";
	/**
	cout << "01234567890123456789\n";
	cout << "01234567890123456789\n";
	cout << "01234567890123456789\n";
	Console::Clear(Coord(6, 0), Coord(6, 2));
	/**/
	std::cin.ignore(MAXLONGLONG, '\n');
	Console::Clear();

	Player player;

	while (1)
	{
		Mob mob = Mob::GetNew();
		while (mob.IsAlive())
		{
			Console::Clear();
			player.Print();
			mob.Print();
			int act = Game::GetAct();
			while (!act)
			{
				Console::Clear();
				player.Print();
				mob.Print();
				std::cout << "\nInput was invalid!\n";
				act = Game::GetAct();
			}

			Console::Clear();
			player.Print();
			mob.Print();
			std::cout << "\nYou have chosen to " << ((act == 1) ? "fight" : "run") << '\n';
			if (act == 1)
				player.Atack(mob);
			else
				if (player.RunFrom(mob))
					break;
		}
	}
}

