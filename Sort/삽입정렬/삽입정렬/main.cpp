#include <iostream>

using namespace std;

#define						SIZE 1000

int main()
{
	int						input[SIZE];

	int						n;

	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> input[i];

	// 삽입정렬 시작
	for (int i = 1; i < n; i++)
	{
		int					key = input[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (key < input[j])
			{
				input[j+1]	= input[j];
				input[j]	= key;
			}
		}
	}

	for (int i = 0; i < n; i++)
		cout << input [i] << endl;

	cin >> n;

	return 0;
}