#pragma once

#ifndef MAZE_H
#define MAZE_H

//Matrix size
#define M 10
#define N 10

#include <iostream>
#include <queue>


using namespace std;

//queue Node for BFS
struct Node
{
	// (x,y) are matrix cell coords
	//dist is min. distance from source
	int x, y, dist;
};

int row[] = {-1, 0, 0, 1};
int col[] = {0, -1, 1, 0};

void BFS(int matrix[][N], int i, int j, int x, int y);
#endif // !MAZE_H
