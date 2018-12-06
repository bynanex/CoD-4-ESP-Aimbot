#include "DrawGDI.h"
//#include <gdiplus.h>
//
//using namespace Gdiplus;
//#pragma comment (lib, "Gdiplus.lib")

void GDI::DrawLine(HDC hdc, float StartX, float StartY, float EndX, float EndY, COLORREF Pen)
{
	HPEN hNPen = CreatePen(PS_SOLID, 1, Pen); // Number in middle is thickness
	HPEN hOPen = (HPEN)SelectObject(hdc, hNPen);
	MoveToEx(hdc, StartX, StartY, NULL);
	int a = LineTo(hdc, EndX, EndY);
	DeleteObject(SelectObject(hdc, hOPen));
}

void GDI::DrawString(HDC hdc, HFONT font, int x, int y, COLORREF color, const char* text) // LPCSTR was const char*
{
	SetTextAlign(hdc, TA_CENTER | TA_NOUPDATECP);
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);
	SelectObject(hdc, font);
	TextOut(hdc, x, y, text, lstrlen(text));
	DeleteObject(font);
}

void GDI::DrawRect(HDC hdc, int StartX, int StartY, int EndX, int EndY, COLORREF color)
{
	RECT rc;
	rc.left = StartX;
	rc.top = StartY;
	rc.right = EndX;
	rc.bottom = EndY;


	HBRUSH hbrush = ::CreateSolidBrush(color);
	FrameRect(hdc, &rc, hbrush);
	DeleteObject(SelectObject(hdc, hbrush));


	//HPEN hNPen = CreatePen(PS_SOLID, 2, (RGB(0, 255, 0)));
	//HPEN hOPen = (HPEN)SelectObject(hdc, hNPen);
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	//::FillRect(hdc, &rc, hbrush);
}


void GDI::DrawAimbotFOV(HDC hdc, int X, int Y, float AimbotFOV, float fov0, COLORREF color)
{


	AimbotFOV = (8.4 * AimbotFOV) / fov0; // I don't know why 8.4 is the correct number but it works


	RECT rc;
	rc.left = X - AimbotFOV;
	rc.top = Y - AimbotFOV;
	rc.right = X + AimbotFOV;
	rc.bottom = Y + AimbotFOV;


	HBRUSH hbrush = ::CreateSolidBrush(color);
	FrameRect(hdc, &rc, hbrush);
	DeleteObject(SelectObject(hdc, hbrush));
}


void GDI::DrawCircle(HDC hdc, int xLeft, int yUp, int xRight, int yDown, COLORREF color)
{

	SetDCPenColor(hdc, color);
	SetDCBrushColor(hdc, BLACK_BRUSH);
	HPEN pen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));
	HBRUSH brush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));


	Ellipse(hdc, xLeft, yUp, xRight, yDown);

	DeleteObject(pen);
	DeleteObject(brush);
}