#include "stdafx.h"
#include "PlayerMob.h"

#pragma region Mob


const char* slime_says =	"You entered a large dungeon room, and saw a pile of goo. It is moving to you,like slime would do";
const char* orc_says =		"You walked along an abandoned mineshaft when a pickax came flying out of the darkness. You barely dodged it. Immediately after it the orc jumped out";
const char* dragom_says =	"You entered a huge cave. You found big stone in the midle. When you climbed\nup on it to look around - the stone began to pour fire on you. Oooops, it was a dragon";

Mob Mob::Mobs[3] = {
	//	symbol	says			health	damage	gold
	Mob('s',	slime_says,		5.0f,	1.0f,	5),
	Mob('o',	orc_says,		25.0f,	4.0f,	20),
	Mob('d',	dragom_says,	100.0f,	4.5f,	500)
};

const char* Mob::SlimeHealText[3]{
	"This slime wasn't tasty... I mean even less tasty then normal slime. It healed  you only ",
	"This slime tasted ok for a slime. It healed you ",
	"This slime was surprisingly tasty! It healed you "
};
const char* Mob::OrcHealText[3]{
	"You spend all your salt on preveus mob, this orc wasn't too good... He's meat\nhealed you only ",
	"This orc's meat was ok-ish. It healed you ",
	"This orc was delisius! It healed you "
};
const char* Mob::DragonHealText[3]{
	"There was a lot of dragon meat... Not too tasty thow, you wasn't able too it much.  It healed you only ",
	"There was a lot of dragon meat... It healed you ",
	"There was a lot of dragon meat... It was very tasty! It healed you\n"
};

const float Mob::SlimeHealMax[3]	{3.0f,	5.5f,	8.0f};
const float Mob::OrcHealMax[3]		{8.0f,	13.5f,	16.0f};
const float Mob::DragonHealMax[3]	{15.0f,	20.0f,	25.0f};


bool Mob::GetHit(float hits)
{
	health -= hits;
	return (health <= 0);
}

char Mob::GetSym()
{
	return sym;
}

float Mob::GetHealth()
{
	return health;
}


#pragma endregion

#pragma region Player


bool Player::GetHit(float hits)
{
	health -= hits;
	return (health <= 0);
}

float Player::AddHealth(float heal)
{
	if (heal > 25 - health) heal = 25 - health;
	health += heal;
	return heal;
}

int Player::GetGold()
{
	return gold;
}

void Player::AddGold(int gold)
{
	this->gold += gold;
}

int Player::GetLvl()
{
	return lvl;
}

float Player::GetDamage()
{
	return damage;
}

int Player::IncLvl()
{
	++lvl;
	++damage;
	return lvl;
}

void Player::Poisen()
{
	poisened = true;
}

bool Player::IsPoisened()
{
	return poisened;
}

void Player::UnPoisen()
{
	poisened = false;
}

void Player::BreakSword()
{
	++sword_breaks;
}

int Player::GetSwordBreaks()
{
	return sword_breaks;
}

void Player::RepearSword()
{
	sword_breaks = 0;
}

void Player::Print()
{
	std::cout <<
		"Your lvl is " << lvl << '\n' <<
		"Your health is " << health << '\n' <<
		"You have " << gold << " gold\n";
	if (sword_breaks)
		std::cout << "Your sword broken in " << sword_breaks << " place(s)\n";
}


#pragma endregion
