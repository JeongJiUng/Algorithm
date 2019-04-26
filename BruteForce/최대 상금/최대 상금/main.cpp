#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

vector<pair<int, int>>		Data;

int							swap_data(int _n);
vector<int>					swap(vector<int> _vec, int _index1, int _index2);
int							findSyncIndex(vector<int> _data, vector<int> _compare, int _index);
int							getMaxNumber(vector<int> _vec, int _count);
int							translate_to_num(vector<int> _vec);
vector<int>					translate_to_vec(int _num);
vector<int>					remainProc(vector<int> _vec, int _count);

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

	return getMaxNumber(move(vec), Data[_n].second);
}

vector<int> swap(vector<int> _vec, int _index1, int _index2)
{
	int						temp = _vec[_index1];
	_vec[_index1]			= _vec[_index2];
	_vec[_index2]			= temp;

	return _vec;
}

int findSyncIndex(vector<int> _data, vector<int> _compare, int _index)
{
	// _data�� _index ��° ���� �ϳ��� ��ġ�� ��ȯ�� ���鼭 _compare�� ��� ������ Ȯ��.
	// ���������� �ߺ��Ǵ� ������ ������ ���� ���� ��ȯ �ε����� ��ȯ�Ѵ�.
	int						valMax = 0;
	int						MaxSync = 0;
	int						findIndex = 0;

	for (int i = _index; i < _data.size(); i++)
	{
		int					sync = 0;

		if (_data[i] >= valMax)
		{
			vector<int>		temp_vec = swap(_data, _index, i);

			for (int j = 0; j < temp_vec.size(); j++)
			{
				if (temp_vec[j] == _compare[j])
				{
					sync++;
				}
			}

			if (MaxSync <= sync)
			{
				valMax		= _data[i];
				MaxSync		= sync;
				findIndex	= i;
			}
		}
	}

	return findIndex;
}

vector<int> remainProc(vector<int> _vec, int _count)
{
	bool					bOverlap = false;
	int						arr[2] = { 0 };

	for (int i = 0; i < _vec.size()-1; i++)
	{
		for (int j = i + 1; j < _vec.size(); j++)
		{
			if (_vec[i] == _vec[j])
			{
				arr[0]		= i;
				arr[1]		= j;
				bOverlap	= true;
				break;
			}
		}
		if (bOverlap)
			break;
	}

	if (!bOverlap)
	{
		int					min_num[2];
		vector<int>			temp = _vec;
		
		sort(temp.begin(), temp.end());
		min_num[0]			= temp[0];
		min_num[1]			= temp[1];

		for (int i = 0; i < _vec.size(); i++)
		{
			if (_vec[i] == min_num[0])
				arr[0]		= i;

			if (_vec[i] == min_num[1])
				arr[1]		= i;
		}
	}

	for (int i = 0; i < _count; i++)
	{
		_vec				= swap(_vec, arr[0], arr[1]);
	}

	return _vec;
}

int getMaxNumber(vector<int> _vec, int _count)
{
	/**
	*	#1. �����Ϸ��� Data�� Vector�� ���� -> (1) data
	*	#2. (1)�� ������������ ������ Vector ���� -> (2) compare
	*	#3. (1)�� _start��° �ε������� �ڱ⺸�� ū ���� ��쿡�� ��ġ ��ȯ�غ���. -> (3)
	*	#4. ��ȯ�� �� ��, (2)�� (3)�� ���� �迭�� ��� �´��� Ȯ�� -> sync, MaxSync
	*	#5. #3 ~ #4���� (1)�� ������ �迭���� �ݺ�.
	*	#6. sync�� ���� ����(MaxSync) �ε��� ��ġ�� ������ (1) ��ȯ ����.
	*	#7. ��ȯ Ƚ���� �� �� �� ���� #3���� ����.
	**/
	vector<int>				compare = _vec;
	vector<int>				data	= _vec;

	// ������������ ����
	sort(compare.begin(), compare.end(), greater<int>());

	for (int i = 0; i < data.size(); i++)
	{
		int					index = findSyncIndex(data, compare, i);
		data				= swap(data, i, index);

		if (index != i)
			_count--;

		if (_count == 0)
			return translate_to_num(data);
	}

	if (_count != 0)
	{
		data				= remainProc(data, _count);
	}

	return translate_to_num(data);
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