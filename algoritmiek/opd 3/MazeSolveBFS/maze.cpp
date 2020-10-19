#include "maze.h"

bool isValid(int matrix[][N], bool visited[][N], int row, int col) {
	return (row >= 0) &&(row < M) &&(col >= 0) &&(col < N) &&
		matrix[row][col] && !visited[row][col];
}


void BFS(int matrix[][N], int i, int j, int x, int y) {

	bool visited[M][N];

	memset(visited, false, sizeof visited);

	queue<Node> q;

	// Set Source coords to true
	visited[i][j] = true;
	q.push({ i,j,0 });

	int min_dist = INT_MAX;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		int i = node.x, j = node.y, dist = node.dist;

		// check if you have reached the destination
		if (i == x && j == y) {
			min_dist = dist;
			break;
		}

		for (int k = 0; k < 4; k++) {
			if (isValid(matrix, visited, i + row[k], j + col[k])) {
				visited[i + row[k]][j + col[k]] = true;
				q.push({ i + row[k], j + col[k], dist + 1 });
			}
		}
	}

	if (min_dist != INT_MAX)
		cout << "Shortest path is: " << min_dist;
	else
		cout << "No Possible Solution";
}


	int main()
	{
		int matrix[M][N] =
		{
			{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
			{ 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
			{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
			{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
			{ 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
			{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
			{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
			{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
		};

		BFS(matrix, 0, 0, 9, 9);

		return 0;
	}