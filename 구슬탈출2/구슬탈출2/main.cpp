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
 * dx, dy�� ���� ���� # �׸��� O�� �ƴҶ� ���� ���� ���� �̵������ִ� �Լ�
**/
void move(int &x, int &y, int dx, int dy)
{
	// # �׸��� O�� �ƴҶ� ���� dx, dy �������� ���� �̵�
	while (map[x + dx][y + dy] != '#' && map[x][y] != 'O')
	{
		x					+= dx;
		y					+= dy;
	}
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

		// ������ 4�������� �̵���Ű�鼭 ������ ���� �� �ִ��� BFS Ž��.
		for (int i = 0; i < 4; i++)
		{
			int				rx2= rx, ry2 = ry, bx2 = bx, by2 = by;
			int				count2 = count + 1;
			// ���� ����, �Ķ� ���� �̵�
			move(rx2, ry2, dx[i], dy[i]);
			move(bx2, by2, dx[i], dy[i]);

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

			// ������ ã�� ���� ���������� ���ߴٸ� �ش� ��ġ�� ť�� �ְ� ������ ��ġ�� Ž���ϵ��� �Ѵ�.
			// ��, �̹� Ž���ߴ� ���� ���� �ʵ��� �Ѵ�.
		}
	}
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
				bead.rx	= j;
				bead.ry = i;
			}
			else if (map[i][j] == 'B')
			{
				bead.bx = j;
				bead.by = i;
			}
		}
	}

	// ���� ó�� ��� ť�� push
	bead_queue.push(bead);
	check[bead.rx][bead.ry][bead.bx][bead.by]	= true;
	bfs();
	return 0;
}