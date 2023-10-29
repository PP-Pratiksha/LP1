#include <bits/stdc++.h>
#include<iostream>
using namespace std;
#define MAX 20
class Scheduler;
class Job{
	string name;
	int priority;
	int arrTime,burstTime,servTime,waitTime,TATime,compTime;
public:
	Job(){
		name="";
		arrTime=burstTime=servTime=priority=waitTime=TATime=compTime=0;
	}
	friend Scheduler;
};
class Scheduler{
	Job allProcess[MAX];
	int n;
public:
	void addProcesses(int m){
		this->n=m;
		for(int i=0;i<n;i++){
			cout<<"\n-----Job"<<i+1<<"------"<<endl;
			cout<<"Enter job name: ";cin>>allProcess[i].name;
			cout<<"Enter job priority : ";cin>>allProcess[i].priority;
			cout<<"Enter job arrival time: ";cin>>allProcess[i].arrTime;
			cout<<"Enter job burst time: ";cin>>allProcess[i].burstTime;
		}
	}
	void calcWaitTime(){
		allProcess[0].waitTime=0;
		allProcess[0].servTime=allProcess[0].arrTime;
		for(int i=1;i<n;i++){
			allProcess[i].servTime=allProcess[i-1].servTime+allProcess[i-1].burstTime;
			allProcess[i].waitTime = allProcess[i].servTime - allProcess[i].arrTime;
			if (allProcess[i].waitTime < 0)
				 allProcess[i].waitTime = 0;
		}
	}
	void calcTATime(){
		for(int i=0;i<n;i++){
			allProcess[i].TATime=allProcess[i].burstTime+allProcess[i].waitTime;
		}
	}
	static bool compareTime(Job &j1,Job &j2){
		return (j1.arrTime<j2.arrTime);
	}
	vector<float> FCFS(int pr){
		if(pr==1)
			cout << "\nNumber "<<"Processes " << " Burst Time " << " Arrival Time "<< " Waiting Time " << " Turn-Around Time "<< " Completion Time \n";
		int total_wt = 0, total_tat = 0;
		sort(allProcess,allProcess+this->n,compareTime);
		calcWaitTime();
		calcTATime();
		for (int i=0;i<n;i++)
		{
		   total_wt = total_wt + allProcess[i].waitTime;
		   total_tat = total_tat + allProcess[i].TATime;
		   int compl_time = allProcess[i].TATime + allProcess[i].arrTime;
		   if(pr==1)
		   	   cout <<i+1<<" \t "<< allProcess[i].name << "\t\t" << allProcess[i].burstTime << "\t\t"<< allProcess[i].arrTime << "\t\t" << allProcess[i].waitTime <<"\t\t"<< allProcess[i].TATime<<"\t\t "<<compl_time<<endl;
		}
		if(pr==1){
			cout << "Average waiting time = "<< (float)total_wt/(float)n;
			cout << "\nAverage turn around time = "<< (float)total_tat/(float)n;
		}
		vector<float>v;
		v.push_back((float)total_wt/(float)n);
		v.push_back((float)total_tat/(float)n);
		return v;
	}
	static bool comparePriority(Job j1,Job j2){
		return j2.priority<j1.priority;
	}
	vector<float> priorityScheduling(int pr){
		if(pr==1)
			cout << "\nNumber "<<"Processes " << " Burst Time " << " Arrival Time "<< " Waiting Time " << " Turn-Around Time "<< " Completion Time \n";
		int total_wt = 0, total_tat = 0;
		sort(allProcess,allProcess+this->n,comparePriority);
		calcWaitTime();
		calcTATime();
		for (int i=0;i<n;i++)
		{
			total_wt = total_wt + allProcess[i].waitTime;
			total_tat = total_tat + allProcess[i].TATime;
			int compl_time = allProcess[i].TATime + allProcess[i].arrTime;
			if(pr==1)
				cout <<i+1<<" \t "<< allProcess[i].name << "\t\t" << allProcess[i].burstTime << "\t\t"<< allProcess[i].arrTime << "\t\t" << allProcess[i].waitTime <<"\t\t"<< allProcess[i].TATime<<"\t\t "<<compl_time<<endl;
		}
		if(pr==1)
			{cout << "Average waiting time = "<< (float)total_wt/(float)n;
			cout << "\nAverage turn around time = "<< (float)total_tat/(float)n;
			}
		vector<float>v;
		v.push_back((float)total_wt/(float)n);
		v.push_back((float)total_tat/(float)n);
		return v;
	}
	static bool compareBurst(Job j1,Job j2){
			return j2.burstTime>j1.burstTime;
		}
	vector<float> SJF(int pr){
		sort(allProcess,allProcess+this->n,compareTime);
		int i=0,j,comp=0;
		int burst[n];
		for(int i=0;i<n;i++){
			burst[i]=allProcess[i].burstTime;
		}
		while(comp<this->n){
			for(j=0;j<n;j++){
				if(allProcess[j].arrTime>i){
					break;
				}
			}
			sort(allProcess,allProcess+this->n,compareBurst);
			if(j>0)
			{      for(j=0;j<n;j++)
						{
							if(burst[i]!=0)
							break;
						}
						if(allProcess[j].arrTime>i)

						{
							i=allProcess[j].arrTime;

						}
						allProcess[j].compTime=i+1;
						burst[i]--;
					}
			i++;
			comp=0;
			for(j=0;j<n;j++)
			{
				if(burst[i]==0)
				  comp++;
			}

		}
		calcWaitTime();
		calcTATime();
		int total_wt=0,total_tat=0;
		if(pr==1)
			cout << "\nNumber "<<"Processes " << " Burst Time " << " Arrival Time "<< " Waiting Time " << " Turn-Around Time "<< " Completion Time \n";
		for (int i=0;i<n;i++)
				{
					total_wt= total_wt + allProcess[i].waitTime;
					total_tat = total_tat + allProcess[i].TATime;
					int compl_time = allProcess[i].TATime + allProcess[i].arrTime;
					if(pr==1)
						cout <<i+1<<" \t "<< allProcess[i].name << "\t\t" << allProcess[i].burstTime << "\t\t"<< allProcess[i].arrTime << "\t\t" << allProcess[i].waitTime <<"\t\t"<< allProcess[i].TATime<<"\t\t "<<compl_time<<endl;
				}
				if(pr==1)
				{cout << "Average waiting time = "<< (float)total_wt/(float)n;
					cout << "\nAverage turn around time = "<< (float)total_tat/(float)n;}
				vector<float>v;
				v.push_back((float)total_wt/(float)n);
				v.push_back((float)total_tat/(float)n);
				return v;
	}


	vector<float> RoundRobin(int pr){
		int tq,totalwt=0,totalTA=0;
		cout<<"Enter time quanta: ";cin>>tq;
		int total=0,counter=0,x=n,i=0;
		int temp[n];
		for(int i=0;i<n;i++){
			temp[i]=allProcess[i].burstTime;
		}
		if(pr==1)
			cout << "\nNumber "<<"Processes " << " Burst Time " << " Arrival Time "<< " Waiting Time " << " Turn-Around Time "<<endl;
		for(i=0,total=0;x!=0;){
			if(temp[i] <= tq&& temp[i] > 0)
			{
			  total = total + temp[i];
			  temp[i] = 0;
			  counter = 1;
			}
			else if(temp[i] > 0)
			{
			   temp[i] = temp[i] - tq;
			   total = total + tq;
			}

			if(temp[i] == 0 && counter == 1)
			{
			   x--;
			   allProcess[i].TATime=total-allProcess[i].arrTime;
			   allProcess[i].waitTime=total-allProcess[i].burstTime-allProcess[i].arrTime;
			   if(pr==1)
				   cout <<i+1<<" \t "<< allProcess[i].name << "\t\t" << allProcess[i].burstTime << "\t\t"<< allProcess[i].arrTime << "\t\t" << allProcess[i].waitTime <<"\t\t"<< allProcess[i].TATime<<endl;
			   totalwt=totalwt+total-allProcess[i].burstTime-allProcess[i].arrTime;
			   totalTA=totalTA+total-allProcess[i].arrTime;
			   counter=0;
			}
			if(i == n - 1)
			{
			    i = 0;
			}
			else if(allProcess[i + 1].arrTime <= total)
			{
			     i++;
			}
			else
			{
			    i = 0;
			}
		}
		if(pr==1)
		{cout << "Average waiting time = "<< (float)totalwt/(float)n;
		cout << "\nAverage turn around time = "<< (float)totalTA/(float)n;
		}
		vector<float>v;
		v.push_back((float)totalwt/(float)n);
		v.push_back((float)totalTA/(float)n);
		return v;
	}

};
int main() {
	Scheduler s;
	int cho,n;
	cout<<"---------CPU Process Scheduling Simulation----------"<<endl;
	while(true){
		cout<<"\n------------Menu-------------\n1.Add processes\n2.First Come First Serve(FCFS)\n3.Priority Scheduling\n4.SJF Scheduling\n5.Round Robin Scheduling\nEnter your choice: ";cin>>cho;
		switch(cho){
		case 1:
			cout<<"\nEnter number of processes: ";cin>>n;
			s.addProcesses(n);
			cout<<"\nAdded successfully!"<<endl;
			break;
		case 2:
			cout<<"\nFirst Come First Serve(FCFS) Scheduling Order: "<<endl;
			s.FCFS(1);
			break;
		case 3:
			cout<<"\nPriority Scheduling Order: "<<endl;
			s.priorityScheduling(1);
			break;
		case 4:
			cout<<"\nSJF Scheduling Order: "<<endl;
			s.SJF(1);
			break;
		case 5:
			cout<<"\nRound Robin Order: "<<endl;
			s.RoundRobin(1);
			break;
		}
	}
	return 0;
}