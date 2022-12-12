#include <bits/stdc++.h>
using namespace std;

int PageFaults(int pages[], int n, int capacity)
{
    int pagefault = 0;
    unordered_set<int> s;
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (s.size() < capacity)
        {
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                q.push(pages[i]);
                pagefault++;
            }
        }
        else
        {
            if (s.find(pages[i]) == s.end())
            {
                int val=q.front();
                q.pop();
                s.erase(val);
                s.insert(pages[i]);
                q.push(pages[i]);
                pagefault++;
            }
        }
    }
    return pagefault;
}

int main()
{
    int n, capacity;
    cout << "Enter size of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter pages: ";
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }
    cout << "Enter capacity: ";
    cin >> capacity;

    int ans = PageFaults(pages, n, capacity);
    cout << "No. of page Faults: " << ans;

    return 0;
}