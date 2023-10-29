#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int totalPageFaults = 0; // Initialize a global variable to keep track of total page faults

void FIFO(int n, int arr[], int f)
{
    int pageFault = 0;
    int s = 0;
    int res[f];
    for (int i = 0; i < f; i++)
    {
        res[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        s = 0;
        for (int j = 0; j < f; j++)
        {
            if (arr[i] == res[j])
            {
                s++;
                pageFault--;
            }
        }
        pageFault++;
        if ((pageFault <= f) && (s == 0))
        {
            res[i] = arr[i];
        }
        else if (s == 0)
        {
            res[(pageFault - 1) % f] = arr[i];
        }
    }
    totalPageFaults += pageFault; // Increment total page faults
    cout<<"Page Faults:"<<totalPageFaults;
}

int predict(int arr[], vector<int> &fr, int n, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++)
    {
        int j;
        for (j = index; j < n; j++)
        {
            if (fr[i] == arr[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
        {
            return i;
        }
    }
    return (res == -1) ? 0 : res;
}

int prediction(int arr[], vector<int> &fr, int n, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++)
    {
        int j;
        for (j = index - 1; j >= 0; j--)
        {
            if (fr[i] == arr[j])
            {
                if (j < farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
        {
            return i;
        }
    }
    return (res == -1) ? 0 : res;
}

bool search(int key, vector<int> &fr)
{
    for (int i = 0; i < fr.size(); i++)
    {
        if (fr[i] == key)
        {
            return true;
        }
    }
    return false;
}

void opr(int pn, int page[], int fn)
{
    vector<int> fr;
    int pageFault = 0; // Initialize page fault counter for this algorithm
    int hit = 0;
    for (int i = 0; i < pn; i++)
    {
        if (search(page[i], fr))
        {
            hit++;
            continue;
        }

        if (fr.size() < fn)
        {
            fr.push_back(page[i]);
        }
        else
        {
            int j = predict(page, fr, pn, i + 1);
            fr[j] = page[i];
        }
        pageFault++;
    }
    totalPageFaults += pageFault; // Increment total page faults
    cout<<"Page Faults:"<<totalPageFaults;
}

void LRU(int pn, int page[], int fn)
{
    vector<int> fr;
    int pageFault = 0; // Initialize page fault counter for this algorithm
    int hit = 0;
    for (int i = 0; i < pn; i++)
    {
        if (search(page[i], fr))
        {
            hit++;
            continue;
        }
        if (fr.size() < fn)
        {
            fr.push_back(page[i]);
        }
        else
        {
            int j = prediction(page, fr, pn, i + 1);
            fr[j] = page[i];
        }
        pageFault++;
    }
    totalPageFaults += pageFault; // Increment total page faults
    cout<<"Page Faults:"<<totalPageFaults;
}

int main()
{
    cout << "Enter All Required Data" << endl;
    int n;
    cout << "Enter the number of pages:";
    cin >> n;
    cout << "Enter the reference string:" << endl;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Page No " << i + 1 << ":";
        cin >> arr[i];
    }
    cout << "How many number of frames you are providing:";
    int f;
    int ch;
    cin >> f;
    do
    {
        cout << "\n******************PAGE REPLACEMENT ALGORITHM******************" << endl;
        cout << "1.FIFO" << endl;
        cout << "2.Optical" << endl;
        cout << "3.LRU" << endl;
        cout << "Enter your choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            FIFO(n, arr, f);
            break;
        case 2:
            opr(n, arr, f);
            break;
        case 3:
            LRU(n, arr, f);
            break;
        case 4:
            cout << "Total Page Faults: " << totalPageFaults << endl;
            cout << "Thank You for using this Program!!";
            exit(0);
            break;
        default:
            cout << "\nPlease enter the correct choice!!!";
        }
    } while (ch != 4);
    return 0;
}

