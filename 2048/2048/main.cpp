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

int							dir_x[4] = { 0, 0, 1, -1 };
int							dir_y[4] = { 1, -1, 0, 0 };

enum
{
	LEFT					= 0,
	RIGHT,
	UP,
	DOWN
};

int							map[20][20];
int							map_size;

void merge(int _dir, int _line, int _map[20][20])
{
	// �� ���ξ� ��ģ��.
	int						i, j;

	if (_dir == LEFT || _dir == RIGHT)
	{
		i					= _line;
		j					= 0;
	}
	else
	{
		i					= 0;
		j					= _line;
	}
	
	while (!merge_queue.empty())
	{
		int					data = merge_queue.front();
		merge_queue.pop();

		if (merge_queue.empty())
		{
			// data ���� ť�� �����Ͱ� ���� ���ٸ�, data�� _map�� ����ϰ� �ݺ� ����.
			_map[i][j]		= data;
			break;
		}

		// data�� ���� ť�� �����Ϳ� ���� �����̸�, ��ģ���� _map�� ����Ѵ�.
		if (data == merge_queue.front())
		{
			int				nData = data + merge_queue.front();
			merge_queue.pop();

			_map[i][j]		= nData;
		}
		else
		{
			_map[i][j]		= data;
		}

		i					+= dir_x[_dir];
		j					+= dir_y[_dir];
	}
}

void move(int _dir, int _map[20][20])
{
	int						nMap[20][20] = { 0, }; 
	switch (_dir)
	{
	case LEFT:
		for (int i = 0; i < map_size; i++)
		{
			for (int j = 0; j < map_size; j++)
			{
				if (_map[i][j] != 0)
					merge_queue.push(_map[i][j]);
			}

			merge(_dir, i, nMap);
		}
		break;

	case RIGHT:
		for (int i = map_size - 1; i >= 0; i--)
		{
			for (int j = map_size - 1; j >= 0; j--)
			{
				if (_map[i][j] != 0)
					merge_queue.push(_map[i][j]);
			}
			
			merge(_dir, i, _map);
		}
		break;

	case UP:
		for (int j = 0; j < map_size; j++)
		{
			for (int i = 0; i < map_size; i++)
			{
				if (_map[i][j] != 0)
					merge_queue.push(_map[i][j]);
			}

			merge(_dir, j, _map);
		}
		break;

	case DOWN:
		for (int j = map_size - 1; j >= 0; j--)
		{
			for (int i = map_size - 1; i >= 0; i--)
			{
				if (_map[i][j] != 0)
					merge_queue.push(_map[i][j]);
			}

			merge(_dir, j, _map);
		}
		break;
	}

	//TODO:: �޸𸮰� �̻��ϰ� �Է��� �ȴ�. Ȯ�� �ʿ�.
	memset(_map, 0, sizeof(int[20][20]));
	memcpy(_map, nMap, sizeof(_map));
}

void solve(int _count, int _map[20][20])
{
	int						copy_map[20][20] = { 0, };

	if (_count >= 5)
	{
		// TODO:: �ְ� ���ؼ� ���.
		cout << _count << endl;
		return;
	}

	memcpy(copy_map, _map, sizeof(copy_map));

	// 4���� �̵���Ű�鼭 �ִ밪 ����.
	for (int i = 0; i < 4; i++)
	{
		// TODO:: Ư�� �������� �����̰� (move)
		// ��� ��θ� Ž���ϱ� ���� solve �Լ��� ��ͽ��� �ִ밪 ���Ѵ�.
		move(i, copy_map);
		solve(_count +1, copy_map);
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

	solve(0, map);

	return 0;
}