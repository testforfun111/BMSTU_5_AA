#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
vector<int> algoS(string text, string pattern);
void threadS(int start, int end, string& pattern, string& text, vector<int>& res);
vector<int> parallelS(string text, string pattern, int k);