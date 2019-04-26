// https://www.acmicpc.net/problem/2606
#include <iostream>
#include <vector>

using namespace std;

int							computer[101];
int							cnt;
vector<int>					network[101];

int							virus = -1;

void dfs(int _idx)
{
	int						size = network[_idx].size();
	virus++;

	for (int i = 0; i < size; i++)
	{
		int					com = network[_idx][i];

		if (computer[com] == true)
			continue;

		computer[com]		= true;
		dfs(com);
	}
}

int main()
{
	cin >> cnt >> cnt;

	for (int i = 1; i <= cnt; i++)
	{
		int a, b;

		cin >> a >> b;
		network[a].push_back(b);
		network[b].push_back(a);
	}

	computer[1]				= true;
	dfs(1);

	cout << virus << endl;
	cin >> cnt;

	return 0;
}