#include <bits/stdc++.h>
using namespace std;

int main()
{
    int cnt, j, n, t, remain, flag = 0, tq;
    int wt = 0, tat = 0, at[10], bt[10], rt[10];
    cout << "Enter Total Process: ";
    cin >> n;
    remain = n;
    for (cnt = 0; cnt < n; cnt++)
    {
        cout << "Enter Arrival Time for Process" << cnt << ": ";
        cin >> at[cnt];
        cout << "Enter Burst Time for Process" << cnt << ": ";
        cin >> bt[cnt];
        rt[cnt] = bt[cnt];
    }
    cout << "Enter Time Quantum: ";
    cin >> tq;
    cout << "\n\nProcess\t|Arrival Time\t|Burst Time\t|Completion Time\t|Turnaround Time|Waiting Time\n\n";
    for (t = 0, cnt = 0; remain != 0;)
    {
        if (rt[cnt] <= tq && rt[cnt] > 0)
        {
            t += rt[cnt];
            rt[cnt] = 0;
            flag = 1;
        }
        else if (rt[cnt] > 0)
        {
            rt[cnt] -= tq;
            t += tq;
        }
        if (rt[cnt] == 0 && flag == 1)
        {
            remain--;
            cout << "P" << cnt << "\t|\t" << at[cnt] << "\t|\t" << bt[cnt] << "\t|\t" << rt[cnt] << "\t|\t" << t - at[cnt] << "\t|\t" << t - at[cnt] - bt[cnt] << "\n";
            wt += t - at[cnt] - bt[cnt];
            tat += t - at[cnt];
            flag = 0;
        }
        if (cnt == n - 1)
            cnt = 0;
        else if (at[cnt + 1] <= t)
            cnt++;
        else
            cnt = 0;
    }
    cout << "Average Waiting Time: " << wt * 1.0 / n << endl;
    cout << "Average Turnaround Time: " << tat * 1.0 / n;

    return 0;
}