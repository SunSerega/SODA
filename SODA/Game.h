#pragma once
#include "PlayerMob.h"

class Game abstract final
{
public:


#pragma region 0


	static int ReadAct();

	static int GetAct(int y);

	static void ClearFRChoise(int y);

	static void SayWinThing(Player& player);


#pragma endregion

#pragma region 1


	static void MobDeath(Player & player, Mob & mob);
	static void PlayerDeath(Player & player, Mob & mob);
	static void PlayerDeath(Player & player);

	static bool Atack(Player& player, Mob& mob);
	static bool Atack(Mob& mob, Player& player);

	static void AtackMob(Player& player, Mob& mob);
	static bool FleeMob(Player& player, Mob& mob);

	static void Heal(Player& player, Mob& mob);

	static bool FaceMob(Player& player, Mob& mob);


#pragma endregion

#pragma region 2


	static void StartLoop();


#pragma endregion

};
