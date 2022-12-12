#include <bits/stdc++.h>
using namespace std;
 
const int N=100005;
 
int n;
struct process
{
    int id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int finishing_time;
    int turn_around_time;
};
process P[N];
 
void SJF()
{
    int complete,current_time,index,minimum;
    double total_waiting_time = 0.0;
    double total_turn_around_time = 0.0;
 
    index = -1;
    complete = 0;
    current_time = 0;
    minimum = INT_MAX;
 
    while(complete < n)
    {
        for(int i=0; i<n; i++)
        {
            if(P[i].arrival_time <= current_time)
            {
                if(P[i].burst_time < minimum && P[i].finishing_time == 0)
                {
                    index = i;
                    minimum = P[i].burst_time;
                }
            }
        }
 
        if(index >= 0)
        {
            complete++;
            minimum = INT_MAX;
            current_time += P[index].burst_time;
            P[index].finishing_time = current_time;
            P[index].turn_around_time = P[index].finishing_time - P[index].arrival_time;
            P[index].waiting_time =  P[index].turn_around_time- P[index].burst_time;
 
            total_waiting_time += P[index].waiting_time;
            total_turn_around_time += P[index].turn_around_time;
 
            index = -1;
        }
        else
        {
            current_time++;
        }
    }
 
    cout<<"PId"<<setw(9)<<"AT"<<setw(9)<<"BT"<<setw(9)<<"CT"<<setw(9)<<"TAT"<<setw(9)<<"WT"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<P[i].id<<setw(9)<<P[i].arrival_time<<setw(9)<<P[i].burst_time<<setw(9)<<P[i].finishing_time<<setw(9)<<P[i].turn_around_time<<setw(9)<<P[i].waiting_time<<endl;
    }
}
 
int main()
{
    cout<<"Number of Processes: ";
    cin>>n;
 
    cout<<"Process Ids:\n";
    for(int i=0; i<n; i++) cin>>P[i].id;
 
    cout<<"Process Burst Times:\n";
    for(int i=0; i<n; i++) cin>>P[i].burst_time;
 
    cout<<"Process Arrival Times:\n";
    for(int i=0; i<n; i++) cin>>P[i].arrival_time;
 
    SJF();
 
    return 0;
}
/**
4
1 9 3 4
6 8 7 3
0 0 0 0
*/


// // #include <bits/stdc++.h>
// // using namespace std;

// // vector<int> completion(int n, vector<pair<int, int>> &v)
// // {
// //     vector<int> completion_time;
// //     int ct = v[0].second;
// //     for (int i = 0; i < n; i++)
// //     {
// //         ct += v[i].first;
// //         completion_time.push_back(ct);
// //         if (i != n - 1)
// //         {
// //             if (v[i + 1].second > ct)
// //             {
// //                 ct = v[i + 1].second;
// //             }
// //         }
// //     }
// //     return completion_time;
// // }

// // vector<int> turn_around(int n, vector<pair<int, int>> &v, vector<int> &completion_time)
// // {
// //     vector<int> turn_around_time;
// //     for (int i = 0; i < n; i++)
// //     {
// //         turn_around_time.push_back(completion_time[i] - v[i].second);
// //     }
// //     return turn_around_time;
// // }

// // vector<int> waiting(int n, vector<pair<int, int>> &v, vector<int> &turn_around_time)
// // {
// //     vector<int> waiting_time;
// //     int sum = 0;
// //     for (int i = 0; i < n; i++)
// //     {
// //         waiting_time.push_back(turn_around_time[i] - v[i].first);
// //         sum += turn_around_time[i] - v[i].second;
// //     }
// //     cout << "Average Waiting Time: " << (float)sum / n << endl;
// //     return waiting_time;
// // }

// // void Output_Table(int n, vector<pair<int, int>> &v, vector<pair<int, int>> &v1, vector<int> &completion_time, vector<int> &turn_around_time, vector<int> &waiting_time)
// // {
// //     cout << "PId" << setw(9) << "AT" << setw(10) << "BT" << setw(10) << "CT" << setw(10) << "TAT" << setw(10) << "WT" << endl;
// //     for (int i = 0; i < n; i++)
// //     {
// //         cout << v1[i].second << setw(10) << v[i].second << setw(10) << v[i].first << setw(10) << completion_time[i] << setw(10) << turn_around_time[i] << setw(10) << waiting_time[i] << endl;
// //     }
// // }

// // int main()
// // {
// //     int n;
// //     cout << "Enter number of process: ";
// //     cin >> n;
// //     vector<int> arrival_time;
// //     vector<int> burst_time;

// //     cout << "Enter arrival time of processes: ";
// //     for (int i = 0; i < n; i++)
// //     {
// //         int x;
// //         cin >> x;
// //         arrival_time.push_back(x);
// //     }

// //     cout << "Enter burst time of processes: ";
// //     for (int i = 0; i < n; i++)
// //     {
// //         int x;
// //         cin >> x;
// //         burst_time.push_back(x);
// //     }
// //     vector<pair<int, int>> v1;
// //     map<int, int> m;
// //     for (int i = 0; i < n; i++)
// //     {
// //         v1.push_back({arrival_time[i], i + 1});
// //         m[i + 1] = burst_time[i];
// //     }
// //     sort(v1.begin(), v1.end());
// //     vector<pair<int, int>> v;
// //     vector<pair<int, int>> v9;
// //     for (int i = 0; i < n; i++)
// //     {
// //         v.push_back({m[v1[i].second], v1[i].first});
// //     }
// //     sort(v.begin(), v.end());
// //     vector<int> completion_time = completion(n, v);
// //     vector<int> turn_around_time = turn_around(n, v, completion_time);
// //     vector<int> waiting_time = waiting(n, v, turn_around_time);
// //     Output_Table(n, v, v1, completion_time, turn_around_time, waiting_time);

// //     return 0;
// // }

// #include <bits/stdc++.h>
// using namespace std;

// int main()
// {
//     int arrival_time[10], burst_time[10], temp[10];
//     int i, smallest, count = 0, time, limit;
//     double wait_time = 0, turnaround_time = 0, end;
//     float average_waiting_time, average_turnaround_time;
//     cout << "Enter the Total Number of Processes: ";
//     cin >> limit;
//     cout << "Enter Details of " << limit << " Processes: " << endl;
//     for (i = 0; i < limit; i++)
//     {
//         cout << "Enter Arrival Time of process " << i << ": ";
//         cin >> arrival_time[i];
//         cout << "Enter Burst Time of process " << i << ": ";
//         cin >> burst_time[i];
//         temp[i] = burst_time[i];
//     }
//     burst_time[9] = 9999;
//     for (time = 0; count != limit; time++)
//     {
//         smallest = 9;
//         for (i = 0; i < limit; i++)
//         {
//             if (arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
//             {
//                 smallest = i;
//             }
//         }
//         burst_time[smallest]--;
//         if (burst_time[smallest] == 0)
//         {
//             count++;
//             end = time + 1;
//             wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
//             turnaround_time = turnaround_time + end - arrival_time[smallest];
//         }
//     }
//     average_waiting_time = wait_time / limit;
//     average_turnaround_time = turnaround_time / limit;
//     cout << "Average Waiting Time: " << average_waiting_time << endl;
//     cout << "Average Turn Around Time: " << average_turnaround_time << endl;
//     return 0;
// }