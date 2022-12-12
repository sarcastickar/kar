#include <bits/stdc++.h>
using namespace std;

vector<int> completion(int n, vector<pair<int, int>> &v)
{
    vector<int> completion_time;
    int ct = v[0].first;
    for (int i = 0; i < n; i++)
    {
        ct += v[i].second;
        completion_time.push_back(ct);
        if (i != n - 1)
        {
            if (v[i + 1].first > ct)
            {
                ct = v[i + 1].first;
            }
        }
    }
    return completion_time;
}

vector<int> turn_around(int n, vector<pair<int, int>> &v, vector<int> &completion_time)
{
    vector<int> turn_around_time;
    for (int i = 0; i < n; i++)
    {
        turn_around_time.push_back(completion_time[i] - v[i].first);
    }
    return turn_around_time;
}

vector<int> waiting(int n, vector<pair<int, int>> &v, vector<int> &turn_around_time)
{
    vector<int> waiting_time;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        waiting_time.push_back(turn_around_time[i] - v[i].second);
        sum += turn_around_time[i] - v[i].second;
    }
    cout << "Average Waiting Time: " << (float)sum / n << endl;
    return waiting_time;
}

void Output_Table(int n, vector<pair<int, int>> &v, vector<pair<int, int>> &v1, vector<int> &completion_time, vector<int> &turn_around_time, vector<int> &waiting_time)
{
    cout << "PId" << setw(9) << "AT" << setw(10) << "BT" << setw(10) << "CT" << setw(10) << "TAT" << setw(10) << "WT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << v1[i].second << setw(10) << v[i].first << setw(10) << v[i].second << setw(10) << completion_time[i] << setw(10) << turn_around_time[i] << setw(10) << waiting_time[i] << endl;
    }
}

int main()
{
    int n;
    cout << "Enter number of process: ";
    cin >> n;
    vector<int> arrival_time;
    vector<int> burst_time;

    cout << "Enter arrival time of processes: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arrival_time.push_back(x);
    }

    cout << "Enter burst time of processes: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        burst_time.push_back(x);
    }
    vector<pair<int, int>> v1;
    map<int, int> m;
    for (int i = 0; i < n; i++)
    {
        v1.push_back({arrival_time[i], i + 1});
        m[i + 1] = burst_time[i];
    }
    sort(v1.begin(), v1.end());
    vector<pair<int, int>> v;
    vector<pair<int, int>> v2;
    for (int i = 0; i < n; i++)
    {
        v.push_back({v1[i].first, m[v1[i].second]});
    }
    sort(v.begin(), v.end());
    vector<int> completion_time = completion(n, v);
    vector<int> turn_around_time = turn_around(n, v, completion_time);
    vector<int> waiting_time = waiting(n, v, turn_around_time);
    Output_Table(n, v, v1, completion_time, turn_around_time, waiting_time);

    return 0;
}