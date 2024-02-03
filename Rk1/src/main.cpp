#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> arr, int x1, int x2)
{
    int flag = 0;
    int i = 0;
    for (; i < arr.size() - 1; i++)
    {
        if (arr[i] == x1 &&  arr[i + 1] == x2)
            flag = 1;
        if (flag == 1)
            break;
    }
    if (flag == 1)
        return i;
    else 
        return -1;
}

int main()
{
    vector<int> arr;
    int x1, x2, len;
    cin >> len;
    int input;
    for (int i = 0; i < len; i++)
    {
        cin >> input;
        arr.push_back(input);
    }
    cin >> x1 >> x2;
    if (x1 >= x2)
    {
        cout << "Input error" << endl;
        return -1;
    }
    cout << solution(arr, x1, x2);
    return 0;
}