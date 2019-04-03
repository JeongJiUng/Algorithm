//https://www.acmicpc.net/problem/12100
//https://rebas.kr/763
/**
 * 4방향, 최대 5번, 최고값 추출.
**/
#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

queue<int>					merge_queue;

enum
{
	LEFT					= 0,
	RIGHT,
	UP,
	DOWN
};

int							map[20][20];
int							map_size;
int							result = 0;

void get(int _i, int _j)
{
	if (map[_i][_j])
	{
		merge_queue.push(map[_i][_j]);
		map[_i][_j]			= 0;
	}
}

void merge(int _i, int _j, int _di, int _dj)
{
	// 한 라인씩 합친다.
	int						i = _i, j = _j;
	
	while (!merge_queue.empty())
	{
		int					data = merge_queue.front();
		merge_queue.pop();
		
		if (!map[i][j])
			map[i][j]		= data;
		else if (data == map[i][j])
		{
			map[i][j]		= data * 2;
			i				+= _di;
			j				+= _dj;
		}
		else
		{
			i += _di;
			j += _dj;
			map[i][j]		= data;
		}
	}
}

void move(int _dir)
{
	switch (_dir)
	{
	case LEFT:
		for (int i = 0; i < map_size; i++)
		{
			for (int j = 0; j < map_size; j++)
			{
				get(i, j);
			}

			merge(i, 0, 0, 1);
		}
		break;

	case RIGHT:
		for (int i = 0; i < map_size; i++)
		{
			for (int j = map_size - 1; j >= 0; j--)
			{
				get(i, j);
			}
			
			merge(i, map_size - 1, 0, -1);
		}
		break;

	case UP:
		for (int j = 0; j < map_size; j++)
		{
			for (int i = 0; i < map_size; i++)
			{
				get(i, j);
			}

			merge(0, j, 1, 0);
		}
		break;

	case DOWN:
		for (int j = 0; j < map_size; j ++)
		{
			for (int i = map_size - 1; i >= 0; i--)
			{
				get(i, j);
			}

			merge(map_size - 1, j, -1, 0);
		}
		break;
	}
}

void solve(int _count)
{
	int						old_map[20][20] = { 0, };

	if (_count >= 5)
	{
		for (int i = 0; i < map_size; i++)
		{
			for (int j = 0; j < map_size; j++)
			{
				if (map[i][j] > result)
					result	= map[i][j];
			}
		}
		return;
	}

	memcpy(old_map, map, sizeof(map));

	// 4방향 이동시키면서 최대값 구함.
	for (int i = 0; i < 4; i++)
	{
		// TODO:: 특정 방향으로 움직이고 (move)
		// 모든 경로를 탐색하기 위해 solve 함수를 재귀시켜 최대값 구한다.
		move(i);
		solve(_count +1);

		memcpy(map, old_map, sizeof(old_map));
	}
}

int main()
{
	cin >> map_size;
	
	for (int i = 0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			cin >> map[i][j];
		}
	}

	solve(0);

	cout<< result <<endl;

//	cin>>map_size;

	return 0;
}