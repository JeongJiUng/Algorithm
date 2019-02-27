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
	vector<int>				vec = translate_to_vec(number);	// number를 자릿수별로 벡터에 저장. etc.) vec[0] = 1, vec[1] = 2, vec[3] = 5

	return compare_number(move(vec), Data[_n].second);
}

int compare_number(vector<int> _vec, int _count)
{
	// 벡터의 0번째 값부터 가장 큰 수와 교환.
	// 교환 후의 값이 교환 전의 값보다 큰지 확인.
	// 크면 교환횟수 차감 후 벡터의 다음 배열로 이동. or 크지 않으면 벡터의 다음 배열로 이동.
	// 반복.
	// 벡터의 마지막번째 값까지 모두 확인 했는데 교환 횟수가 남아있다면, 가장 작은 값과 그 다음 값을 교환 횟수만큼 교환.
	int						prev/*교환 이전 데이터*/, next/*교환 이후 데이터*/;
	vector<int>				swap_data/*값의 위치를 바꾼 임시 벡터.*/;
	
	prev					= translate_to_num(_vec);

	while (_count)
	{
		// 벡터의 0번째 값부터 탐색.
		for (int i = 0; i < _vec.size()-1; i++)
		{
			// 현재 비교한 숫자중 가장 큰 숫자의 배열 위치.
			int					top = i + 1;
			// i + 1번째 배열의 값부터 i 번째 값이랑 크기 비교.
			for (int j = i + 1; j < _vec.size(); j++)
			{
				// j번째 배열의 값이 i번째 배열의 값보다 크고,
				if (_vec[i] < _vec[j])
				{
					// j번째 배열의 값이 현재 비교한 숫사중 가장 큰 숫자의 배열 위치의 값보다 크면,
					if (_vec[j] >= _vec[top])
					{
						// 현재 비교한 숫자중 가장 큰 숫자 갱신.
						top	= j;
					}
				}
			}
			// top 위치의 값고 i번째 위치의 값을 서로 교환해준다.
			int				temp;
			swap_data		= _vec;
			temp			= move(swap_data[i]);
			swap_data[i]	= move(swap_data[top]);
			swap_data[top]	= move(temp);

			next			= translate_to_num(swap_data);
			// 교환 이후 데이터와 교환 이전 데이터를 비교해서 교환 이후 데이터가 값이 높으면 교환 횟수 차감하고 다음 탐색 진행.
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
	// 벡터에 자릿수만큼 배열로 저장되어 있는 데이터를 다시 int형 값으로 변경.
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