#include <iostream>
#include <vector>
#include <random>
using namespace std;

default_random_engine dre;
uniform_int_distribution<> uid(1, 1000);

int main()
{
	vector<int> vec;
	vec.reserve(1000);
	for(int i=0; i< 1000; ++i)
	{
		vec.push_back(uid(dre));
	}

	for (const auto& i : vec)
	{
		cout << i << endl;
	}

	sort(vec.begin(), vec.end());

	for (const auto& i : vec)
	{
		cout << i << endl;
	}

}