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
	bool					bEnable;				// Ȧ�� ã�Ҵ��� �ƴ��� ����
	std::queue<POS>				queue;
}STR_QUEUE;

bool						flag = false;			// ���� ���� ���ۿ� ������ �ƴ��� Ȯ���ؼ� �Ķ����� �������� �ν����� ���� ����.
int							X, Y;
POS							RED_POS = { 0 };		// ���� �� ��ġ
POS							BLUE_POS = { 0 };		// �Ķ� �� ��ġ
POS							HOLE_POS = { 0 };		// ���� ��ġ
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
	int						count = 0;	// �� ��� �������� ������ Ȧ�� ��������
	// Left -> Right -> Up -> Down	
	while (true)
	{
		/**
		* BALL CHECK
		**/		
		if (BFS_RED.queue.empty() == false)
		{
			// 10�� �̳��� �������� �� �� �ִ��� Ȯ��.
			if (count > 10)
			{
				cout << "-1" << endl;
				break;
			}

			// ť�� �ԷµǾ� �ִ� ��ǥ �� ����
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
			
		// ���ʺ��� �� ������ Ȯ��
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

		// ������ �� ������ Ȯ��
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

		// ���� �� ������ Ȯ��
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

		// �Ʒ��� �� ������ Ȯ��
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
	// direction ���� ���� ���� �������� ���� �ϸ鼭 �� ���� ������ �� �����Ͱ� .(�����)�� �ƴҶ� ���� ��� Ž��.
	// ���� �� �����Ͱ� .(�����)�� �ƴ� ��� ���� ��ǥ�� ��ȯ.
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

	// ���� �� �����Ͱ� �� ������ ��� �� ���� �� �����͵� ��� Ȯ���ϱ� ���� ��� ȣ��
	if (MAP[next_pos.x][next_pos.y] == '.' || MAP[next_pos.x][next_pos.y] == 'R')
		return check_empty(next_pos.x, next_pos.y, _direction);
	// ���� �� �����Ͱ� Ȧ�� ��� ������ ���������� ������ ���� ��ǥ ������ �� ����
	else if (MAP[next_pos.x][next_pos.y] == 'O')
		return next_pos;

	// �� �Ǵ� �ٸ� ������ ������ ��� current_pos�� ����
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
		// ���� pos�� BLUE_POS���� ������ ������ �������� �������� ���ߴٴ� �ǹ��̴� �ش� �κ��� ť�� ���� �ʵ��� �Ѵ�.
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
		// ���� pos�� RED_POS���� ������ ������ �������� �������� ���ߴٴ� �ǹ��̴� �ش� �κ��� ť�� ���� �ʵ��� �Ѵ�.
		if (!(move(pos) == move(RED_POS)))
		{
			pos.prev_dir	= _dir;
			BFS_RED.queue.push(pos);
		}

		return false;
	}
}