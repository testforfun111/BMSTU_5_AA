#include "Measure.h"
using namespace std;

string random_text(int len)
{
	unsigned seed = time(0);
	srand(seed);
	string res;
	for (int i = 0; i < len; i++)
	{
		char c = 'a' + rand() % 5;
		res += c;
	}
	return res;
}


void timeMeasure(void)
{
	vector<int> size_txt = { 10000, 20000, 30000, 40000, 50000, 60000};
	vector<int> size_patok = { 1, 2, 4, 8, 12, 16 };
	ofstream f1 = ofstream("../../tex/csv/4patok.csv");
	ofstream f2 = ofstream("../../tex/csv/manypatok.csv");
	f1 << "size_txt," << "size_patt," << "time1," << "time4" << endl;
	f1 << "\n";
	f2 << "size_patok," << "time" << endl;
	f2 << "\n";

	for (int i = 0; i < size_txt.size(); i++)
	{
		string txt = random_text(size_txt[i] * 10);
		string patt = random_text(5);
		vector<int> ans;
		clock_t beg, end;
		double time1 = 0, time2 = 0;
		for (int k = 0; k < TIMES; k++)
		{
			beg = clock();
			ans = algoS(txt, patt);
			end = clock();
			time1 += (end - beg);
		}
		time1 = (time1 * 1000) / (CLOCKS_PER_SEC * TIMES);
		cout << "Execution time of the sequential algorithm: " << time1 << " mc" << endl;

		for (int k = 0; k < TIMES; k++)
		{
			beg = clock();
			ans = parallelS(txt, patt, 12);
			end = clock();
			time2 += (end - beg);
		}
		time2 = (time2 * 1000) / (CLOCKS_PER_SEC * TIMES);
		cout << "Execution time of the parallel algorithm: " << time2 << " mc" << endl;
		f1 << size_txt[i] << "," << 5 << "," << time1 << "," << time2 << endl;

		string test_txt = random_text(5000000);
		string test_pat = random_text(5);
		int n = size_patok[i];
		time2 = 0;
		for (int k = 0; k < TIMES; k++)
		{
			beg = clock();
			ans = parallelS(test_txt, test_pat, n);
			end = clock();
			time2 += (end - beg);
		}
		time2 = (time2 * 1000) / (CLOCKS_PER_SEC * TIMES);
		cout << "Execution time of the parallel algorithm " << size_patok[i] << "thread: " << time2 << endl;
		f2 << size_patok[i] << "," << time2 << endl;
	}
	f1.close();
	f2.close();
}