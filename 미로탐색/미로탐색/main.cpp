// https://www.acmicpc.net/problem/2178
#include <iostream>
#include <queue>

using namespace std;

typedef struct _maze
{
	int						x, y;
	int						cost;
}MAZE;

queue<MAZE>					qMaze;

bool						check_map[101][101] = { 1, };
int							map[101][101];
int							X, Y;

int							dx[4] = { 1, 0, -1, 0 };
int							dy[4] = { 0, 1, 0, -1 };

int bfs()
{
	while (!qMaze.empty())
	{
		MAZE				maze = qMaze.front();
		qMaze.pop();

		if (maze.x == X - 1 && maze.y == Y - 1)
		{
			return maze.cost;
		}

		for (int i = 0; i < 4; i++)
		{
			MAZE			nMaze;
			nMaze.x			= maze.x + dx[i];
			nMaze.y			= maze.y + dy[i];
			nMaze.cost		= maze.cost + 1;

			if (nMaze.x >= X || nMaze.x < 0 || nMaze.y >= Y || nMaze.y < 0)
				continue;
			if (check_map[nMaze.y][nMaze.x] == true)
				continue;
			if (map[nMaze.y][nMaze.x] == 0)
				continue;

			qMaze.push(nMaze);
			check_map[nMaze.y][nMaze.x]	= true;
		}
	}

	return 0;
}

int main()
{
	cin >> Y >> X;

	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			char			input;
			cin >> input;
			map[y][x]		= input - '0';
		}
	}

	MAZE					maze = { 0, 0, 1 };
	qMaze.push(maze);

	cout << bfs() << endl;
	cin >> X;

	return 0;
}