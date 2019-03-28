// https://www.acmicpc.net/problem/13460
#include <iostream>
#include <queue>

using namespace std;

struct _bead_info
{
	int						rx, ry, bx, by;
	int						count;
};

bool						check[10][10][10][10];		// 빨간공, 파란공 둘 다 체크하기 위해 4차원 배열 사용.
char						map[10][10] = { 0, };
int							N, M;
const int					dx[4] = { -1, 0, 1, 0 };
const int					dy[4] = { 0, 1, 0, -1 };

_bead_info					bead;
queue<_bead_info>			bead_queue;

/**
 * int &x -> 구슬 x 좌표
 * int &y -> 구슬 y 좌표
 * int dx -> x좌표 이동 방향
 * int dy -> y좌표 이동 방향
 * return int -> 해당 구슬이 몇칸 만큼 움직였는지에 대한 값 반환
 * dx, dy의 값에 따라 # 그리고 O가 아닐때 까지 구슬 방향 이동시켜주는 함수
**/
int move(int &x, int &y, int dx, int dy)
{
	int						moved = 0;
	// # 그리고 O가 아닐때 까지 dx, dy 방향으로 구슬 이동
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

		// 구슬을 4방향으로 이동시키면서 구슬을 빼낼 수 있는지 BFS 탐색.
		for (int i = 0; i < 4; i++)
		{
			int				rx2= rx, ry2 = ry, bx2 = bx, by2 = by;
			int				count2 = count + 1;
			int				moved_red, moved_blue;
			// 빨간 구슬, 파란 구슬 이동
			moved_red		= move(rx2, ry2, dx[i], dy[i]);
			moved_blue		= move(bx2, by2, dx[i], dy[i]);

			// 파란 구슬이 구멍에 빠지면 안되니까 해당 방향 탐색은 무효로 한다.
			if (map[bx2][by2] == 'O')
			{
				continue;
			}
			else if (map[rx2][ry2] == 'O')
			{
				cout << count2 << endl;
				return;
			}

			// 이동한 다음 빨간공과 파란공이 겹치는 경우에 대한 처리.
			if (rx2 == bx2 && ry2 == by2)
			{
				// 빨간공이 파란공보다 이동한 칸 수가 더 많다는 것은 파란공 뒤에 위치했었다는 것. 따라서, 빨간공의 위치를 수정해줘야 한다.
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

			// 구멍을 찾지 못해 빠져나가지 못했다면 해당 위치를 큐에 넣고 인접한 위치를 탐색하도록 한다.
			// 단, 이미 탐색했던 곳은 하지 않도록 한다.
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

	// 가장 처음 노드 큐에 push
	bead_queue.push(bead);
	check[bead.rx][bead.ry][bead.bx][bead.by]	= true;
	bfs();

	return 0;
}