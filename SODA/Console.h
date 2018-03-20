#pragma once
#include <iostream>

class Console abstract final
{
private:
	static HANDLE out_handle;

public:

	static void MoveTo(COORD c);

	static void MoveTo(__int16 x, __int16 y);


	static void WaitInput();


	static void Clear(COORD from, COORD to);

	static void Clear();

};
