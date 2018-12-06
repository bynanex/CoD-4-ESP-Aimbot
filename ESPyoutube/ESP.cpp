#include "ESPVar.h"
#include "ESP.h"
#include "DrawGDI.h"
#include <Windows.h>
#include <iostream>
using std::cout;
bool AutoShoot = false;
int Triggerbot = 0;
bool EnemiesOnly = true;
float AimbotFOV = 2.5;
float SmoothFloat = 18;
bool ESPBOOL = true;



void Drawing(HDC hdc, HANDLE phandle)
{
	hDC = hdc;
	pHandle = phandle;
}

void DrawSettings()
{
	if (AutoShoot == true)
		GDI::DrawString(hDC, Font, 100, 300, (RGB(255, 158, 0)), "Triggerbot:   ON");
	else
		GDI::DrawString(hDC, Font, 100, 300, (RGB(255, 158, 0)), "Triggerbot:   OFF");

	if (EnemiesOnly == true)
		GDI::DrawString(hDC, Font, 100, 325, (RGB(255, 158, 0)), "Enemies Only:   ON");
	else
		GDI::DrawString(hDC, Font, 100, 325, (RGB(255, 158, 0)), "Enemies Only:   OFF");

	std::string AIMBOTSTRING = "Aimbot FOV:   " + std::to_string((float)AimbotFOV);
	GDI::DrawString(hDC, Font, 350, 82, (RGB(0, 0, 250)), AIMBOTSTRING.c_str());

	std::string SMOOTHSTRING = "Smooth FOV:   " + std::to_string((float)SmoothFloat);
	GDI::DrawString(hDC, Font, 350, 98, (RGB(0, 0, 250)), SMOOTHSTRING.c_str());

	fov[0] = Read<float>(0x797610);
	GDI::DrawAimbotFOV(hDC, (resolution[0] / 2), resolution[1] / 2, AimbotFOV, fov[0], RGB(50, 50, 255));
}



void UpdateRes()
{
	ReadProcessMemory(pHandle, (LPVOID)0xD573F34, &resolution[0], 8, NULL);
	GotResolution = true;
}



float CheckStance(int stance)
{
	float height; // height of player's eyes
	if (stance == 2 || stance == 1024 || stance == 2048 || stance == 1048576 || stance == 0 || stance == 16 || stance == 32)	// 1048576 is sprinting		0 is broken ankles		There's a lot of different values for mounting objects
		height = 60; // Standing
	else if (stance == 4 || stance == 4096 || stance == 8192 || stance == 64 || stance == 128)	// last two are moving while aiming
		height = 40;	//Crouching
	else if (stance == 8 || stance == 256 || stance == 512)
		height = 21;	// Prone is actually 11 but it fucks the box.
	else
		height = 50;	// Climbing or anything I didn't find.

	return height;
}

PlayerD GetPlayerInfo()
{
	PlayerD playerDD;
	//playerDD.inGame = Read<int>(0x74E34C);		Works but only check once, no point in reading every time
	playerDD.ClientNum = Read<int>(0x74E338);
	playerDD.team = Read<int>(0x839270 + playerDD.ClientNum * 0x4CC + 0x20);
	playerDD.Alive = Read<bool>(0x84F2D8 + playerDD.ClientNum * 0x1DC + 0x1C0);


	//playerDD.Killstreak = Read<int>(0x16DFBB4);
	//playerDD.EntityListViewAngles = Read<Vector>(0x839270 + playerDD.ClientNum * 0x4CC + 3E4)    // View Angles of Enemies



	fov[0] = Read<float>(0x797610);
	fov[1] = Read<float>(0x797614);



	viewAngles = Read<Vector>(0x79B698);
	viewAngles_FloatingSight = Read<Vector>(0x79E76C);

	playerDD.ClientAimAngles = Read<Vector>(0xC84FD8);
	
	


	playerDD.Pos = Read<Vector>(0x84F2D8 + playerDD.ClientNum * 0x1DC + 0x1C);
	playerDD.stance = Read<int>(0x839270 + playerDD.ClientNum * 0x4CC + 0x470);

	playerDD.InLastStand = Read<int>(0x839270 + playerDD.ClientNum * 0x4CC + 0x4A0);
	if (playerDD.InLastStand == 0)
		playerDD.Pos.z += CheckStance(playerDD.stance);
	else if (playerDD.InLastStand == 1)
		playerDD.Pos.z += 11;	// 11 is the prone height.


	//playerDD.WeaponInHandsID = Read<int>(0x839270 + playerDD.ClientNum * 0x4CC + 0x4AC)

	//playerDD.IsShooting = Read<int>(0x839270 + playerDD.ClientNum * 0x4CC + 0x488)
	//playerDD.IsADS = Read<int>(0x839270 + playerDD.ClientNum * 0x4CC + 0x490)


	return playerDD;
}



Vector SubVectorDist(Vector &Vec1, Vector &Vec2)
{
	return Vector(Vec1.x - Vec2.x, Vec1.y - Vec2.y, Vec1.z - Vec2.z);
}

float Get3dDistance(Vector to, Vector from)
{
	return (sqrtf(
		((to.x - from.x) * (to.x - from.x)) +
		((to.y - from.y) * (to.y - from.y)) +
		((to.z - from.z) * (to.z - from.z))
	));
}




bool OnlyEnemies = false;
int Target = -1;
void Changes()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_RETURN))
			break;
		if (GetAsyncKeyState(VK_DELETE))
		{
			int enemycounter = 0;
			PlayerD EntityArray[50];

			for (int x = 0; x < 50; x++)
			{
				PlayerD Entity;

				Entity.valid = Read<int>(0x839270 + x * 0x4CC);
				if (Entity.valid == 1)
				{
					Entity.ClientNum = Read<int>(0x84F2D8 + x * 0x1DC + 0xCC);
					ReadProcessMemory(pHandle, (LPVOID)(0x839270 + x * 0x4CC + 0xC), &Entity.PlayerName, sizeof(Entity.PlayerName), NULL);
					cout << Entity.ClientNum << endl << Entity.PlayerName << endl << endl;


					EntityArray[enemycounter] = Entity;
					enemycounter++;
				}
			}
			cout << "Who is your Target:	";
			cin >> Target;
			break;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			OnlyEnemies = !OnlyEnemies;
			if (OnlyEnemies == true)
				cout << "Enemies Only\n";
			else
				cout << "All players\n";
		}

		Sleep(100);
	}





	system("CLS");
	cout << "Press Up Arrow to enable / disable Triggerbot" << endl;
	cout << "Press End Key to change ESP settings" << endl << endl;
	Sleep(100);
}


PlayerD Player;
PlayerD CurrentEntity;
void esp()
{
	#define MAXPLAYERS 50
	PlayerD EntityArray[MAXPLAYERS];
	PlayerD Spectators[MAXPLAYERS];
	short int enemycounter = 0;
	short int SpectatorCounter = 0;

	// This is the instructions on how to use everything.
	if (GetAsyncKeyState(VK_END))
	{
		system("CLS");
		cout << "--------------------------------" << endl << "Make your ESP changes" << endl << "--------------------------------" << endl << endl;
		cout << "Press the Home Key when you are done making changes" << endl << endl;
		cout << " - Press Down for Team ESP\n";
		cout << " - Press Delete to select one player to follow\n";
		cout << " - Press Enter to return to hacking!\n";

		Changes();
	}

	if (!GotResolution)	UpdateRes();
	short int PlayersInGame = Read<short int>(0x774350);


	Player = GetPlayerInfo();
	if (Player.Alive == 0)
		Player.Pos = Read<Vector>(0x797618);

	// Scan through (potentially) 64 entities. Break once you've found them all (PlayersInGame)
	for (int x = 0; x < MAXPLAYERS; x++)
	{
		CurrentEntity.valid = Read<int>(0x839270 + x * 0x4CC);
		if (!CurrentEntity.valid) continue;

		CurrentEntity.ClientNum = Read<int>(0x84F2D8 + x * 0x1DC + 0xCC);
		if (CurrentEntity.ClientNum == Player.ClientNum) continue;

		CurrentEntity.team = Read<int>(0x839270 + x * 0x4CC + 0x20);
		if (CurrentEntity.team == 3)
		{
			ReadProcessMemory(pHandle, (LPVOID)(0x839270 + x * 0x4CC + 0xC), &CurrentEntity.PlayerName, sizeof(CurrentEntity.PlayerName), NULL);			
			Spectators[SpectatorCounter] = CurrentEntity;
			SpectatorCounter ++;
			continue;
		}

		CurrentEntity.Alive = Read<bool>(0x84F2D8 + x * 0x1DC + 0x1C0);
		if (CurrentEntity.Alive == 0) continue;

		if (OnlyEnemies == true && CurrentEntity.team == Player.team)	continue;



		// Read Name
		ReadProcessMemory(pHandle, (LPVOID)(0x839270 + x * 0x4CC + 0xC), &CurrentEntity.PlayerName, sizeof(CurrentEntity.PlayerName), NULL);

		// Read Team, Position, and Stance -> (Standing, Kneeling, Prone)
		CurrentEntity.Pos = Read<Vector>(0x84F2D8 + x * 0x1DC + 0x1C);
		CurrentEntity.stance = Read<int>(0x839270 + x * 0x4CC + 0x470);	
		CurrentEntity.Pos.z += CheckStance(CurrentEntity.stance) - 10;  // Lowers Box so that it centers on body.

		


		

		EntityArray[enemycounter] = CurrentEntity;
		enemycounter++;
		if (enemycounter > PlayersInGame)
			continue;
	}

	
	float dist, drawx, drawy;

	//** Drawing loop here *** 
	for (int x = 0; x <= enemycounter; x++)
	{
		dist = SubVectorDist(Player.Pos, EntityArray[x].Pos).length() / 60;

		if (WorldToScreen(EntityArray[x].Pos, Player.Pos))
		{
			// Draw height and width of box based on stance
			if (EntityArray[x].stance == 8 || EntityArray[x].stance == 256 || EntityArray[x].stance == 512)	// Prone
			{
				drawx = 300.0f / dist / fov[0];
				drawy = 150.0f / dist / fov[0];
			}
			else if (EntityArray[x].stance == 4 || EntityArray[x].stance == 4096 || EntityArray[x].stance == 8192)	// Crouching
			{
				drawx = 225.0f / dist / fov[0];
				drawy = 300.0f / dist / fov[0];
			}
			else 		//Standing
			{
				drawx = 150.0f / dist / fov[0];
				drawy = 300.0f / dist / fov[0];
			}



			//Get top left of ESP box
			tagPOINT tl;
			tl.x = ScreenX - drawx / 2;
			tl.y = ScreenY;


			

			COLORREF color = Player.team == EntityArray[x].team ? FriendlyCol : EnemyCol;
			if (EntityArray[x].ClientNum == Target)//Target
			{
				color = TargetCol;

				//Draw ESP BOX
				GDI::DrawRect(hDC, tl.x, tl.y, (tl.x + drawx), (tl.y + drawy), color);

				//GDI::DrawCircle(hDC, (tl.x + 0.25 * drawx), tl.y - drawy * 0.13, (tl.x + 0.75 * drawx), (tl.y + (drawy * 0.13)), color);

				//Draw snap line
				GDI::DrawLine(hDC, resolution[0] / 2, resolution[1], tl.x + (drawx /2), tl.y + drawy, color);
								
				//Draw Distance & Name
				std::string nameNdistance = std::string(EntityArray[x].PlayerName) + " ( " + std::to_string((int)floorf(dist)) + "m )";
				GDI::DrawString(hDC, Font, tl.x, tl.y - 25, color, nameNdistance.c_str());
			}
			else if (dist <= 15 && Player.team != EntityArray[x].team)
			{
				color = EnemyCloseCol;
				//Draw ESP BOX
				GDI::DrawRect(hDC, tl.x, tl.y, (tl.x + drawx), (tl.y + drawy), color);

				//GDI::DrawCircle(hDC, (tl.x + 0.25 * drawx), tl.y - drawy * 0.13, (tl.x + 0.75 * drawx), (tl.y + (drawy * 0.13)), color);

				std::string nameNdistance = std::string(EntityArray[x].PlayerName) + " ( " + std::to_string((int)floorf(dist)) + "m )";
				GDI::DrawString(hDC, Font, tl.x, tl.y - 25, color, nameNdistance.c_str());
			}
			else
			{
				if (EnemiesOnly == false)
					color = RGB(255, 60, 0);
				//Draw ESP BOX
				GDI::DrawRect(hDC, tl.x, tl.y, (tl.x + drawx), (tl.y + drawy), color);

				//GDI::DrawCircle(hDC, (tl.x + 0.25 * drawx), tl.y - drawy * 0.13, (tl.x + 0.75 * drawx), (tl.y + (drawy * 0.13)), color);

				//Draw snap line
				//GDI::DrawLine(hDC, resolution[0] / 2, resolution[1], tl.x + (drawx /2), tl.y + drawy, color);

				//Draw Distance & Name
				//std::string nameNdistance = std::string(Entities[x].PlayerName) + " ( " + std::to_string((int)floorf(dist)) + "m )";
				//GDI::DrawString(hDC, Font, tl.x, tl.y - 25, color, nameNdistance.c_str());
			}
		}
	}

	// Draw Standard crosshair
	//GDI::DrawLine(hDC, (resolution[0] / 2 - 16), (resolution[1] / 2 - 4), (resolution[0] / 2 + 14), (resolution[1] / 2 - 4), (RGB(0, 255, 0)));
	//GDI::DrawLine(hDC, (resolution[0] / 2 - 1), (resolution[1] / 2 - 20), (resolution[0] / 2 - 1), (resolution[1] / 2 + 10), (RGB(0, 255, 0)));
	// Draw Triangle crosshair
	//{
	//	GDI::DrawLine(hDC, (resolution[0] / 2 - 8), (resolution[1] / 2 + 1), (resolution[0] / 2 + 7), (resolution[1] / 2 + 1), (RGB(255, 10, 0)));
	//	GDI::DrawLine(hDC, (resolution[0] / 2 + 0), (resolution[1] / 2 - 12), (resolution[0] / 2 + 7), (resolution[1] / 2 + 1), (RGB(255, 10, 0)));
	//	GDI::DrawLine(hDC, (resolution[0] / 2 + 0), (resolution[1] / 2 - 12), (resolution[0] / 2 - 8), (resolution[1] / 2 + 1), (RGB(255, 10, 0)));
	//}
	
	


	DrawSettings();
	// Draw Spectators
	if (SpectatorCounter != 0)
	{
		GDI::DrawString(hDC, Font, 400, 50, (RGB(255, 40, 0)), "Spectators:   ");
		for (int x = 0; x < SpectatorCounter; x++)
			GDI::DrawString(hDC, Font, 500 + (x * 100), 50, (RGB(255, 40, 0)), Spectators[x].PlayerName);
	}


	// Only works in bot match
	//std::string KillstreakString = std::string(Player.Kills) + std::to_string(Player.Killstreak);
	//GDI::DrawString(hDC, Font, 100, 325, (RGB(255, 158, 0)), KillstreakString.c_str());	
}























#define PI 3.1415927f

bool calcAngle(Vector PlayerPos, Vector EnemyPos, float AimbotFOV, float SmoothFloat)
{
	Vector AngleToEnemy;
	float Distance = Get3dDistance(PlayerPos, EnemyPos);

	// This is old method
	AngleToEnemy.x = -asin((EnemyPos.z - PlayerPos.z) / Distance) * 180 / 3.14159265359;
	AngleToEnemy.y = atan2(EnemyPos.y - PlayerPos.y, EnemyPos.x - PlayerPos.x) * 180 / 3.14159265359;
	AngleToEnemy.z = 0;

	
	//AngleToEnemy.x = (-(float)atan2(EnemyPos.x - PlayerPos.x, EnemyPos.y - PlayerPos.y)) / PI * 180.0f;
	//AngleToEnemy.y = (float)(atan2(EnemyPos.z - PlayerPos.z, Get3dDistance(PlayerPos, EnemyPos))) * 180.0f / PI;
	//cout << " Current View:		" << viewAngles.y << endl;
	//cout << " To Enemy View:	" << AngleToEnemy.y << endl;



	Vector fovDifference = SubVectorDist(viewAngles_FloatingSight, AngleToEnemy);
	//cout << " Difference View:	" << fovDifference.y << endl;


	if (fovDifference.x > 180)
		fovDifference.x = (fovDifference.x - 360);

	if (fovDifference.y > 180)
		fovDifference.y = (fovDifference.y - 360);



	//cout << "\nX-Diff:	" << fovDifference.x;
	//cout << "\nY-Diff:	" << fovDifference.y;

	//AimbotFOV = ( AimbotFOV / ((SubVectorDist(PlayerPos, EnemyPos).length() / 60) / 3));
	AimbotFOV = (AimbotFOV / 2);


	if (fovDifference.y < AimbotFOV && fovDifference.y > -AimbotFOV && fovDifference.x < (AimbotFOV + 1) && fovDifference.x > -AimbotFOV)
	{	
		if (SmoothFloat == 0)
		{
			Player.ClientAimAngles.x = (Player.ClientAimAngles.x - fovDifference.x);
			Player.ClientAimAngles.y = (Player.ClientAimAngles.y - fovDifference.y);
		}
		else
		{//float Smooth = (1 + (1 / SmoothFloat));
			Player.ClientAimAngles.x = (Player.ClientAimAngles.x - (fovDifference.x / SmoothFloat));
			Player.ClientAimAngles.y = (Player.ClientAimAngles.y - (fovDifference.y / SmoothFloat));
		}
		Write<Vector>(0xC84FD8, Player.ClientAimAngles);		//Write<float>(0xC84FDC, Player.ClientAimAngles.y);
		return true;
	}

	else 
		return false;
}




void TriggerBot()
{
	if (GetAsyncKeyState(VK_UP))
	{
		AutoShoot = !AutoShoot;
		system("CLS");
		cout << "Press Up Arrow to enable / disable Triggerbot" << endl;
		cout << "Press End Key to change ESP settings" << endl << endl;

		if (AutoShoot == true)
			cout << "Triggerbot Status:   ON" << endl;
		else
			cout << "Triggerbot Status:   OFF" << endl;

		while (GetAsyncKeyState(VK_UP))
		{
			Sleep(50);
		}
	}
	if (AutoShoot == 1 && (GetKeyState(VK_RBUTTON) & 0x80) != 0 && (GetKeyState(VK_LBUTTON) & 0x80) == 0)
	{
		//Zombies 0x01C08B50       //Cod 4  00794484        2C3D822C
		ReadProcessMemory(pHandle, (PBYTE*)(0x794484), &Triggerbot, sizeof(Triggerbot), NULL);
		if (Triggerbot == 16 || Triggerbot == 272)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(3);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
}




void Aimbot(/*int boneID*/)
{
	// Toggles
	{
		if (GetAsyncKeyState(VK_NUMPAD1))
		{
			EnemiesOnly = !EnemiesOnly;
			while (GetAsyncKeyState(VK_NUMPAD1))
			{
				Sleep(10);
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD0))
		{
			ESPBOOL = !ESPBOOL;
			while (GetAsyncKeyState(VK_NUMPAD0))
			{
				Sleep(10);
			}
		}
		if (GetAsyncKeyState(VK_LEFT) && AimbotFOV > 0.05)			AimbotFOV -= 0.025f;
		else if (GetAsyncKeyState(VK_RIGHT) && AimbotFOV < 90)		AimbotFOV += 0.025f;

		if (GetAsyncKeyState(VK_NUMPAD4) && SmoothFloat > 1)		SmoothFloat -= 0.0250000f;
		else if (GetAsyncKeyState(VK_NUMPAD4) && SmoothFloat <= 1)	SmoothFloat = 0.0f;
		else if (GetAsyncKeyState(VK_NUMPAD6) && SmoothFloat < 100)	SmoothFloat += 0.0250000f;
	}

	
	TriggerBot();
	Player.inGame = Read<int>(0x74E34C);
	if (Player.inGame == 0)
		GDI::DrawString(hDC, BigFont, 150, 20, (RGB(255, 255, 0)), "Hello Hoganator52 :)");

	else if (Player.inGame == 1 && ESPBOOL == true)
		esp();

	else
	{
		DrawSettings();
		GDI::DrawString(hDC, Font, 350, 114, (RGB(255, 0, 0)), "ESP IS OFFLINE");
	}


	if (GetAsyncKeyState('L'))
	{
		for (int x = 0; x < MAXPLAYERS; x++)
		{
			CurrentEntity.valid = Read<int>(0x839270 + x * 0x4CC);
			if (!CurrentEntity.valid) continue;

			CurrentEntity.Alive = Read<bool>(0x84F2D8 + x * 0x1DC + 0x1C0);
			if (CurrentEntity.Alive == false) continue;

			CurrentEntity.team = Read<int>(0x839270 + x * 0x4CC + 0x20);
			if (EnemiesOnly == true && CurrentEntity.team == Player.team) continue;


			while (GetAsyncKeyState('L') && CurrentEntity.Alive == true)
			{
				Player = GetPlayerInfo();
				CurrentEntity.Pos = Read<Vector>(0x84F2D8 + x * 0x1DC + 0x1C);
				CurrentEntity.stance = Read<int>(0x839270 + x * 0x4CC + 0x470);
				CurrentEntity.Pos.z += CheckStance(CurrentEntity.stance) - 4;	// Subtracting this makes aimbot lower, helps not aim at top of helmet. Centers it


				bool InFOV = calcAngle(Player.Pos, CurrentEntity.Pos, AimbotFOV, SmoothFloat);
				if (!InFOV)		break;











				TriggerBot();

				if (ESPBOOL == true)	esp();
				else	DrawSettings();

				CurrentEntity.Alive = Read<bool>(0x84F2D8 + x * 0x1DC + 0x1C0);
				Sleep(1);
			}
		}
	}

}








//Cod 4 Wold to screen
bool WorldToScreen(Vector &dst, Vector &src)
{
	Vector vLocal, vTransForm;
	vForward = new Vector();
	vRight = new Vector();
	vUpward = new Vector();

	Angles();
	vLocal = SubVectorDist(dst, src);

	vTransForm.x = vLocal.dotproduct(*vRight);
	vTransForm.y = vLocal.dotproduct(*vUpward);
	vTransForm.z = vLocal.dotproduct(*vForward);


	delete vForward;		// *** Deleting these stops a memory leak from forming when creating "new vector" *** //
	delete vRight;
	delete vUpward;


	if (vTransForm.z < 0.01)
		return false;

	ScreenX = resolution[0] / 2 + (resolution[0] / 2 / vTransForm.z * (1 / fov[0])) * vTransForm.x;
	ScreenY = resolution[1] / 2 + (resolution[1] / 2 / vTransForm.z * (1 / fov[1])) * vTransForm.y;
	return true;
}


//Google CALC VIEW ANGLE
void Angles()
{
	float angle;
	float sr, sp, sy, cr, cp, cy,
		cpi = (3.141f * 2 / 360);

	
	//cpi = same view angles.x isn't
	angle = viewAngles.x * cpi;
	sp = (float)sin(angle);
	cp = (float)cos(angle);
	angle = viewAngles.y * cpi;
	sy = (float)sin(angle);
	cy = (float)cos(angle);
	angle = viewAngles.z * cpi;
	sr = (float)sin(angle);
	cr = (float)cos(angle);

	vForward->x = cp * cy;
	vForward->y = cp * sy;
	vForward->z = -sp;


	vRight->x = (-1 * sr * sp * cy + -1 * cr * -sy);
	vRight->y = (-1 * sr * sp * sy + -1 * cr * cy);
	vRight->z = -1 * sr * cp;


	vUpward->x = (-cr * sp * cy + -sr * -sy);
	vUpward->y = (-cr * sp * sy + -sr * cy);
	vUpward->z = -cr * cp;
}
















/// Old ESP Boxes
//void esp(bool ESP)
//{
//	//Each Player information is stored in enemyVec
//	//GetVec gets info from current player and stores in playerDD
//	PlayerD Player = GetPlayerInfo();
//	int enemycounter = 0;
//	PlayerD enemyVec[50];
//	PlayerD enemiesVec;
//	int PlayersInGame;
//
//	// This is just the instructions on how to use everything.
//	if (GetAsyncKeyState(VK_END))
//	{
//		system("CLS");
//		cout << "--------------------------------" << endl << "Make your ESP changes" << endl << "--------------------------------" << endl << endl;
//		cout << "Press the Home Key when you are done making changes" << endl << endl;
//		Changes();
//	}
//
//
//
//	{
//		if (!GotResolution)
//			UpdateRes();
//
//		ReadProcessMemory(pHandle, (LPVOID)(0x774350), &PlayersInGame, 4, NULL);
//
//		// Scan through (potentially) 64 entities. Break once you've found them all (PlayersInGame)p
//		for (int x = 0; x <= 64; x++)
//		{
//			// If a player is in game (valid), check their ClientNumber and if they're Alive.
//			enemiesVec.valid = Read<int>(0x839270 + x * 0x4CC);
//			if (enemiesVec.valid == 1)
//			{
//				//ReadProcessMemory(pHandle, (LPVOID)(0x839270 + x * 0x4CC + 0xC), &enemiesVec.PlayerName, sizeof(enemiesVec.PlayerName), NULL);
//				enemiesVec.ClientNum = Read<int>(0x84F2D8 + x * 0x1DC + 0xCC);
//				enemiesVec.Alive = Read<int>(0x84F2D8 + x * 0x1DC + 0x1C0);
//
//				// Read Team, Position, and Stance -> (Standing, Kneeling, Prone)
//				if (enemiesVec.Alive == 1 && enemiesVec.ClientNum != Player.ClientNum)
//				{
//					enemiesVec.team = Read<int>(0x839270 + x * 0x4CC + 0x20);
//					enemiesVec.Pos = Read<Vector>(0x84F2D8 + x * 0x1DC + 0x1C);
//					enemiesVec.stance = Read<int>(0x84F2D8 + x * 0x1DC + 0x64);
//
//					enemiesVec.Pos.z = enemiesVec.Pos.z + 42;
//					enemiesVec.WhichStance = 1;
//
//					if (enemiesVec.stance == 4 || enemiesVec.stance == 6 || enemiesVec.stance == 64 || enemiesVec.stance == 70 || enemiesVec.stance == 262148 || enemiesVec.stance == 262150)
//					{
//						enemiesVec.Pos.z = enemiesVec.Pos.z - 15;
//						enemiesVec.WhichStance = 2;
//					}
//					else if (enemiesVec.stance == 8 || enemiesVec.stance == 10 || enemiesVec.stance == 72 || enemiesVec.stance == 74 || enemiesVec.stance == 262152 || enemiesVec.stance == 262154)
//					{
//						enemiesVec.Pos.z = enemiesVec.Pos.z - 25;
//						enemiesVec.WhichStance = 3;
//					}
//
//					enemyVec[enemycounter] = enemiesVec;
//					enemycounter++;
//					if (enemycounter > PlayersInGame)
//						break;
//				}
//			}
//		}
//
//		float dist;
//		float drawx;
//		float drawy;
//		for (int x = 0; x <= enemycounter; x++)
//		{
//			dist = SubVectorDist(Player.Pos, enemyVec[x].Pos).length() / 48;
//
//			if (WorldToScreen(enemyVec[x].VecCoords(), Player.VecCoords()))
//			{
//				if (enemyVec[x].WhichStance == 3)
//				{
//					drawx = 700.0f / dist;
//					drawy = 350.0f / dist;
//				}
//				else if (enemyVec[x].WhichStance == 2)
//				{
//					drawx = 350.0f / dist;
//					drawy = 450.0f / dist;
//				}
//				else
//				{
//					drawx = 350.0f / dist;
//					drawy = 700.0f / dist;
//				}
//
//
//
//
//				//scaling
//				ScreenY += 4.6f;
//
//
//				if (enemyVec[x].ClientNum == Target)
//					enemiesVec.color = CreateSolidBrush(RGB(0, 255, 255));
//				else if (enemyVec[x].team == 1)
//					enemiesVec.color = Enemy;
//				else
//					enemiesVec.color = Friendly;
//
//
//
//				if (ESP)
//					DrawBorder(hDC, enemiesVec.color, (int)(ScreenX)-(drawx / 2), (int)(ScreenY)-(drawy / 2), drawx, drawy, 2);
//			}
//		}
//	}
//}