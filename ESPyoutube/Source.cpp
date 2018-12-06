#include <iostream>
#include <Windows.h>
#include "ESP.h"
using namespace std;



DWORD procID;
HWND hWnd;
void FindGame()
{
	system("CLS");
	cout << "Looking for Call of Duty 4" << endl << endl;


	// Finding hWnd
	while (true)
	{
		hWnd = FindWindowA(0, ("Call of Duty 4"));
		if (hWnd)
			break;

		hWnd = FindWindowA(0, ("Call of Duty 4 X"));
		if (hWnd)
			break;

		Sleep(1000);
	}


	// Attach to Game //
	HDC hdc = GetDC(hWnd);
	GetWindowThreadProcessId(hWnd, &procID);
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	Drawing(hdc, pHandle);


	system("CLS");
	cout << "This hack includes: \n - ESP Boxes\n - TriggerBot\n - Aimbot\n\n";
	cout << "Press Up Arrow to enable / disable Triggerbot" << endl;
	cout << "Press End Key to change ESP settings" << endl << endl;
	cout << "Triggerbot Status:   ON" << endl;
}


int main()
{
	for (;;)
	{
		FindGame();





		//infinite loop
		while (hWnd == FindWindowA(0, ("Call of Duty 4")) || hWnd == FindWindowA(0, ("Call of Duty 4 X")))
		{
			Aimbot();

			Sleep(1);
		}
	}
}