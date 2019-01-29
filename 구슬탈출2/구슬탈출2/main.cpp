// https://www.acmicpc.net/problem/13460
#include <iostream>
#include <queue>

using namespace				std;

typedef struct struct_queue
{
	bool					bEnable;			// Ȧ�� ã�Ҵ��� �ƴ��� ����
	queue<int*>				queue;
}STR_QUEUE;

void main()
{
	int						X, Y;
	int						RED_POS[2] = { 0 };		// ���� �� ��ġ
	int						BLUE_POS[2] = { 0 };	// �Ķ� �� ��ġ
	int						HOLE_POS[2] = { 0 };	// ���� ��ġ
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