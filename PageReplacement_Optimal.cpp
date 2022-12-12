#include <bits/stdc++.h>
using namespace std;

bool search(int key, vector<int> &fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

// Function to find the frame that will not be used
// recently in future after given index in pages[0..pn-1]
int predict(int pages[], vector<int> &fr, int pn, int index)
{
    // Store the index of pages which are going
    // to be used recently in future
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++)
    {
        int j;
        for (j = index; j < pn; j++)
        {
            if (fr[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in future,
        // return it.
        if (j == pn)
            return i;
    }

    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

int optimalPage(int pages[], int n, int capacity)
{
    // Create an array for given number of
    // frames and initialize it as empty.
    vector<int> fr;

    // Traverse through page reference array
    // and check for miss and hit.
    int hit = 0;
    for (int i = 0; i < n; i++)
    {

        // Page found in a frame : HIT
        if (search(pages[i], fr))
        {
            hit++;
            continue;
        }

        // Page not found in a frame : MISS

        // If there is space available in frames.
        if (fr.size() < capacity)
            fr.push_back(pages[i]);

        // Find the page to be replaced.
        else
        {
            int j = predict(pages, fr, n, i + 1);
            fr[j] = pages[i];
        }
    }
    int PageFault = n - hit;
    return PageFault;
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

    int ans = optimalPage(pages, n, capacity);
    cout << "No. of page Faults: " << ans;

    return 0;
}