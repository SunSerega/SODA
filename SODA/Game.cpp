#include "stdafx.h"
#include "Game.h"
#include "Console.h"
#include "PlayerMob.h"



#pragma region 0


int Game::ReadAct()
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

int Game::GetAct(int y)
{
	int act = Game::ReadAct();
	while (!act)
	{
		Game::ClearFRChoise(y);
		std::cout << "Input was invalid!\n";
		act = Game::ReadAct();
	}
	Game::ClearFRChoise(y);
	return act;
}

void Game::ClearFRChoise(int y)
{
	Console::Clear(Coord(0, y), Coord(0, 20));
	Console::MoveTo(0, y);
}

void Game::SayWinThing(Player& player)
{
	std::cout <<
		"\nYou reached lvl 20!\n" <<
		"With that - you won the game, carrying home " << player.GetGold() << " gold\n"
		"y: continue\n" <<
		"every thing else: exit\n";
	char act;
	std::cin >> act;
	if (act != 'y')
		exit(0);
	Console::WaitInput();
}


#pragma endregion

#pragma region 1


void Game::MobDeath(Player & player, Mob & mob)
{
	std::cout <<
		"\nYou killed " << mob.GetName() << ", what a monster...\n" <<
		"You carve it and found " << mob.GetGold() << " gold inside (wtf?!)\n" <<
		"Your lvl is now " << player.IncLvl() << '\n';
}

void Game::PlayerDeath(Player & player, Mob & mob)
{
	std::cout <<
		"\nYou mystiryosly died in front of " << mob.GetName() << ".\n" <<
		"Last thing you remember was " << player.GetGold() << " gold, you will not have opportunity to spend...\n" <<
		"\nPress Enter to exit\n";
	Console::WaitInput();
	exit(0);
}

void Game::PlayerDeath(Player & player)
{
	std::cout <<
		"You died from poisen\n" <<
		"Last thing you remember was " << player.GetGold() << " gold, you will not have opportunity to spend...\n" <<
		"Press Enter to exit";
	Console::WaitInput();
	exit(0);
}

bool Game::Atack(Player & player, Mob & mob)
{
	if (player.GetSwordBreaks() >= 10)
	{
		std::cout << "Your sword is broken. You can't figth";
		return false;
	}
	float hits;
	switch (rand() % 5)
	{
	case 0:
		std::cout << "Your hit was slow and misereble\n";
		if (rand() % 3 == 0)
		{
			std::cout << mob.GetName() << " dodged it easely\n";
			return !mob.IsAlive();
		}
		hits = ((float(rand()) / RAND_MAX) * 0.1f + 0.0f) * player.GetDamage();
		break;
	case 1:
		std::cout << "Your hit was slow, but " << mob.GetName() << " wasn't paying enoght attention\n";
		hits = ((float(rand()) / RAND_MAX) * 0.2f + 0.1f) * player.GetDamage();
		break;
	case 2:
		std::cout << "Your hit was ok-ish\n";
		hits = ((float(rand()) / RAND_MAX) * 0.4f + 0.3f) * player.GetDamage();
		break;
	case 3:
		std::cout << "Your hit was prety good\n";
		hits = ((float(rand()) / RAND_MAX) * 0.2f + 0.7f) * player.GetDamage();
		break;
	case 4:
		std::cout << "Your hit was fast and powerfull\n";
		if (rand() % 3 == 0)
		{
			switch (mob.GetSym())
			{
			case 's':
				std::cout << "You managed to hit " << mob.GetName() << " rigth in he's core\n";
				break;
			case 'o':
				std::cout << "You managed to hit " << mob.GetName() << " rigth in he's hearth\n";
				break;
			case 'd':
				std::cout << "You managed to hit " << mob.GetName() << " rigth in he's g point. He поперхнулся своим же огнём and blow up\n";
				break;
			}
			mob.GetHit(mob.GetHealth());
			return !mob.IsAlive();
		}
		hits = ((float(rand()) / RAND_MAX) * 0.1f + 0.9f) * player.GetDamage();
		break;
	}

	if (player.GetSwordBreaks())
	{
		int mlt = 10 * (10 - player.GetSwordBreaks());
		std::cout << "Your sword is a bit broken, your damage is on " << mlt << "%\n";
		hits = hits * mlt / 100;
	}

	std::cout << "You hit " << mob.GetName() << " with " << hits << " damage\n";
	mob.GetHit(hits);

	return !mob.IsAlive();
}

bool Game::Atack(Mob & mob, Player & player)
{
	float hits;
	switch (rand() % 5)
	{
	case 0:
		std::cout << mob.GetName() << " tried as hard as he coud, but his attack was slow\n";
		if (rand() % 3 == 0)
		{
			std::cout << "Unfortunately " << mob.GetName() << " missed you\n";
			return false;
		}
		hits = ((float(rand()) / RAND_MAX) * 0.1f + 0.0f) * mob.GetDamage();
		break;
	case 1:
		std::cout << mob.GetName() << " tried as hard as he coud, but his attack was slow. You wasn't paying\nenoght attention, thou\n";
		hits = ((float(rand()) / RAND_MAX) * 0.2f + 0.1f) * mob.GetDamage();
		break;
	case 2:
		std::cout << mob.GetName() << "'s hit was ok-ish\n";
		hits = ((float(rand()) / RAND_MAX) * 0.4f + 0.3f) * mob.GetDamage();
		break;
	case 3:
		std::cout << mob.GetName() << "'s hit was prety good\n";
		hits = ((float(rand()) / RAND_MAX) * 0.2f + 0.7f) * mob.GetDamage();
		break;
	case 4:
		std::cout << mob.GetName() << "'s hit was fast and powerfull\n";
		if (rand() % 3 == 0)
		{
			switch (mob.GetSym())
			{
			case 's':
				std::cout << mob.GetName() << " managed to poisen you. You taking damage\n";
				player.Poisen();
				break;
			case 'o':
				std::cout << mob.GetName() << " managed to break your sword. Your damage decresed\n";
				player.BreakSword();
				break;
			case 'd':
				std::cout << mob.GetName() << " cooked you up a bit. -10 health\n";
				player.GetHit(10.0f);
				break;
			}
			if (!player.IsAlive())
				return true;
		}
		hits = ((float(rand()) / RAND_MAX) * 0.1f + 0.9f) * mob.GetDamage();
		break;
	}
	std::cout << mob.GetName() << " hit you with " << hits << " damage\n";
	player.GetHit(hits);

	return !player.IsAlive();
}

void Game::AtackMob(Player & player, Mob & mob)
{
	std::cout << "You have chosen to fight\n\n";
	if (Game::Atack(player, mob))
	{
		Game::MobDeath(player, mob);
		return;
	}
	std::cout << "\n";
	if (Game::Atack(mob, player))
	{
		Game::PlayerDeath(player, mob);
		return;
	}
}

bool Game::FleeMob(Player & player, Mob & mob)
{
	std::cout << "You have chosen to run\n\n";
	if (rand() % 2 == 0)
	{
		std::cout << "You can't run from your problems! This time was no exception...\n\n";
		if (Game::Atack(mob, player))
			Game::PlayerDeath(player, mob);
		return false;
	}
	else
	{
		std::cout << "You successfully escaped " << mob.GetName() << "\n";
		return true;
	}
}

void Game::Heal(Player& player, Mob & mob)
{
	int food = rand() % 3;
	switch (mob.GetSym())
	{
		float heal;
	case 's':
		heal = Mob::SlimeHealMax[food] * (0.75f + (float(rand() / RAND_MAX / 2)));
		std::cout << '\n' << Mob::SlimeHealText[food] << player.AddHealth(heal) << " health\n";
		break;
	case 'o':
		heal = Mob::OrcHealMax[food] * (0.75f + (float(rand() / RAND_MAX / 2)));
		std::cout << '\n' << Mob::OrcHealText[food] << player.AddHealth(heal) << " health\n";
		break;
	case 'd':
		heal = Mob::DragonHealMax[food] * (0.75f + (float(rand() / RAND_MAX / 2)));
		std::cout << '\n' << Mob::DragonHealText[food] << player.AddHealth(heal) << " health\n";
		break;
	}
}

bool Game::FaceMob(Player & player, Mob & mob)
{
	Console::Clear();
	player.Print();
	mob.Print();
	int act = Game::GetAct(
		((mob.GetSym() == 'd') ? 9 : 8) +
		((player.GetSwordBreaks()) ? 1 : 0)
	);//а отсюда ничинается моя костыльная карьера...
	if (act == 1)
	{
		Game::AtackMob(player, mob);
		return false;
	}
	else
	{
		return Game::FleeMob(player, mob);
	}

}


#pragma endregion

#pragma region 2



void Game::StartLoop()
{
	std::cout << "Hello Player, press Enter to start:";
	std::cin.ignore(MAXLONGLONG, '\n');
	Console::Clear();

	Player player;

	while (1)
	{
		Mob mob = Mob::GetNew();

		while (mob.IsAlive())
		{
			if (Game::FaceMob(player, mob))
				break;

			if (player.IsPoisened())
			{
				std::cout << "\nYou took poisen damage\n";
				player.GetHit(1.0f);
				if (!player.IsAlive())
					PlayerDeath(player);
				if (rand() % 3 == 0)
				{
					std::cout << "You are not poisened anymore\n";
					player.UnPoisen();
				}
			}

			if (mob.IsAlive())
				Console::WaitInput();
		}

		if (!mob.IsAlive())
		{
			Game::Heal(player, mob);
			player.AddGold(mob.GetGold());
		}

		if (player.GetLvl() == 20)
			Game::SayWinThing(player);

		if (player.IsPoisened())
		{
			std::cout << "\nYou are not poisened anymore\n";
			player.UnPoisen();
		}

		if (player.GetSwordBreaks())
			if (rand() % 5 == 0)
			{
				std::cout << "\nYou finally repeared your sword\n";
				player.RepearSword();
			}

		Console::WaitInput();
	}
}


#pragma endregion

