#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

vector<int> getEratosthenes(int n)
{
	bool* prime = new bool[n];
	for(int i = 0; i < n; ++i)
		prime[i] = true;

	int p = 2;
	while(p * p <= n)
	{
		int index = p * p - 1;
		while (index < n)
		{
			prime[index] = false;
			index += p;
		}
		while (p < n && !prime[p])
			++p;
		++p;
	}
	vector<int> result;
	for(int i = 0; i < n; ++i)
	{
		if(prime[i])
			result.push_back(i + 1);
	}
	delete[] prime;
	return result;
}

int main()
{
	int n;
	vector<int> res;

	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		fin >> n;
		fin.close();
	}

	res = getEratosthenes(n);

	fstream fout;
	fout.open("output.txt", ios::out);
	for (int i = 0; i < res.size(); i++)
		fout << res[i] << " ";
	fout.close();

	return 0;
}