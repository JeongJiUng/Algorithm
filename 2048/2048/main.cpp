//https://www.acmicpc.net/problem/12100
//https://rebas.kr/763
/**
 * 4방향, 최대 5번, 최고값 추출.
**/
#include <iostream>
#include <queue>

using namespace std;

vector<int>					results;
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

void move(int _dir)
{
	switch (_dir)
	{
	case LEFT:
		break;

	case RIGHT:
		break;

	case UP:
		break;

	case DOWN:
		break;
	}
}

void solve(int _count)
{
	if (_count >= 5)
	{
		// TODO:: 최고값 구해서 출력.
		return;
	}

	// 4방향 이동시키면서 최대값 구함.
	for (int i = 0; i < 4; i++)
	{
		// TODO:: 특정 방향으로 움직이고 (move)
		// 모든 경로를 탐색하기 위해 solve 함수를 재귀시켜 최대값 구한다.
		move(i);
		solve(_count +1);
	}
}

void main()
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
}