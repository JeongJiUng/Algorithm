#include <iostream>

using namespace std;

#define			SIZE 1000

int main()
{
	int			input[SIZE] = { 0, };
	int			n;

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}

	// 거품정렬
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - (i + 1); j++)
		{
			if (input[j] > input[j + 1])
			{
				int			temp = input[j];
				input[j]	= input[j + 1];
				input[j + 1]= temp;
			}
		}
	}

	for (int i = 0; i < n; i++)
		cout << input[i] << endl;

	cin >> n;

	return 0;
}