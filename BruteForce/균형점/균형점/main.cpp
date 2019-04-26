// https://www.swexpertacademy.com/main/learn/course/lectureProblemViewer.do
#include <iostream>
#include <algorithm>

using namespace std;

#define						MAX 10
#define						MIN	2
#define						PE 1e-12

typedef struct _testcase
{
	int						n;	// 자성체 개수 (2 <= N <= 10)
	int						pos[MAX];
	int						mass[MAX];
}TESTCASE;

TESTCASE					testcase[10];

double						binary_serach(int _case, int _p);

int main()
{
	int						testcount;

	cin >> testcount;

	for (int i = 0; i < testcount; i++)
	{
		// 자성체 개수 입력
		cin >> testcase[i].n;
		for (int j = 0; j < testcase[i].n; j++)
		{
			// 자성체 개수만큼 x좌표 입력
			cin >> testcase[i].pos[j];
		}
		for (int j = 0; j < testcase[i].n; j++)
		{
			// 각 자성체의 질량 값 입력
			cin >> testcase[i].mass[j];
		}
	}

	for (int case_num = 0; case_num < testcount; case_num++)
	{
		int					n = testcase[case_num].n;
		double				position = 0.0f;	// 물체의 위치

		cout << "#" << case_num+1;
		for (int i = 0; i < n - 1; i++)
		{
			position		= binary_serach(case_num, i);
			printf(" %0.10lf", position);
		}
		cout << endl;
	}

	cin >> testcount;

	return 0;
}

double binary_serach(int _case, int _p)
{
	// 물체의 좌표를 계속해서 탐색해서 알아가야 한다.
	// 일단은 _p와 _p+1의 자성체의 가운데 좌표((_p + _p+1) / 2)를 시작점으로 한다. -> 임의로 정한 물체의 위치.
	// 임의로 정한 물체의 위치를 기반으로 인력을 구한다.
	// 인력 값에 따라 물체를 오른쪽으로 움직일지, 왼쪽으로 움직일지 결정한다.
	double					left = testcase[_case].pos[_p];
	double					right = testcase[_case].pos[_p+1];

	while (true)
	{
		double				lef_F = 0;						// 왼쪽 인력
		double				rig_F = 0;						// 오른쪽 인력
		double				F = 0;							// 왼쪽 - 오른쪽 인력
		double				mid = (left + right) / 2.0f;

		// 왼쪽 자성체의 인력 계산
		for (int i = 0; i <= _p; i++)
		{
			lef_F			+= testcase[_case].mass[i] / pow(testcase[_case].pos[i] - mid, 2.0f);
		}
		// 오른쪽 자성체의 인력 계산
		for (int i = _p + 1; i < testcase[_case].n; i++)
		{
			rig_F			+= testcase[_case].mass[i] / pow(testcase[_case].pos[i] - mid, 2.0f);
		}
		// 왼쪽과 오른쪽의 인력을 빼서 어느 방향의 인력이 더 영향이 있는지 확인.
		F					= lef_F - rig_F;

		if (F < 0)
		{
			// 오른쪽 인력이 더 영향을 주는 경우
			right			= mid;
		}
		else if (F > 0)
		{
			// 왼쪽 인력이 더 영향을 주는 경우
			left			= mid;
		}
		else
		{
			return mid;
		}

		if (abs(left - right) < PE)
			return mid;
	}
}