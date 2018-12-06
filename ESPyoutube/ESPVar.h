#pragma once
#include <Windows.h>
#include "Player.h"

//ESP
int ScreenX, ScreenY;
int resolution[2];
bool GotResolution = false;
int ScreenCenter[2];
float fov[2];
Vector viewAngles, viewAngles_FloatingSight;
Vector *vForward, *vRight, *vUpward;

//int ScaleESP = 1;


bool Focus = false;
int FocusTarget = -1;



HDC hDC;
HANDLE pHandle;
DWORD pID;
HBRUSH Friendly;
HBRUSH Enemy;



HFONT Font = CreateFont(16, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, "Verdana");
HFONT BigFont = CreateFont(22, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, "Verdana");

COLORREF FriendlyCol = (RGB(0, 215, 215));
COLORREF EnemyCol = (RGB(255, 60, 0));
COLORREF EnemyCloseCol = (RGB(128, 255, 0));
COLORREF TargetCol = (RGB(255, 0, 255));