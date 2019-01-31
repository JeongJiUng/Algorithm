// https://www.acmicpc.net/problem/13460
#include <iostream>
#include <queue>

using namespace				std;

enum direction
{
	left					= 0,
	right,
	up,
	down
};

typedef struct position
{
	int						x;
	int						y;
}POS;

typedef struct struct_queue
{
	bool					bEnable;				// 홀을 찾았는지 아닌지 여부
	queue<POS>				queue;
}STR_QUEUE;

int							X, Y;
POS							RED_POS = { 0 };		// 빨간 공 위치
POS							BLUE_POS = { 0 };		// 파란 공 위치
POS							HOLE_POS = { 0 };		// 구멍 위치
char						MAP[10][10] = { 0 };

STR_QUEUE					BFS_RED;
STR_QUEUE					BFS_BLUE;

POS							check_empty(int _x, int _y, direction _direction);
bool						check_hole(int _x, int _y);

void main()
{
	BFS_RED.bEnable			= false;
	BFS_BLUE.bEnable		= false;

	cin >> X;
	cin >> Y;

	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			cin >> MAP[x][y];

			if (MAP[x][y] == 'R')
			{
				RED_POS.x	= x;
				RED_POS.y	= y;

				BFS_RED.queue.push(RED_POS);
			}
			else if (MAP[x][y] == 'B')
			{
				BLUE_POS.x	= x;
				BLUE_POS.y	= y;

				BFS_BLUE.queue.push(BLUE_POS);
			}
			else if (MAP[x][y] == 'O')
			{
				HOLE_POS.x	= x;
				HOLE_POS.y	= y;
			}
		}
	}

	// Proc BFS
	// Left -> Right -> Up -> Down
	while (true)
	{
		/**
		* RED BALL CHECK
		**/		
		if (BFS_RED.queue.empty() == false)
		{
			// 큐에 입력되어 있는 좌표 값 추출
			RED_POS.x		= BFS_RED.queue.front().x;
			RED_POS.y		= BFS_RED.queue.front().y;
			BFS_RED.queue.pop();
		}
			
		// 왼쪽부터 맵 데이터 확인
		POS LEFT_POS		= check_empty(RED_POS.x, RED_POS.y, direction::left);
		
		if (check_hole(LEFT_POS.x, LEFT_POS.y))
			break;
		else
		{
			BFS_RED.queue.push(LEFT_POS);
		}
	}
}

POS check_empty(int _x, int _y, direction _direction)
{
	// direction 값에 따라 한쪽 방향으로 진행 하면서 그 진행 방향의 맵 데이터가 .(빈공간)이 아닐때 까지 계속 탐색.
	// 다음 맵 데이터가 .(빈공간)이 아닐 경우 현재 좌표를 반환.
	int						x = 0, y = 0;

	switch (_direction)
	{
	case direction::left:
		x					= -1;
		break;

	case direction::right:
		x					= 1;
		break;

	case direction::up:
		y					= -1;
		break;

	case direction::down:
		y					= 1;
		break;
	}

	POS						current_pos = {_x, _y };
	POS						next_pos = { _x + x, _y + y };

	if (MAP[next_pos.x][next_pos.y] == '.')
		return check_empty(next_pos.x, next_pos.y, _direction);

	return current_pos;
}

bool check_hole(int _x, int _y)
{
	if (MAP[_x][_y] == 'O')
		return true;

	return false;
}