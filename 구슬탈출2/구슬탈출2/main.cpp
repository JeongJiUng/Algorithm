// https://www.acmicpc.net/problem/13460
#include <iostream>
#include <queue>

using namespace std;

struct _bead_info
{
	int						rx, ry, bx, by;
	int						count;
};

bool						check[10][10][10][10];		// ������, �Ķ��� �� �� üũ�ϱ� ���� 4���� �迭 ���.
char						map[10][10] = { 0, };
int							N, M;
const int					dx[4] = { -1, 0, 1, 0 };
const int					dy[4] = { 0, 1, 0, -1 };

_bead_info					bead;
queue<_bead_info>			bead_queue;

/**
 * int &x -> ���� x ��ǥ
 * int &y -> ���� y ��ǥ
 * int dx -> x��ǥ �̵� ����
 * int dy -> y��ǥ �̵� ����
 * return int -> �ش� ������ ��ĭ ��ŭ ������������ ���� �� ��ȯ
 * dx, dy�� ���� ���� # �׸��� O�� �ƴҶ� ���� ���� ���� �̵������ִ� �Լ�
**/
int move(int &x, int &y, int dx, int dy)
{
	int						moved = 0;
	// # �׸��� O�� �ƴҶ� ���� dx, dy �������� ���� �̵�
	while (map[x + dx][y + dy] != '#' && map[x][y] != 'O')
	{
		x					+= dx;
		y					+= dy;
		moved++;
	}

	return moved;
}

void bfs()
{
	while (!bead_queue.empty())
	{
		int					rx = bead_queue.front().rx;
		int					ry = bead_queue.front().ry;
		int					bx = bead_queue.front().bx;
		int					by = bead_queue.front().by;
		int					count = bead_queue.front().count;
		bead_queue.pop();

		if (count >= 10)
		{
			cout << "-1" << endl;
			return;
		}

		// ������ 4�������� �̵���Ű�鼭 ������ ���� �� �ִ��� BFS Ž��.
		for (int i = 0; i < 4; i++)
		{
			int				rx2= rx, ry2 = ry, bx2 = bx, by2 = by;
			int				count2 = count + 1;
			int				moved_red, moved_blue;
			// ���� ����, �Ķ� ���� �̵�
			moved_red		= move(rx2, ry2, dx[i], dy[i]);
			moved_blue		= move(bx2, by2, dx[i], dy[i]);

			// �Ķ� ������ ���ۿ� ������ �ȵǴϱ� �ش� ���� Ž���� ��ȿ�� �Ѵ�.
			if (map[bx2][by2] == 'O')
			{
				continue;
			}
			else if (map[rx2][ry2] == 'O')
			{
				cout << count2 << endl;
				return;
			}

			// �̵��� ���� �������� �Ķ����� ��ġ�� ��쿡 ���� ó��.
			if (rx2 == bx2 && ry2 == by2)
			{
				// �������� �Ķ������� �̵��� ĭ ���� �� ���ٴ� ���� �Ķ��� �ڿ� ��ġ�߾��ٴ� ��. ����, �������� ��ġ�� ��������� �Ѵ�.
				if (moved_red > moved_blue)
				{
					rx2		-= dx[i];
					ry2		-= dy[i];
				}
				else
				{
					bx2		-= dx[i];
					by2		-= dy[i];
				}
			}

			// ������ ã�� ���� ���������� ���ߴٸ� �ش� ��ġ�� ť�� �ְ� ������ ��ġ�� Ž���ϵ��� �Ѵ�.
			// ��, �̹� Ž���ߴ� ���� ���� �ʵ��� �Ѵ�.
			if (check[rx2][ry2][bx2][by2] == true)
			{
				continue;
			}
			
			bead_queue.push({ rx2, ry2, bx2, by2, count2 });
			check[rx2][ry2][bx2][by2]	= true;
		}
	}

	cout << "-1" << endl;
}

int main()
{
	bead.count				= 0;

	cin >> N;
	cin >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 'R')
			{
				bead.rx	= i;
				bead.ry = j;
			}
			else if (map[i][j] == 'B')
			{
				bead.bx = i;
				bead.by = j;
			}
		}
	}

	// ���� ó�� ��� ť�� push
	bead_queue.push(bead);
	check[bead.rx][bead.ry][bead.bx][bead.by]	= true;
	bfs();

	return 0;
}