#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void FIFO(int n, int arr[], int f)
{
    int pageFault = 0; // Initialize the page fault counter
    int s = 0;
    int res[f]; // An array to represent the frames in memory

    for (int i = 0; i < f; i++)
    {
        res[i] = -1; // Initialize the frames with -1 (indicating an empty frame)
    }
    cout << "******CONTENTS OF TABLE********" << endl; // Print the table header
    for (int i = 0; i < n; i++) // Loop through the reference string
    {
        s = 0;
        for (int j = 0; j < f; j++) // Loop through the frames
        {
            if (arr[i] == res[j]) // Check if the page in the reference string is already in a frame
            {
                s++; // If it's found in a frame, increment 's'
                pageFault--; // Decrement page fault (it will be incremented later)
            }
        }
        pageFault++; // Increment page fault for each memory access

        if ((pageFault <= f) && (s == 0)) // If there are empty frames and the page is not already in memory
        {
            res[i] = arr[i]; // Place the page into an empty frame
        }
        else if (s == 0) // If there are no empty frames and the page is not already in memory
        {
            res[(pageFault - 1) % f] = arr[i]; // Replace the page in the oldest frame (circular replacement)
        }

        for (int i = 0; i < f;i++) // Loop to print the contents of frames after each memory access
        {
            cout << res[i] << " ";
        }
        cout << "\n";
    }

    int hit = n - pageFault; // Calculate the number of hits
    cout << "\nTotal Number of Page Faults/Miss: " << pageFault << endl; // Print the total page faults
    cout << "Total Number of Page Hits: " << hit << endl; // Print the total page hits
}


int predict(int arr[], vector<int>& fr, int n, int index)
{
   int res = -1, farthest = index;
   for(int i = 0; i < fr.size(); i++) 
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
      if(j==n)
      {
      	return i;
	  }     
   }
   return (res == -1) ? 0 : res;
}

int prediction(int arr[], vector<int>& fr, int n, int index) 
{
   int res = -1, farthest = index;
   for (int i = 0; i < fr.size(); i++) 
   {
      int j;
      for (j = index-1; j>=0; j--) 
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
      if(j==n)
      {
      	return i;
	  }     
   }
   return (res == -1) ? 0 : res;
}

bool search(int key, vector<int>& fr) 
{
   for(int i = 0; i < fr.size(); i++)
   {
   
	   if (fr[i] == key)
	   {
	   		return true;
	   }
	}
   return false;
}
void opr(int pn, int page[],int fn) 
{
   vector<int> fr;
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
   }
   cout << "Hits = " << hit << endl;
   cout << "Misses = " << pn - hit << endl;
}

void LRU(int pn, int page[],int fn) 
{
   vector<int> fr;
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
   }
   cout << "Hits = " << hit << endl;
   cout << "Misses = " << pn - hit << endl;
}

int main()
{
	cout<<"Enter All Required Data"<<endl;
	int n;
	cout<<"Enter the number of pages:";
	cin>>n;
	cout<<"Enter the reference string:"<<endl;
	int arr[n];
	for(int i=0;i<n;i++)
	{
		cout<<"Page No "<<i+1<<":";
		cin>>arr[i];
	}
	cout<<"How many number of frames you are providing:";
	int f;
	int ch;
	cin>>f;
	do
	{
		cout<<"\n******************PAGE REPLACEMENT ALGORITHM******************"<<endl;
		cout<<"1.FIFO"<<endl;
		cout<<"2.Optical"<<endl;
		cout<<"3.LRU"<<endl;
		cout<<"Enter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1:
			FIFO(n,arr,f);
			break;
		case 2:
			opr(n,arr,f);
			break;
		case 3:
			LRU(n,arr,f);
			break;
		case 4:
			cout<<"Thank You for using this Program!!";
			exit(0);
			break;
		default:
			cout<<"\nPlease enter correct choice!!!";
		}
	}while(ch!=4);
	return 0;
}
