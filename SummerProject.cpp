#include<iostream>
using namespace std;

void findTurnAroundTime(int pro[], int n,int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}


void findWaitingTimeRR(int pro [], int n,int bt[], int wt[], int quantum)
{
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];
  
    int t = 0;
    while (1)
    {
        bool done = true;
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = false;
  
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
  
        if (done == true)
          break;
    }
}
void findavgTimeRR(int pro[], int n, int bt[],int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
  
    findWaitingTimeRR(pro, n, bt, wt, quantum);
    
    findTurnAroundTime(pro, n, bt, wt, tat);
  
    cout << "Processes "<< " Burst time "<< " Waiting time " << " Turn around time\n";
  
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << bt[i] <<"\t "<< wt[i] <<"\t\t " << tat[i] <<endl;
    }
  
    cout << "Average waiting time = "<< (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "<< (float)total_tat / (float)n;
}



void findWaitingTimeSRTF(int pro[],int n,int bt[],int at[],int wt[])
{
    int rt[n];
 
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];
 
    int complete = 0, t = 0, minm = INT_MAX;
    int finish_time,shortest = 0;
    bool check = false;
 
    while (complete != n) 
	{
 
        for (int j = 0; j < n; j++) 
		{
            if ((at[j] <= t) && (rt[j] < minm) && rt[j] > 0) 
			{
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
 
        if (check == false) 
		{
            t++;
            continue;
        }
 
        rt[shortest]--;
 
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
 
        if (rt[shortest] == 0) 
		{
            complete++;
            check = false;
 
            finish_time = t + 1;
 
            wt[shortest] = finish_time -bt[shortest] -at[shortest];
 
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}
void findavgTimeSRTF(int pro[], int n,int at[],int bt[])
{
    int wt[n], tat[n], total_wt = 0,total_tat = 0;
 
    findWaitingTimeSRTF(pro,n,bt,at,wt);
 
    findTurnAroundTime(pro,n,bt, wt, tat);
 
    cout << "Processes "<< " Arrival time "<< "   Burst time    "<< "   Waiting time "<< "   Turn around time\n";
 
    for (int i = 0; i < n; i++) 
	{
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << pro[i] << "\t\t"<< at[i] << "\t\t"<< bt[i] << "\t\t " << wt[i]<< "\t\t " << tat[i] << endl;
    }
 
    cout << "\nAverage waiting time = "<< (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "<< (float)total_tat / (float)n;
}



void findWaitingTimeFCFS(int pro[], int n,int bt[], int wt[])
{
    wt[0] = 0;
    for (int  i = 1; i < n ; i++ )
        wt[i] =  bt[i-1] + wt[i-1] ;
}
void findavgTimeFCFS(int pro[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
 
    findWaitingTimeFCFS(pro, n, bt, wt);
 
    findTurnAroundTime(pro, n, bt, wt, tat);
 
    cout << "Processes  "<< " Burst time  "<< " Waiting time  " << " Turn around time\n";
 
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << "   " << pro[i] << "\t\t" << bt[i] <<"\t    "<< wt[i] <<"\t\t  " << tat[i] <<endl;
    }
 
    cout << "Average waiting time = "<< (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "<< (float)total_tat / (float)n;
}




int main()
{
	cout<<"Press 1:First Come First Serve"<<endl
	<<"Press 2:Shortest Job First(Preemptive) // Shortest Remaining Time First"<<endl
	<<"Press 3:Round Robin Scheduling"<<endl
	<<"Select Case : ";
	int test;
	cin>>test;
	cout<<endl;
	
	int n;
	cout<<"Enter number of Processes ";
	cin>>n;
	
    int processes[n];
    for(int i=0;i<n;i++)
    {
    	processes[i]=i+1;
	}
	cout<<endl;
	
    int arrival_time[n];
    if(test ==2)
    {
    	cout<<"Enter arrival time ";
        for(int i=0;i<n;i++)
        {
    	    cin>>arrival_time[i];
	    }
	    cout<<endl;
	}

    int  burst_time[n];
    cout<<"Enter burst time ";
    for(int i=0;i<n;i++)
    {
    	cin>>burst_time[i];
	}
	cout<<endl;
	int quantum;
	
	switch(test)
	{
		case 1:
			{
				findavgTimeFCFS(processes, n,  burst_time);
				break;
			}
		case 2:
			{
				findavgTimeSRTF(processes, n,arrival_time,burst_time);
				break;
			}
		case 3:
			{
				cout<<"Enter the quantum time ";
				cin>>quantum;
				findavgTimeRR(processes, n, burst_time, quantum);
				break;
			}
		default:
			{
				cout<<"Error: NOT VALID CASE";
				break;
			}
	}

    return 0;
}
