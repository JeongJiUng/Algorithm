// https://www.acmicpc.net/problem/13460
#include <iostream>
#include <queue>

using namespace				std;
using std::queue;

enum direction
{
	left					= 0,
	right,
	up,
	down,
	none
};

typedef struct position
{
	int						x;
	int						y;
	direction				prev_dir;
}POS;

typedef struct struct_queue
{
	bool					bEnable;				// 홀을 찾았는지 아닌지 여부
	std::queue<POS>				queue;
}STR_QUEUE;

bool						flag = false;			// 빨간 공이 구멍에 들어갔는지 아닌지 확인해서 파란공이 빨간공을 인식할지 말지 결정.
int							X, Y;
POS							RED_POS = { 0 };		// 빨간 공 위치
POS							BLUE_POS = { 0 };		// 파란 공 위치
POS							HOLE_POS = { 0 };		// 구멍 위치
char						MAP[10][10] = { 0 };

STR_QUEUE					BFS_RED;
STR_QUEUE					BFS_BLUE;

POS							check_empty(int _x, int _y, direction _direction);
bool						check_hole(int _x, int _y);
bool						check_blue_ball(direction _dir);
bool						check_red_ball(direction _dir);

bool operator== (POS _lvalue, POS _rvalue)
{
	if (_lvalue.x == _rvalue.x &&
		_lvalue.y == _rvalue.y)
		return true;

	return false;
}

int main()
{
	BFS_RED.bEnable			= false;
	BFS_BLUE.bEnable		= false;

	cin >> Y;
	cin >> X;

	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			cin >> MAP[x][y];

			if (MAP[x][y] == 'R')
			{
				RED_POS.x	= x;
				RED_POS.y	= y;
				RED_POS.prev_dir	= direction::none;

				BFS_RED.queue.push(RED_POS);
			}
			else if (MAP[x][y] == 'B')
			{
				BLUE_POS.x	= x;
				BLUE_POS.y	= y;
				BLUE_POS.prev_dir	= direction::none;

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
	int						count = 0;	// 총 몇번 움직여서 구슬이 홀에 빠졌는지
	// Left -> Right -> Up -> Down	
	while (true)
	{
		/**
		* BALL CHECK
		**/		
		if (BFS_RED.queue.empty() == false)
		{
			// 10번 이내에 목적지에 갈 수 있는지 확인.
			if (count > 10)
			{
				cout << "-1" << endl;
				break;
			}

			// 큐에 입력되어 있는 좌표 값 추출
			RED_POS.x		= BFS_RED.queue.front().x;
			RED_POS.y		= BFS_RED.queue.front().y;
			RED_POS.prev_dir	= BFS_RED.queue.front().prev_dir;
			BFS_RED.queue.pop();
			
			if (BFS_BLUE.queue.empty() == false)
			{
				BLUE_POS.x = BFS_BLUE.queue.front().x;
				BLUE_POS.y = BFS_BLUE.queue.front().y;
				BLUE_POS.prev_dir	= BFS_BLUE.queue.front().prev_dir;
				BFS_BLUE.queue.pop();
			}

			count++;
		}
		else
		{
			count			= -1;
			break;
		}
			
		// 왼쪽부터 맵 데이터 확인
		if (!(RED_POS.prev_dir == direction::right))
		{
			if (check_blue_ball(direction::left))
			{
				if (check_red_ball(direction::left))
				{
					break;
				}
			}
		}

		// 오른쪽 맵 데이터 확인
		if (!(RED_POS.prev_dir == direction::left))
		{
			if (check_blue_ball(direction::right))
			{
				if (check_red_ball(direction::right))
				{
					break;
				}
			}
		}

		// 위쪽 맵 데이터 확인
		if (!(RED_POS.prev_dir == direction::down))
		{
			if (check_blue_ball(direction::up))
			{
				if (check_red_ball(direction::up))
				{
					break;
				}
			}
		}

		// 아래쪽 맵 데이터 확인
		if (!(RED_POS.prev_dir == direction::up))
		{
			if (check_blue_ball(direction::down))
			{
				if (check_red_ball(direction::down))
				{
					break;
				}
			}
		}
	}

	if (count <= 10)
	{
		cout << count << endl;
	}
	return 0;
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

	POS						current_pos = { _x, _y };
	POS						next_pos = { _x + x, _y + y };

	// 다음 맵 데이터가 빈 공간인 경우 그 다음 맵 데이터도 계속 확인하기 위해 재귀 호출
	if (MAP[next_pos.x][next_pos.y] == '.' || MAP[next_pos.x][next_pos.y] == 'R')
		return check_empty(next_pos.x, next_pos.y, _direction);
	// 다음 맵 데이터가 홀일 경우 구슬이 빠져나가기 때문에 다음 좌표 값으로 값 리턴
	else if (MAP[next_pos.x][next_pos.y] == 'O')
		return next_pos;

	// 벽 또는 다른 색상의 구슬인 경우 current_pos로 리턴
	return current_pos;
}

bool check_hole(int _x, int _y)
{
	if (MAP[_x][_y] == 'O')
		return true;

	return false;
}

bool check_blue_ball(direction _dir)
{
	POS pos			= check_empty(BLUE_POS.x, BLUE_POS.y, _dir);

	if (!check_hole(pos.x, pos.y))
	{
		// 만약 pos와 BLUE_POS값이 같으면 가려는 방향으로 움직이지 못했다는 의미이니 해당 부분은 큐에 넣지 않도록 한다.
		if (!(move(pos) == move(BLUE_POS)))
		{
			pos.prev_dir	= _dir;
			BFS_BLUE.queue.push(pos);
		}

		return true;
	}

	return false;
}

bool check_red_ball(direction _dir)
{
	POS pos					= check_empty(RED_POS.x, RED_POS.y, _dir);

	if (check_hole(pos.x, pos.y))
	{
		return true;
	}
	else
	{
		// 만약 pos와 RED_POS값이 같으면 가려는 방향으로 움직이지 못했다는 의미이니 해당 부분은 큐에 넣지 않도록 한다.
		if (!(move(pos) == move(RED_POS)))
		{
			pos.prev_dir	= _dir;
			BFS_RED.queue.push(pos);
		}

		return false;
	}
}