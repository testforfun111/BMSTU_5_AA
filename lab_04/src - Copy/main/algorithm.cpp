#include "algorithm.h"
mutex m_res;

vector<int> algoS(string text, string pattern)
{
	int n = text.size(), m = pattern.size();
	vector<int> res;
	
	int flag = 0;
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (text[i] == pattern[0])
			flag = 1;
		if (flag)
		{
			j = i + 1;
			for (int k = 1; flag && k < m && j < n; j++, k++)
				if (text[j] != pattern[k])
				{
					flag = 0;
				}
		}
		if (flag && j - i == m)
			res.push_back(i);
		flag = 0;
	}
	return res;
}

void threadS(int start, int end, string& pattern, string& text, vector<int>& res)
{
	int n = end, m = pattern.size();

	int flag = 0;
	int j = 0;
	for (int i = start; i < n; i++)
	{
		if (text[i] == pattern[0])
			flag = 1;
		if (flag)
		{
			j = i + 1;
			for (int k = 1; flag && k < m && j < n; j++, k++)
				if (text[j] != pattern[k])
				{
					flag = 0;
				}
		}
		if (flag && j - i == m)
		{
			m_res.lock();
			res.push_back(i);
			m_res.unlock();
			flag = 0;
		}
	}
}

vector<int> parallelS(string text, string pattern, int k)
{
	vector<int> res;
	int n = text.size(), m = pattern.size();

	vector<thread> threads_1;
	int segmentSize = n / k;
	int start, end;
	for (int i = 0; i < k; i++)
	{
		start = i * segmentSize;
		end = (i == k - 1) ? n : (i + 1) * segmentSize;
		threads_1.emplace_back(threadS, start, end, ref(pattern), ref(text), ref(res));
	}
	for (auto& th : threads_1)
		th.join();

	vector<thread> threads_2;
	for (int i = 1; i <= k - 1; i++)
	{
		start = i * segmentSize - (m - 1);
		end = i * segmentSize + (m - 1);
		threads_2.emplace_back(threadS, start, end, ref(pattern), ref(text), ref(res));
	}
	for (auto& th : threads_2)
		th.join();
	return res;
}
