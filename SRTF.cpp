#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a[10], b[10], x[10], i, j, smallest, count = 0, time, n;
    double avg = 0, tt = 0, end;
    cout << "Enter the number of Processes: ";
    cin >> n;
    cout << "Enter arrival time: ";
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << "Enter burst time: ";
    for (i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    for (i = 0; i < n; i++)
        x[i] = b[i];

    b[9] = 9999;

    for (time = 0; count != n; time++)
    {
        smallest = 9;
        for (i = 0; i < n; i++)
        {
            if (a[i] <= time && b[i] < b[smallest] && b[i] > 0)
                smallest = i;
        }
        b[smallest]--;
        if (b[smallest] == 0)
        {
            count++;
            end = time + 1;
            avg = avg + end - a[smallest] - x[smallest];
            tt = tt + end - a[smallest];
        }
    }
    cout << "Average waiting time: " << avg / n << endl;
    cout << "Average Turnaround time: " << tt / n << endl;
    return 0;
}