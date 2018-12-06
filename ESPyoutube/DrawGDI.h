#pragma once
#include <windows.h>




namespace GDI
{
	void DrawLine(HDC hdc, float StartX, float StartY, float EndX, float EndY, COLORREF color);
	void DrawString(HDC hdc, HFONT font, int x, int y, COLORREF color, const  char* text);
	void DrawRect(HDC hdc, int StartX, int StartY, int EndX, int EndY, COLORREF color);
	void DrawAimbotFOV(HDC hdc, int X, int Y, float AimbotFOV, float fov0, COLORREF color);
	void DrawCircle(HDC hdc, int xLeft, int yUp, int xRight, int yDown, COLORREF color);
}