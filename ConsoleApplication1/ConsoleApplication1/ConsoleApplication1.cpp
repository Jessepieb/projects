// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"
#include <iostream>
#include <thread>
#include <chrono>


using namespace std;

int main()
{
	using namespace std::this_thread;
	using namespace std::chrono;
	cout << "test123" << endl;
	
	Life test(10,12);
	Life test2(15, 11);
	Life test3(9, 13);
	
	while (true) {
		if ((test.x == test2.x) && (test.y == test2.y))
		{
			cout << "hit" << endl;
			break;
		}
		else {
			test.move();
			test2.move();
			sleep_for(seconds(2));
		}
	}

}

