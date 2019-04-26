// https://www.acmicpc.net/problem/7569
#include <iostream>
#include <queue>

#define						MAP_SIZE 100

using namespace std;

typedef struct _tomato
{
	int						h, x, y;
	int						day;
}TOMATO;

int							map[MAP_SIZE][MAP_SIZE][MAP_SIZE];
int							H, Y, X; // 높이, 세로, 가로
int							dx[6] = { 1, 0, 0, -1, 0, 0 };
int							dy[6] = { 0, 1, 0, 0, -1, 0 };
int							dh[6] = { 0, 0, 1, 0, 0, -1 };

queue<TOMATO>				q;

void bfs()
{
	while (!q.empty())
	{
		TOMATO				tomato = q.front();
		q.pop();

		for (int i = 0; i < 6; i++)
		{
			TOMATO			nTomato;
			nTomato.h		= tomato.h + dh[i];
			nTomato.x		= tomato.x + dx[i];
			nTomato.y		= tomato.y + dy[i];
			nTomato.day		= tomato.day + 1;

			if (nTomato.h >= H || nTomato.h < 0 || nTomato.x >= X || nTomato.x < 0 || nTomato.y >= Y || nTomato.y < 0)
				continue;

			if (map[nTomato.h][nTomato.y][nTomato.x] == 0)
			{
				map[nTomato.h][nTomato.y][nTomato.x]	= nTomato.day;
				q.push(nTomato);
			}
			else if (map[nTomato.h][nTomato.y][nTomato.x] > 1)
			{
				if (map[nTomato.h][nTomato.y][nTomato.x] > nTomato.day)
				{
					map[nTomato.h][nTomato.y][nTomato.x]	= nTomato.day;
					q.push(nTomato);
				}
			}
		}
	}
}

int main()
{
	cin >> X >> Y >> H;

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			for (int k = 0; k < X; k++)
			{
				cin >> map[i][j][k];

				if (map[i][j][k] == 1)
				{
					TOMATO	tomato = { i, k, j, 0 };
					q.push(tomato);
				}
			}
		}
	}

	bfs();

	bool					bEnable = true;
	int						result = 0;
	for (int h = 0; h < H && bEnable == true; h++)
	{
		for (int y = 0; y < Y && bEnable == true; y++)
		{
			for (int x = 0; x < X && bEnable == true; x++)
			{
				if (result < map[h][y][x])
					result	= map[h][y][x];

				if (map[h][y][x] == 0)
				{
					bEnable	= false;
					break;
				}
			}
		}
	}

	if (bEnable == false)
		cout << "-1" << endl;
	else if (result == 1)
		cout << "0" << endl;
	else
		cout << result << endl;

	cin >> result;

	return 0;
}