#pragma once
#ifndef TEST_HEADER_H
#define TEST_HEADER_H
#include <iostream>
#include<ctime>
class Life
{
public:
	Life(int lx, int ly);
	~Life();
	int age;
	int health;
	void move();
	int x;
	int y;


private:




};
Life::Life(int lx, int ly)
{
	this->x = lx;
	this->y = ly;
}

Life::~Life()
{
}

int randomNum(int d) {

	//int range = 2 - 2 + 1;
	int random = rand()%3-1;
	std::cout << "integer = " << random << "\n";
	int num = d + random;
	random = NULL;
	return num;
}

void Life::move()
{
	this->x = randomNum(x);
	this->y = randomNum(y);
	std::cout << "x = " << x << "\n";
	std::cout << "y = " << y << "\n";
};


#endif