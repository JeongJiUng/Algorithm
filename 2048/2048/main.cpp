//https://www.acmicpc.net/problem/12100
//https://rebas.kr/763
/**
 * 4����, �ִ� 5��, �ְ� ����.
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

void move(int _dir, int *_map)
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

void solve(int _count, int _map[20][20])
{
	int						copy_map[20][20];

	if (_count >= 5)
	{
		// TODO:: �ְ� ���ؼ� ���.
		return;
	}

	memcpy(copy_map, _map, sizeof(_map));

	// 4���� �̵���Ű�鼭 �ִ밪 ����.
	for (int i = 0; i < 4; i++)
	{
		// TODO:: Ư�� �������� �����̰� (move)
		// ��� ��θ� Ž���ϱ� ���� solve �Լ��� ��ͽ��� �ִ밪 ���Ѵ�.
		move(i, *copy_map);
		solve(_count +1, copy_map);
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

	solve(0, map);
}