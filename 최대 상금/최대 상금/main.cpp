#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>>		Data;

int							swap_data(int _n);
int							compare_number(vector<int> _vec, int _count);
int							translate_to_num(vector<int> _vec);
vector<int>					translate_to_vec(int _num);

int main()
{
	int						N;

	cin >> N;

	Data.clear();

	for (int i = 0; i < N; i++)
	{
		int					number;
		int					count;
		
		cin >> number;
		cin >> count;
		Data.push_back(make_pair(number, count));
	}

	for (int i = 0; i < N; i++)
	{
		int					result = 0;
		cout << "#" << i + 1;
		result				= swap_data(i);
		cout << " " << result << endl;
	}

	return 0;
}

int swap_data(int _n)
{
	int						number = Data[_n].first;
	vector<int>				vec = translate_to_vec(number);	// number�� �ڸ������� ���Ϳ� ����. etc.) vec[0] = 1, vec[1] = 2, vec[3] = 5

	return compare_number(move(vec), Data[_n].second);
}

int compare_number(vector<int> _vec, int _count)
{
	// ������ 0��° ������ ���� ū ���� ��ȯ.
	// ��ȯ ���� ���� ��ȯ ���� ������ ū�� Ȯ��.
	// ũ�� ��ȯȽ�� ���� �� ������ ���� �迭�� �̵�. or ũ�� ������ ������ ���� �迭�� �̵�.
	// �ݺ�.
	// ������ ��������° ������ ��� Ȯ�� �ߴµ� ��ȯ Ƚ���� �����ִٸ�, ���� ���� ���� �� ���� ���� ��ȯ Ƚ����ŭ ��ȯ.
	int						prev/*��ȯ ���� ������*/, next/*��ȯ ���� ������*/;
	vector<int>				swap_data/*���� ��ġ�� �ٲ� �ӽ� ����.*/;
	
	prev					= translate_to_num(_vec);

	while (_count)
	{
		// ������ 0��° ������ Ž��.
		for (int i = 0; i < _vec.size()-1; i++)
		{
			// ���� ���� ������ ���� ū ������ �迭 ��ġ.
			int					top = i + 1;
			// i + 1��° �迭�� ������ i ��° ���̶� ũ�� ��.
			for (int j = i + 1; j < _vec.size(); j++)
			{
				// j��° �迭�� ���� i��° �迭�� ������ ũ��,
				if (_vec[i] < _vec[j])
				{
					// j��° �迭�� ���� ���� ���� ������ ���� ū ������ �迭 ��ġ�� ������ ũ��,
					if (_vec[j] >= _vec[top])
					{
						// ���� ���� ������ ���� ū ���� ����.
						top	= j;
					}
				}
			}
			// top ��ġ�� ���� i��° ��ġ�� ���� ���� ��ȯ���ش�.
			int				temp;
			swap_data		= _vec;
			temp			= move(swap_data[i]);
			swap_data[i]	= move(swap_data[top]);
			swap_data[top]	= move(temp);

			next			= translate_to_num(swap_data);
			// ��ȯ ���� �����Ϳ� ��ȯ ���� �����͸� ���ؼ� ��ȯ ���� �����Ͱ� ���� ������ ��ȯ Ƚ�� �����ϰ� ���� Ž�� ����.
			if (next >= prev)
			{
				prev		= next;
				_vec		= translate_to_vec(next);
				_count--;
			}

			if (_count == 0)
				break;
		}

		if (_count != 0)
		{

		}
	}

	return translate_to_num(_vec);
}

int translate_to_num(vector<int> _vec)
{
	// ���Ϳ� �ڸ�����ŭ �迭�� ����Ǿ� �ִ� �����͸� �ٽ� int�� ������ ����.
	reverse(_vec.begin(), _vec.end());
	int						result = _vec[0];

	for (int i = 1; i < _vec.size(); i++)
	{
		result += (_vec[i] * pow(10, i));
	}

	return result;
}

vector<int> translate_to_vec(int _num)
{
	vector<int>				vec;

	while (_num)
	{
		int					mod = _num % 10;
		_num = _num / 10;
		vec.push_back(mod);
	}
	reverse(vec.begin(), vec.end());

	return vec;
}