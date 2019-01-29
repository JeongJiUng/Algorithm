// https://www.acmicpc.net/problem/13460
#include <iostream>
#include <queue>

using namespace				std;

typedef struct struct_queue
{
	bool					bEnable;			// 홀을 찾았는지 아닌지 여부
	queue<int*>				queue;
}STR_QUEUE;

void main()
{
	int						X, Y;
	int						RED_POS[2] = { 0 };		// 빨간 공 위치
	int						BLUE_POS[2] = { 0 };	// 파란 공 위치
	int						HOLE_POS[2] = { 0 };	// 구멍 위치
	char					M[10][10] = { 0 };
	
	STR_QUEUE				BFS_RED;
	STR_QUEUE				BFS_BLUE;
	BFS_RED.bEnable			= false;
	BFS_BLUE.bEnable		= false;

	cin >> X;
	cin >> Y;

	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			cin >> M[x][y];

			if (M[x][y] == 'R')
			{
				RED_POS[0] = x;
				RED_POS[1] = y;

				BFS_RED.queue.push(RED_POS);
			}
			else if (M[x][y] == 'B')
			{
				BLUE_POS[0] = x;
				BLUE_POS[1] = y;

				BFS_BLUE.queue.push(BLUE_POS);
			}
			else if (M[x][y] == 'O')
			{
				HOLE_POS[0] = x;
				HOLE_POS[1] = y;
			}
		}
	}

	// Proc BFS
}