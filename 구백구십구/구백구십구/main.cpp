#include <iostream>
#include <string>

using namespace std;

int main()
{
	string					number[] = {"", "��", "��", "��", "��", "��", "��", "ĥ", "��", "��"};
	string					jari[] = {"", "��", "��", "õ", "��", "��", "��", "õ", "��", "��", "��", "õ", "��"};

	string					input;

	cin >> input;

	string					newStr;
	for (int i = 0; i < input.length(); i++)
	{
		newStr				+= number[input[i] - '0'];

		if (i < input.length() - 1)
		{
			if (input[i] - '0' != 0)
				newStr			+= jari[(input.length() - 1) - i];
		}
	}

	cout << newStr << endl;

	cin >> input;
	
	return 0;
}