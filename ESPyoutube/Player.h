#pragma once
//#include "Process.h"
#include <math.h>
#include <string>

using namespace std;



class Vector
{
public:
	float x;
	float y;
	float z;

	Vector(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector()
	{
	}

	float length()
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	float dotproduct(Vector dot)
	{
		return (x * dot.x + y * dot.y + z * dot.z);
	}
};

class PlayerD
{
public:
	Vector Pos;
	Vector ClientAimAngles;
	int valid;
	int Alive;
	int ClientNum;
	int team;
	int InLastStand;

	char PlayerName[16];

	//int health;		Can't read other peoples' health in multiplayer

	char Kills[13] = "Killstreak: ";
	int Killstreak;



	int stance; 


	////Drawing Colors
	//HBRUSH color;

	DWORD inGame;
	//int health;
	
	Vector VecCoords()
	{
		Vector vec(Pos.x, Pos.y, Pos.z);
		return vec;
	}


	float dist;


};




