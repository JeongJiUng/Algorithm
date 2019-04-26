// https://www.acmicpc.net/problem/7576
// http://blog.naver.com/PostView.nhn?blogId=occidere&logNo=221050425303&categoryNo=0&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView
// http://blog.naver.com/PostView.nhn?blogId=jhc9639&logNo=221335215340&categoryNo=110&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define						MAP_SIZE 1001

typedef struct _context
{
	int						x, y;
	int						day;
}TOMATO;

int							map[MAP_SIZE][MAP_SIZE];
int							M, N;
int							dx[4] = { 1, 0, -1, 0 };
int							dy[4] = { 0, 1, 0, -1 };
vector<pair<int, int>>		tomato;						// 익은 토마토의 x,y 위치
queue<TOMATO>				q;

void bfs()
{
	while (!q.empty())
	{
		TOMATO				infor = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			TOMATO			nInfor;
			nInfor.x		= infor.x + dx[i];
			nInfor.y		= infor.y + dy[i];
			nInfor.day		= infor.day + 1;

			if (nInfor.x >= M || nInfor.x < 0 || nInfor.y >= N || nInfor.y < 0)
				continue;

			if (map[nInfor.y][nInfor.x] == 0)
			{
				map[nInfor.y][nInfor.x]	= nInfor.day;
				q.push(nInfor);
			}
			else if (map[nInfor.y][nInfor.x] > 0)
			{
				if (map[nInfor.y][nInfor.x] > nInfor.day)
				{
					map[nInfor.y][nInfor.x]	= nInfor.day;
					q.push(nInfor);
				}
			}
		}
	}
}

int main()
{	
	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 1)
			{
				tomato.push_back(pair<int,int>(j, i));
				TOMATO				info;
				info.x				= j;
				info.y				= i;
				info.day = 0;
				q.push(info);
			}
		}
	}

	bfs();

	bool					bEnable = true;
	int						result = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (result < map[i][j])
				result		= map[i][j];

			if (map[i][j] == 0)
			{
				bEnable		= false;
				break;
			}
		}
		
		if (bEnable == false)
			break;
	}

	if (bEnable == false)
		cout << "-1" << endl;
	else if (result == 1)
		cout << "0" << endl;
	else
		cout << result << endl;

	cin >> N;

	return 0;
}