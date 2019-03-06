//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV15PTkqAPYCFAYD&categoryId=AV15PTkqAPYCFAYD&categoryType=CODE
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _data
{
	int						left;
	int						right;

	_data(int _left, int _right)
	{
		left = _left;
		right = _right;
	}
}Data;

pair<int, int>				find(map<int, Data> _data, pair<int, int> _node);
vector<int>					getNodeList(map<int, Data> _data, int _start_node);
bool						findNode(vector<int>* _vec, int _start_node, int _find_node, map<int, Data> _data);
int							getSameNode(vector<int> _list_1, vector<int> _list_2);
int							getSize(int _start_node, map<int, Data> _data);

int main()
{
	int						testCase;
	int						V[10], E[10];
	pair<int, int>			node[10];
	map<int, Data>			items[10];	// 정점 값, 자식 정점 값

	cin >> testCase;

	for (int i = 0; i < testCase; i++)
	{
		// 각 테스트 케이스마다 트리의 정점의 총 수 V와 간선의 총 수 E, 정점 값을 나열한다.
		// V와 E 값, 공통 조상을 찾는 두개의 정점(node) 번호 입력
		cin >> V[i];
		cin >> E[i];
		cin >> node[i].first;
		cin >> node[i].second;

		for (int j = 0; j < E[i]; j++)
		{
			int					key, data;

			cin >> key;
			cin >> data;

			if (items[i].find(key) == items[i].end())
			{
				items[i].insert(make_pair(key, Data(0, 0)));
			}

			map<int, Data>::iterator	iter = items[i].find(key);
			if (iter->second.left == 0)
			{
				iter->second.left	= data;
				items[i].insert(make_pair(data, Data(0, 0)));
			}
			else
			{
				iter->second.right = data;
				items[i].insert(make_pair(data, Data(0, 0)));
			}
		}

		cout << "#" << i + 1 << " ";
		pair<int, int>		result = find(items[i], node[i]);
		cout << result.first << " " << result.second;
		cout << endl;
	}

	return 0;
}

pair<int, int> find(map<int, Data> _data, pair<int, int> _node)
{
	int						same_node, size = 0;;
	vector<int>				list_1, list_2;

	// 공통 조상을 찾아야 하는 정점을 루트부터 정점까지 리스트로 얻어온다.
	list_1					= getNodeList(_data, _node.first);
	list_2					= getNodeList(_data, _node.second);

	same_node				= getSameNode(list_1, list_2);
	size					= getSize(same_node, _data);


	return pair<int, int>(same_node, size);
}

vector<int> getNodeList(map<int, Data> _data, int _find_node)
{
	vector<int>				list;

	findNode(&list, _data.begin()->first, _find_node, _data);

	return list;
}

bool findNode(vector<int>* _vec, int _start_node, int _find_node, map<int, Data> _data)
{
	map<int, Data>::iterator	iter = _data.find(_start_node);

	if (iter == _data.end())
		return false;
		
	_vec->push_back(iter->first);

	if (iter->first == _find_node)
		return true;

	// 왼쪽 데이터부터 검사
	if (iter->second.left != 0)
	{
		if (!findNode(_vec, iter->second.left, _find_node, _data))
		{
			// 왼쪽부터 타고 내려온 벡터의 마지막 값이 찾으려는 정점의 값이 아닌 경우, 벡터 마지막 값 제거.
			_vec->pop_back();
		}
		else
			return true;
	}

	// 오른쪽 데이터 검사
	if (iter->second.right != 0)
	{
		if (!findNode(_vec, iter->second.right, _find_node, _data))
		{
			// 오른쪽부터 타고 내려온 벡터의 마지막 값이 찾으려는 정점의 값이 아닌 경우, 벡터 마지막 값 제거.
			_vec->pop_back();
		}
		else 
			return true;
	}

	return false;
}

int getSameNode(vector<int> _list_1, vector<int> _list_2)
{
	// 같은 정점을 가지고 있는지 확인.
	for (int i = _list_1.size()-1; i >= 0; i--)
	{
		for (int j = _list_2.size()-1; j >= 0; j--)
		{
			if (_list_1[i] == _list_2[j])
			{
				return _list_1[i];
			}
		}
	}
}

void procSize(int* _size, map<int, Data>::iterator _iter, map<int, Data> _data)
{
	*_size = *_size + 1;

	// 왼쪽부터 크기 증가
	if (_iter->second.left != 0)
	{
		procSize(_size, _data.find(_iter->second.left), _data);
	}

	// 오른쪽 크기 증가
	if (_iter->second.right != 0)
	{
		procSize(_size, _data.find(_iter->second.right), _data);
	}
}

int getSize(int _start_node, map<int, Data> _data)
{
	// 공통 조상을 루트로 하는 서브 트리의 크기 구함.
	int						size = 0;
	map<int, Data>::iterator	iter = _data.find(_start_node);

	procSize(&size, iter, _data);


	return size;
}