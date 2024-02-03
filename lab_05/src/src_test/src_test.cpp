#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex> 
#include <queue>
#include <cstdio>
#include <thread>
using namespace std;

ofstream Myfile;

struct strings {
    string text;
    string pattern;
};

using strings_t = struct strings;

struct strings_state
{
    bool stage_1;
    bool stage_2;
    bool stage_3;
};

using strings_state_t = struct strings_state;

struct result_time
{
    int task;
    int tape;

    double beg;
    double end;

    chrono::time_point<chrono::system_clock> time_begin;
};

using res_time_t = struct result_time;

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

string reverse_string(string pattern)
{
    string res;
    int len = pattern.size();
    for (int i = len - 1; i >= 0; i--)
    {
        res += pattern[i];
    }
    return res;
}

void write_to_file(ofstream& file, string pattern, string text, vector<int>& task1, vector<int>& task2)
{
    file << pattern << "\n";
    file << text << "\n";
    for (int i = 0; i < task1.size(); i++)
        file << task1[i] << " ";
    file << "\n";
    for (int i = 0; i < task2.size(); i++)
        file << task2[i] << " ";
    file << "\n";
}

void init_time_result_arr(std::vector<res_time_t>& time_result_arr,
    std::chrono::time_point<std::chrono::system_clock> time_begin,
    int cnt_matr, int cnt_threads)
{
    int len = cnt_matr * cnt_threads;
    time_result_arr.resize(len);

    for (int i = 0; i < len; i++)
    {
        res_time_t time_res;
        time_res.time_begin = time_begin;

        time_result_arr[i] = time_res;
    }

}

void print_res_time(std::vector<res_time_t>& time_result_arr, int size_arr)
{
    printf("--------------------------------------------------------"
        "\n   matrix  |    step  | time start | time end \n"
        "--------------------------------------------------------\n");

    for (int i = 0; i < size_arr; i++)
    {
        printf("    %3d      |     %2d     |   %.6f   |   %.6f   \n",
            time_result_arr[i].task,
            time_result_arr[i].tape,
            time_result_arr[i].beg,
            time_result_arr[i].end);

        if ((i + 1) % 3 == 0)
        {
            printf("--------------------------------------------------------\n");
        }
    }
}

void save_result(std::vector<res_time_t>& time_result_arr,
    std::chrono::time_point<std::chrono::system_clock> time_start,
    std::chrono::time_point<std::chrono::system_clock> time_end,
    std::chrono::time_point<std::chrono::system_clock> time_begin,
    int task_num, int numb_stage)
{
    double beg_time = (std::chrono::duration_cast<std::chrono::nanoseconds>
        (time_start - time_begin).count()) / 1e9;

    double end_time = (std::chrono::duration_cast<std::chrono::nanoseconds>
        (time_end - time_begin).count()) / 1e9;

    int index = (task_num - 1) * 3 + numb_stage - 1;

    time_result_arr[index].task = task_num;
    time_result_arr[index].tape = numb_stage;
    time_result_arr[index].beg = beg_time;
    time_result_arr[index].end = end_time;
}

vector<int> task1(mutex& m1, queue<strings_t>& qA1, queue<strings_t>& qA2)
{
    m1.lock();
    strings_t tmpStrings = qA1.front();
    m1.unlock();
    vector<int> tmpV = algoS(tmpStrings.text, tmpStrings.pattern);

    m1.lock();
    qA2.push(tmpStrings);
    m1.unlock();

    qA1.pop();
    return tmpV;
}

vector<int> task2(mutex& m1, mutex& m2, queue<strings_t>& qA2, queue<strings_t>& qA3)
{

    m1.lock();
    strings_t tmpStrings = qA2.front();
    m1.unlock();

    vector<int> tmpV = algoS(tmpStrings.text, reverse_string(tmpStrings.pattern));

    m2.lock();
    qA3.push(tmpStrings);
    m2.unlock();
    m1.lock();
    qA2.pop();
    m1.unlock();
    return tmpV;
}

void task3(mutex& m2, queue<strings_t>& qA3, vector<int>& V1, vector<int>& V2, ofstream& file)
{
    m2.lock();
    strings_t tmpStrings = qA3.front();
    m2.unlock();

    write_to_file(file, tmpStrings.pattern, tmpStrings.text, V1, V2);

    m2.lock();
    qA3.pop();
    m2.unlock();
}

void liner(int size, int cnt, bool is_count)
{
    queue<strings_t> qA1;
    queue<strings_t> qA2;
    queue<strings_t> qA3;
    vector<int> tmpV1;
    vector<int> tmpV2;
    mutex m1;
    mutex m2;

    std::chrono::time_point<std::chrono::system_clock> time_start, time_end,
        time_begin = std::chrono::system_clock::now();

    std::vector<res_time_t> time_result_arr;
    init_time_result_arr(time_result_arr, time_begin, cnt, 3);

    for (int i = 0; i < cnt; i++)
    {
        strings_t strings;
        strings.text = random_text(size);
        strings.pattern = random_text(size / 4);

        qA1.push(strings);
    }

    for (int i = 0; i < cnt; i++)
    {
        time_start = chrono::system_clock::now();
        tmpV1 = task1(ref(m1), ref(qA1), ref(qA2));
        time_end = std::chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 1);

        time_start = chrono::system_clock::now();
        tmpV2 = task2(ref(m1), ref(m2), ref(qA2), ref(qA3));
        time_end = std::chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 2);

        time_start = chrono::system_clock::now();
        task3(ref(m2), ref(qA3), ref(tmpV1), ref(tmpV2), Myfile);
        time_end = std::chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 3);
    }

    if (is_count)
    {
        printf("     %4d      |     %4d      |   %.6f  \n",
            size, cnt, time_result_arr[cnt - 1].end);
    }
    else
    {
        print_res_time(time_result_arr, cnt * 3);
    }
}

void parallel_stage_1(mutex& time_mutex, mutex& m1, queue<strings_t>& qA1, queue<strings_t>& qA2, vector<vector<int>>& V1, vector<strings_state_t>& state, vector<res_time_t>& time_result_arr, bool & qA1_is_empty)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while (!qA1.empty())
    {
        time_start = chrono::system_clock::now();
        vector<int> tmp = task1(m1, qA1, qA2);
        time_end = std::chrono::system_clock::now();
        time_mutex.lock();
        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 1);
        time_mutex.unlock();
        V1.push_back(tmp);
        state[task_num - 1].stage_1 = true;
        task_num++;
    }
    qA1_is_empty = true;
}

void parallel_stage_2(mutex& time_mutex, mutex& m1, mutex& m2, queue<strings_t>& qA2, queue<strings_t>& qA3, vector<vector<int>>& V2, vector<strings_state_t>& state, vector<res_time_t>& time_result_arr, bool &qA1_is_empty, bool & qA2_is_empty)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while (1)
    {
        if (qA2.empty() == false)
        {
            if (state[task_num - 1].stage_1 == true)
            {
                time_start = chrono::system_clock::now();
                vector<int> tmp = task2(m1, m2, qA2, qA3);
                time_end = std::chrono::system_clock::now();
                time_mutex.lock();
                save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 2);
                time_mutex.unlock();
                V2.push_back(tmp);
                state[task_num - 1].stage_2 = true;
                task_num++;
            }
        }
        else if (qA1_is_empty)
            break;
    }
    qA2_is_empty = true;
}

void parallel_stage_3(mutex& time_mutex, mutex& m2, queue<strings_t>& qA3, vector<vector<int>>& V1, vector<vector<int>>& V2, vector<strings_state_t>& state, vector<res_time_t>& time_result_arr, bool& qA2_is_empty)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while (1)
    {
        if (qA3.empty() == false)
        {
            if (state[task_num - 1].stage_2 == true && state[task_num - 1].stage_1 == true)
            {
                time_start = chrono::system_clock::now();
                task3(m2, qA3, V1[task_num - 1], V2[task_num - 1], Myfile);
                time_end = std::chrono::system_clock::now();
                time_mutex.lock();
                save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 3);
                time_mutex.unlock();
                state[task_num - 1].stage_3 = true;
                task_num++;
            }
        }
        else if (qA2_is_empty)
            break;
    }
}

void parallel(int size, int cnt, bool is_count)
{
    queue<strings_t> qA1;
    queue<strings_t> qA2;
    queue<strings_t> qA3;
    vector<vector<int>> V1;
    vector<vector<int>> V2;
    bool qA1_is_empty = false;
    bool qA2_is_empty = false;
    mutex m1;
    mutex m2;
    mutex time_mutex;

    for (int i = 0; i < cnt; i++)
    {
        strings_t strings;
        strings.text = random_text(size);
        strings.pattern = random_text(size / 4);
        qA1.push(strings);
    }

    vector<strings_state_t> state(cnt);
    for (int i = 0; i < cnt; i++)
    {
        strings_state_t tmp_state;
        tmp_state.stage_1 = false;
        tmp_state.stage_2 = false;
        tmp_state.stage_3 = false;
        state[i] = tmp_state;
    }
    chrono::time_point<std::chrono::system_clock> time_begin = chrono::system_clock::now();
    vector<res_time_t> time_result_arr;
    init_time_result_arr(time_result_arr, time_begin, cnt, 3);
    thread threads[3];
    threads[0] = thread(parallel_stage_1, ref(time_mutex), ref(m1), ref(qA1), ref(qA2), ref(V1), ref(state), ref(time_result_arr), ref(qA1_is_empty));
    threads[1] = thread(parallel_stage_2, ref(time_mutex), ref(m1), ref(m2), ref(qA2), ref(qA3), ref(V2), ref(state), ref(time_result_arr), ref(qA1_is_empty), ref(qA2_is_empty));
    threads[2] = thread(parallel_stage_3, ref(time_mutex), ref(m2), ref(qA3), ref(V1), ref(V2), ref(state), ref(time_result_arr), ref(qA2_is_empty));

    for (int i = 0; i < 3; i++)
        threads[i].join();
    if (is_count)
        printf("     %4d      |     %4d      |   %.6f  \n",
            size, cnt, time_result_arr[cnt - 1].end);
    else
        print_res_time(time_result_arr, cnt * 3);
}

int read_number_action()
{
    std::cout <<
        "\n\tMenu\n\n"
        "\t1. Linear\n"
        "\t2. Conveyor\n"
        "\t3. Time analysis\n"
        "\t0. Exit \n\n"
        "\tInput: ";

    int r;
    cin >> r;
    return r;
}

void compare_time()
{
    cout << "Time conversion\n";
    printf(" Text size | Number request |  Time end  \n"
        "-----------------------------------------------\n");
    for (int i = 50; i < 2000; i *= 2)
    {
        parallel(100, i, true);
    }
    cout << "Time for linear\n";
    printf(" Text size | Number request |  Time end  \n"
        "-----------------------------------------------\n");
    for (int i = 50; i < 2000; i *= 2)
    {
        liner(100, i, true);
    }
    cout << "Time conversion size\n";
    printf(" Text size | Number request |  Time end  \n"
        "-----------------------------------------------\n");
    for (int i = 20; i < 500; i *= 2)
    {
        parallel(i, 100, true);
    }
    cout << "Time linear size\n";
    printf(" Text size | Number request |  Time end  \n"
        "-----------------------------------------------\n");
    for (int i = 20; i < 500; i *= 2)
    {
        liner(i, 100, true);
    }

}

int main()
{
    srand(time(nullptr));
    int action = -1;
    Myfile.open("test.txt");

    while (action)
    {
        int action = read_number_action();
        if (action < 0 || action > 3)
        {
            cout << "Input again!\n";
            continue;
        }
        if (action == 1)
        {
            int size, cnt;
            cout << "\tInput size of string: ";
            cin >> size;
            cout << "\tInput number of request: ";
            cin >> cnt;
            liner(size, cnt, false);
        }
        else if (action == 2)
        {
            int size, cnt;
            cout << "\tInput size of string: ";
            cin >> size;
            cout << "\tInput number of request: ";
            cin >> cnt;
            parallel(size, cnt, false);
        }
        else if (action == 3)
        {
            compare_time();
        }
    }
    Myfile.close();
    return 0;
}
