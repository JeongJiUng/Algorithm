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
	// 한 라인씩 합친다.
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
			// data 다음 큐의 데이터가 만약 없다면, data를 _map에 등록하고 반복 종료.
			_map[i][j]		= data;
			break;
		}

		// data가 다음 큐의 데이터와 같은 숫자이면, 합친다음 _map에 등록한다.
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

	//TODO:: 메모리가 이상하게 입력이 된다. 확인 필요.
	memset(_map, 0, sizeof(int[20][20]));
	memcpy(_map, nMap, sizeof(_map));
}

void solve(int _count, int _map[20][20])
{
	int						copy_map[20][20] = { 0, };

	if (_count >= 5)
	{
		// TODO:: 최고값 구해서 출력.
		cout << _count << endl;
		return;
	}

	memcpy(copy_map, _map, sizeof(copy_map));

	// 4방향 이동시키면서 최대값 구함.
	for (int i = 0; i < 4; i++)
	{
		// TODO:: 특정 방향으로 움직이고 (move)
		// 모든 경로를 탐색하기 위해 solve 함수를 재귀시켜 최대값 구한다.
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