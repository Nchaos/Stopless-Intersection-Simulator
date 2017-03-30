/*
	Nicholas Chao
	March 21, 2017
	Car Object
	Car.cpp
*/

#include "Car.h"
#include <iostream>

using namespace std;

Car::Car(int n_id, bool n_dir, float n_speed, float n_xpos, float n_ypos)
{
	id = n_id;
	dir = n_dir;
	speed = n_speed;
	x_pos = n_xpos;
	y_pos = n_ypos;
}

int Car::getID()
{
	return id;
}

void Car::setID(int n_id)
{
	id = n_id;
}

float Car::getSpeed()
{
	return speed;
}

void Car::setSpeed(float n_speed)
{
	speed = n_speed;
}

float Car::getXPos()
{
	return x_pos;
}

void Car::setXPos(float n_xpos)
{
	x_pos = n_xpos;
}

float Car::getYPos()
{
	return y_pos;
}

void Car::setYPos(float n_ypos)
{
	y_pos = n_ypos;
}

bool Car::getDir()
{
	return dir;
}

void Car::setDir(bool n_dir)
{
	dir = n_dir;
}

float Car::getRed()
{
    return red;
}

float Car::getBlue()
{
    return blue;
}

float Car::getGreen()
{
    return green;
}

void Car::setColor(float r, float g, float b)
{
    red = r;
    green = g;
    blue = b;
}

bool Car::getDanger()
{
    return danger;
}

void Car::setDanger(bool logic)
{
    danger = logic;
}

bool Car::getCollision()
{
    return collision;
}

void Car::setCollision(bool logic)
{
    collision = logic;
}

float Car::getCarStart()
{
    return carStart;
}

void Car::setCarStart(float start)
{
    carStart = start;
}

float Car::getCarEnd()
{
    return carEnd;
}

void Car::setCarEnd(float end)
{
    carEnd = end;
}

float Car::getCarCollisionTime()
{
    return carCollisionTime;
}

void Car::setCarCollisionTime(float time)
{
    carCollisionTime = time;
}

void Car::alignCoordinates()
{
	if(dir) // north/south 
	{
		x_pos = -5.0;
	}
	else // east/west
	{
		y_pos = 5.0;
	}
}

void Car::print()
{
	cout << "id: \t" << id << endl;
	cout << "North: \t" << dir << endl;
	cout << "x_pos: \t" << x_pos << endl;
	cout << "y_pos: \t" << y_pos << endl;
	cout << "Speed: \t" << speed << endl;
}

void Car::printTime()
{
    cout << "id: \t\t" << id << endl;
    cout << "Start Time: \t" << carStart << endl;
    cout << "End Time: \t" << carEnd << endl;
    cout << "Collision Time: \t" << carCollisionTime << endl;
}

