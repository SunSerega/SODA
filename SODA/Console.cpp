#include "stdafx.h"
#include "Console.h"


HANDLE Console::out_handle = GetStdHandle(STD_OUTPUT_HANDLE);


void Console::MoveTo(COORD c)
{
	SetConsoleCursorPosition(out_handle, c);
}

void Console::MoveTo(__int16 x, __int16 y)
{
	return MoveTo(Coord(x, y));
}

void Console::WaitInput()
{
	std::cin.ignore(MAXLONGLONG, '\n');
}


void Console::Clear(COORD from, COORD to)
{
	if (from.Y > to.Y) return;
	MoveTo(from);
	std::cout << std::string(
		to.X - from.X +
		80 * (to.Y - from.Y),
		' '
	);
}

void Console::Clear()
{
	system("cls");
}
