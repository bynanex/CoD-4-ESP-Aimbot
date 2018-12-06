#pragma once
#include "Player.h"
#include <vector>
#include <algorithm>
#define MAX 50;
#define Health 100;



void esp();
void Aimbot();
void Drawing(HDC hdc, HANDLE phandle);
Vector SubVectorDist(Vector &playerFrom, Vector &playerTo);
bool WorldToScreen(Vector &WorldLoc, Vector &pos);
void Angles();

//void DrawFilledRct(HDC Desktop, HBRUSH hbrush, int x, int y, int w, int h);

void UpdateRes();
//float Get3dDistance(PlayerD to, PlayerD from);
//int FindClosest(PlayerD * enemiesData, int enemiesLength, PlayerD myPos);
	
	//void DrawBorder(HDC Desktop, HBRUSH hbrush, int x, int y, int w, int h, int thickness);


// RPM / WPM Templates
template<class TYPE>
TYPE Read(DWORD address) {
	TYPE buffer;
	ReadProcessMemory(pHandle, (LPVOID)address, &buffer, sizeof(TYPE), 0);
	return buffer;
}

template<class TYPE>
void Write(DWORD address, TYPE dataToWrite) {
	WriteProcessMemory(pHandle, (LPVOID)address, &dataToWrite, sizeof(TYPE), 0);
}
//
//
//
//
//
//
//bool calcAngle(Vector PlayerPos, Vector EnemyPos, float AimbotFOV)
//{
//	Vector AngleToEnemy;
//	float Distance = Get3dDistance(PlayerPos, EnemyPos);
//
//	// This is old method
//	AngleToEnemy.x = -asin((EnemyPos.z - PlayerPos.z) / Distance) * 180 / 3.14159265359;
//	AngleToEnemy.y = atan2(EnemyPos.y - PlayerPos.y, EnemyPos.x - PlayerPos.x) * 180 / 3.14159265359;
//	AngleToEnemy.z = 0;
//
//
//	// This is new method, couldn't get to work though
//	//AngleToEnemy.x = (-(float)atan2(EnemyPos.x - PlayerPos.x, EnemyPos.y - PlayerPos.y)) / PI * 180.0f;
//	//AngleToEnemy.y = (float)(atan2(EnemyPos.z - PlayerPos.z, Get3dDistance(PlayerPos, EnemyPos))) * 180.0f / PI;
//	//cout << " Current View:		" << viewAngles.y << endl;
//	//cout << " To Enemy View:	" << AngleToEnemy.y << endl;
//
//
//
//	Vector fovDifference = SubVectorDist(viewAngles_FloatingSight, AngleToEnemy);
//	//cout << " Difference yView:	" << fovDifference.y << endl;
//
//
//	if (fovDifference.x > 180)
//		fovDifference.x = (fovDifference.x - 360);
//
//	if (fovDifference.y > 180)
//		fovDifference.y = (fovDifference.y - 360);
//
//
//
//	//cout << "\nX-Diff:	" << fovDifference.x;
//	//cout << "\nY-Diff:	" << fovDifference.y;
//
//	//AimbotFOV = ( AimbotFOV / ((SubVectorDist(PlayerPos, EnemyPos).length() / 60) / 3));
//	AimbotFOV = (AimbotFOV / 2);
//
//
//	if (fovDifference.y < AimbotFOV && fovDifference.y > -AimbotFOV && fovDifference.x < (AimbotFOV + 1) && fovDifference.x > -AimbotFOV)
//		return true;
//
//	else
//		return false;
//}
//
//void AimAtEnemy(Vector PlayerPos, Vector EnemyPos, float AimbotFOV, float SmoothFloat)
//{
//	Vector AngleToEnemy;
//	float Distance = Get3dDistance(PlayerPos, EnemyPos);
//
//	AngleToEnemy.x = -asin((EnemyPos.z - PlayerPos.z) / Distance) * 180 / 3.14159265359;
//	AngleToEnemy.y = atan2(EnemyPos.y - PlayerPos.y, EnemyPos.x - PlayerPos.x) * 180 / 3.14159265359;
//	AngleToEnemy.z = 0;
//
//	Vector fovDifference = SubVectorDist(viewAngles_FloatingSight, AngleToEnemy);
//
//
//
//	if (fovDifference.x > 180)
//		fovDifference.x = (fovDifference.x - 360);
//
//	if (fovDifference.y > 180)
//		fovDifference.y = (fovDifference.y - 360);
//
//	//AimbotFOV = ( AimbotFOV / ((SubVectorDist(PlayerPos, EnemyPos).length() / 60) / 3));
//	AimbotFOV = (AimbotFOV / 2);
//
//
//	if (SmoothFloat == 0)
//	{
//		Player.ClientAimAngles.x = (Player.ClientAimAngles.x - fovDifference.x);
//		Player.ClientAimAngles.y = (Player.ClientAimAngles.y - fovDifference.y);
//	}
//	else
//	{
//		Player.ClientAimAngles.x = (Player.ClientAimAngles.x - (fovDifference.x / SmoothFloat));
//		Player.ClientAimAngles.y = (Player.ClientAimAngles.y - (fovDifference.y / SmoothFloat));
//	}
//	Write<Vector>(0xC84FD8, Player.ClientAimAngles);
//}
//
//
//
//void TriggerBot()
//{
//	if (GetAsyncKeyState(VK_UP))
//	{
//		AutoShoot = !AutoShoot;
//		system("CLS");
//		cout << "Press Up Arrow to enable / disable Triggerbot" << endl;
//		cout << "Press End Key to change ESP settings" << endl << endl;
//
//		if (AutoShoot == true)
//			cout << "Triggerbot Status:   ON" << endl;
//		else
//			cout << "Triggerbot Status:   OFF" << endl;
//
//		while (GetAsyncKeyState(VK_UP))
//		{
//			Sleep(50);
//		}
//	}
//	if (AutoShoot == 1 && (GetKeyState(VK_RBUTTON) & 0x80) != 0 && (GetKeyState(VK_LBUTTON) & 0x80) == 0)
//	{
//		//Zombies 0x01C08B50       //Cod 4  00794484        2C3D822C
//		ReadProcessMemory(pHandle, (PBYTE*)(0x794484), &Triggerbot, sizeof(Triggerbot), NULL);
//		if (Triggerbot == 16 || Triggerbot == 272)
//		{
//			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
//			Sleep(3);
//			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
//		}
//	}
//}
//
//
//
//
//void Aimbot(/*int boneID*/)		// Aim at closest person to your crosshair within the AimbotFOV
//{
//	// Toggles
//	{
//		if (GetAsyncKeyState(VK_NUMPAD1))
//		{
//			EnemiesOnly = !EnemiesOnly;
//			while (GetAsyncKeyState(VK_NUMPAD1))
//			{
//				Sleep(10);
//			}
//		}
//		if (GetAsyncKeyState(VK_NUMPAD0))
//		{
//			ESPBOOL = !ESPBOOL;
//			while (GetAsyncKeyState(VK_NUMPAD0))
//			{
//				Sleep(10);
//			}
//		}
//		if (GetAsyncKeyState(VK_LEFT) && AimbotFOV > 0.05)
//			AimbotFOV -= 0.025f;
//		else if (GetAsyncKeyState(VK_RIGHT) && AimbotFOV < 90)
//			AimbotFOV += 0.025f;
//
//		if (GetAsyncKeyState(VK_NUMPAD4) && SmoothFloat > 0.05)
//			SmoothFloat -= 0.0250000f;
//		else if (GetAsyncKeyState(VK_NUMPAD4) && SmoothFloat < 1)
//			SmoothFloat = 0.0f;
//		else if (GetAsyncKeyState(VK_NUMPAD6) && SmoothFloat < 100)
//			SmoothFloat += 0.0250000f;
//	}
//
//
//	TriggerBot();
//	Player.inGame = Read<int>(0x74E34C);
//	if (Player.inGame == 0)
//		GDI::DrawString(hDC, BigFont, 150, 20, (RGB(255, 255, 0)), "Hello Hoganator52 :)");
//
//	else if (Player.inGame == 1 && ESPBOOL == true)
//		esp();
//
//	else
//	{
//		DrawSettings();
//		GDI::DrawString(hDC, Font, 350, 114, (RGB(255, 0, 0)), "ESP IS OFFLINE");
//	}
//
//	short int PlayersInGame = Read<short int>(0x774350);
//	PlayerD EntityArray[MAXPLAYERS];
//	short int EnemyCounter = 0;
//
//
//	while (GetAsyncKeyState(0x4C))
//	{
//		Player = GetPlayerInfo();
//
//		for (int x = 0; x <= MAXPLAYERS; x++)
//		{
//			CurrentEntity.valid = Read<int>(0x839270 + x * 0x4CC);
//			if (!CurrentEntity.valid) continue;
//
//			CurrentEntity.Alive = Read<bool>(0x84F2D8 + x * 0x1DC + 0x1C0);
//			if (CurrentEntity.Alive == false) continue;
//
//			CurrentEntity.team = Read<int>(0x839270 + x * 0x4CC + 0x20);
//			if (EnemiesOnly == true && CurrentEntity.team == Player.team) continue;
//
//
//			CurrentEntity.ClientNum = Read<int>(0x839270 + x * 0x4CC + 0x8);
//
//			CurrentEntity.Pos = Read<Vector>(0x84F2D8 + x * 0x1DC + 0x1C);
//			CurrentEntity.stance = Read<int>(0x839270 + x * 0x4CC + 0x470);
//			CurrentEntity.InLastStand = Read<int>(0x839270 + x * 0x4CC + 0x4A0);
//			if (CurrentEntity.InLastStand == 0)
//				CurrentEntity.Pos.z += CheckStance(CurrentEntity.stance) - 4;	// Subtracting this makes aimbot lower, helps not aim at top of helmet. Centers it
//			else	CurrentEntity.Pos.z += 11;
//
//
//
//			bool InFOV = calcAngle(Player.Pos, CurrentEntity.Pos, AimbotFOV);
//			if (!InFOV)		continue;
//			else
//			{
//				EntityArray[EnemyCounter] = CurrentEntity;
//				EnemyCounter++;
//			}
//		}
//
//		for (int x = 0; x < EnemyCounter; x++)
//		{
//
//			CurrentEntity.Alive = Read<bool>(0x84F2D8 + EntityArray[x].ClientNum * 0x1DC + 0x1C0);
//			if (CurrentEntity.Alive == 0)	continue;
//
//			Player = GetPlayerInfo();
//
//			EntityArray[x].Pos = Read<Vector>(0x84F2D8 + EntityArray[x].ClientNum * 0x1DC + 0x1C);
//			EntityArray[x].stance = Read<int>(0x839270 + EntityArray[x].ClientNum * 0x4CC + 0x470);
//			EntityArray[x].Pos.z += CheckStance(EntityArray[x].stance) - 4;	// Subtracting this makes aimbot aim lower, helps not aim at top of helmet. Centers it on body
//
//
//			AimAtEnemy(Player.Pos, EntityArray[x].Pos, AimbotFOV, SmoothFloat);
//
//
//
//
//
//
//
//		}
//		TriggerBot();
//
//		if (ESPBOOL == true)	esp();
//		else	DrawSettings();
//
//		Sleep(4);
//	}
//}