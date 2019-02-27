// https://www.swexpertacademy.com/main/learn/course/lectureProblemViewer.do
#include <iostream>
#include <algorithm>

using namespace std;

#define						MAX 10
#define						MIN	2
#define						PE 1e-12

typedef struct _testcase
{
	int						n;	// �ڼ�ü ���� (2 <= N <= 10)
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
		// �ڼ�ü ���� �Է�
		cin >> testcase[i].n;
		for (int j = 0; j < testcase[i].n; j++)
		{
			// �ڼ�ü ������ŭ x��ǥ �Է�
			cin >> testcase[i].pos[j];
		}
		for (int j = 0; j < testcase[i].n; j++)
		{
			// �� �ڼ�ü�� ���� �� �Է�
			cin >> testcase[i].mass[j];
		}
	}

	for (int case_num = 0; case_num < testcount; case_num++)
	{
		int					n = testcase[case_num].n;
		double				position = 0.0f;	// ��ü�� ��ġ

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
	// ��ü�� ��ǥ�� ����ؼ� Ž���ؼ� �˾ư��� �Ѵ�.
	// �ϴ��� _p�� _p+1�� �ڼ�ü�� ��� ��ǥ((_p + _p+1) / 2)�� ���������� �Ѵ�. -> ���Ƿ� ���� ��ü�� ��ġ.
	// ���Ƿ� ���� ��ü�� ��ġ�� ������� �η��� ���Ѵ�.
	// �η� ���� ���� ��ü�� ���������� ��������, �������� �������� �����Ѵ�.
	double					left = testcase[_case].pos[_p];
	double					right = testcase[_case].pos[_p+1];

	while (true)
	{
		double				lef_F = 0;						// ���� �η�
		double				rig_F = 0;						// ������ �η�
		double				F = 0;							// ���� - ������ �η�
		double				mid = (left + right) / 2.0f;

		// ���� �ڼ�ü�� �η� ���
		for (int i = 0; i <= _p; i++)
		{
			lef_F			+= testcase[_case].mass[i] / pow(testcase[_case].pos[i] - mid, 2.0f);
		}
		// ������ �ڼ�ü�� �η� ���
		for (int i = _p + 1; i < testcase[_case].n; i++)
		{
			rig_F			+= testcase[_case].mass[i] / pow(testcase[_case].pos[i] - mid, 2.0f);
		}
		// ���ʰ� �������� �η��� ���� ��� ������ �η��� �� ������ �ִ��� Ȯ��.
		F					= lef_F - rig_F;

		if (F < 0)
		{
			// ������ �η��� �� ������ �ִ� ���
			right			= mid;
		}
		else if (F > 0)
		{
			// ���� �η��� �� ������ �ִ� ���
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