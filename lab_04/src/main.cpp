 //main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "algorithm.h"
#include "measure.h"
int main()
{
    //string txt = "ABABDABACDABABCABABAABCBCABCBABCBABCBABBABCBABCBABCBABCBBBBCBABCBABCBABCBABABABABAB";
    //string pat = "ABA";
    //string txt = "daymldayaaaymtstadayamkl";
    //string pat = "day";
    //string txt = "abcdabc";
    //string pat = "bc";
    string msg = "Menu: \n \
					0. Exit\n \
					1. Sequential algorithm\n\
					2. Parallel algorithm\n \
					3. Time\n \
Enter the command: ";
    int choice = -1;
    while (choice != 0)
    {
        cout << msg;
        cin >> choice;
        if (choice == 1 || choice == 2)
        {
            vector<int> res;
            string txt, pat;
            int k;
            cout << "Enter the string: ";
            cin >> txt;
            cout << "Enter the pattern: ";
            cin >> pat;
            if (choice == 1)
                res = algoS(txt, pat);
            else
            {
                cout << "Enter the number of threads: ";
                cin >> k;
                res = parallelS(txt, pat, k);
            }
            for (int i = 0; i < res.size(); i++)
                cout << res[i] << " ";
            cout << endl;
        }
        else if (choice == 3)
            timeMeasure();
        else
            choice = 0;
    }
    return 0;
}