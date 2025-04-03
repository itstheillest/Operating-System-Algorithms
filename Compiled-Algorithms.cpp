/*
    Mark Clarenz Alpajora
    Mac Justin Azur
    France Evangelista
    Rhen Peñada
    John Carlo Villanueva
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string> //!!!!!!!!IMPORTANT!!!!!!!!   c++ version must be c++ 11
#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid;             // Process ID
    int arrival_time;    // Arrival time
    int burst_time;      // Burst time
    int remaining_time;  // Remaining time
    int start_time;      // Start time
    int completion_time; // Completion time
    int tat;             // Turnaround time
    int wt;              // Waiting time
    int rt;              // Response time
    int pl;				 // Priority level
    float rr;    		 // Response Ratio
    bool completed;      // Process completion status
};

struct Process_HRRN //Made for the stubbornness of the HRRN
{
    int pid;       // Unique process ID
    float arrival_time;     // Arrival Time
    float burst_time;     // Burst Time
    float completion_time;     // Completion Time
    float start_time; //Start Time
    float tat;    // Turnaround Time
    float wt;     // Waiting Time
    float rt;		//Response Time
    float rr;     // Response Ratio
    bool completed; // Process completion status
};

struct average
{
    float turnaround = 0.0;
    float waiting = 0.0;
    float reaction = 0.0;
}avg;

struct Disk 
{
    int req; //Disk requests
};

struct Computations
{
    int size;
    string direction;
    vector<int> left, right; //Movement
    vector<int> seek_sequence;
    int disk_size;
    int curTrack;
    int head;
    int distance;
    long long seekCount = 0;
} comp;

void clear(); //to clear
void pause(); //To pause
void patchnotes(); //to tell user what's new

void mainmenu(); //choose algorithms
void choiceCPUSchedalgo();
void choiceDiscSched();

//work in progress for CPU scheduling and Disc Management
void workinprogress();
void CPUworkinprogress();
void discworkinprogress();

void askprocess(int &, char);

//the actual calculation for Preemptiveand Non-preemptive scheduling
void FCFS(Process[], average, int, char);
void SJF(Process[], average, int, char);
void NPP(Process[], average, int, char);
void HRRN(vector<Process_HRRN> &, average, int, char);
void SRTF(Process[], average, int, char);
void PP(Process[], average, int, char);
void RR(Process[], average, int, vector<int> &, int, char);

//table and gantt chart
void gantt_chart(Process[], int, int &, vector<int> &, vector<int> &);
void gantt_chart_hrrn(vector<Process_HRRN> &, int, int &, vector<int> &, vector<int> &);
void table(Process[], average, int,  int &, vector<int> &, vector<int> &, char);


//Fixed Partition
void fixedPartition();

void temp_table(vector<int> &,vector<int> &,vector<int> &,vector<int> &,vector<int> &,
			vector<int> &,vector<int> &,vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void final_table(vector<int> &,vector<int> &,vector<int> &,vector<int> &,vector<int> &,
			vector<int> &,vector<int> &,vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void memory_allocation(int, int, vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void memory_deallocation(vector<int> &,vector<int> &,vector<int> &,vector<int> &,vector<int> &,
						vector<int> &,vector<int> &,vector<int> &, vector<int> &, vector<int> &, vector<int> &);

//Actuall calculations for the fixed partition algorithms
void FF(vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void BF(vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void WF(vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void NF(vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);

void deallocation_FF(vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void deallocation_BF(vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void deallocation_WF(vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);
void deallocation_NF(vector<int> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);

//Disc Scheduling functions
void discSchedulingInput(char);
void graph(vector<int>, int, vector<int>);

void FCFS(vector<int>, int, string, int);
void SSTF(vector<int> &, int, string, int);
void CSCAN(vector<Disk> &, Computations &);
void SCAN(vector<Disk> &, Computations &);
void LOOK(vector<int> , int, string, int);
void CLOOK(vector<int>, int, string, int);

bool compareArrival(Process p1, Process p2) {
    return p1.arrival_time < p2.arrival_time;
}

int main()
{
	char choice = ' ';
	int val = 0; //short for Validation
	int size = 0;
	average avg;


	cout << "Welcome to the Compiled Algorithm!\n\n";
	pause();
	clear();
	patchnotes();
	pause();
	clear();
	mainmenu();

	do
	{
		cout << "\nPlease Choose: ";
		cin >> choice;

		switch (choice)
		{
			case 'a':
			case 'A': cout << endl;
			clear();
			choiceCPUSchedalgo();
			val = 1;
				break;

			case 'b':
			case 'B': cout << endl;
			clear();
			fixedPartition();
			val = 1;
				break;

			case 'c':
			case 'C': cout << endl;
			clear();
			choiceDiscSched();
			val = 1;
				break;

			default:
				cout << endl << "-------------" << endl;
				cout << "| Misinput! |" << endl;
				cout << "-------------\n\n";
				pause();
				clear();
				mainmenu();
		}
	} while (val < 1);
}

void clear()
{
    system("cls");
}

void pause() //para less typings for system("pause")
{
	system("pause");
}

void patchnotes()
{
    cout << "Version 2-2.3-4.1.6 Completion Update Patch notes:";
	//2-2 means our year and section,
	//0.1-0.0 means completed preemptive(left) and non-preemptive(right),
	//0.0.1.0 means completed Fixed partition
	//0.0.0.1 means completed Disc Scheduling
	cout << "\n\nFeatures:" << endl;
	cout << "\n|-------------------- CPU Scheduling --------------------|" << endl;
	cout << "| 1. Shortest Remaining Time First (SRTF)" << endl;
	cout << "| 2. First Come First Serve (FCFS)" << endl;
	cout << "| 3. Shortest Job First (SJF)" << endl;
	cout << "| 4. Non-Preemptive Priority (NPP)" << endl;
	cout << "| 5. Round Robin(RR)" << endl;
	cout << "| 6. Preemptive Priority (PP)" << endl;
	cout << "| 7. High Response Ratio Next (HRRN)" << endl;
	cout << "\n|-------------------- Fixed Partition --------------------|" << endl;
	cout << "| 1. Fixed Partition" << endl;
	cout << "\n|-------------------- Disc Management/Scheduling --------------------|" << endl;
	cout << "| 1. First Come First Serve (FCFS)" << endl;
	cout << "| 2. Shortest Seek Time First (SSTF)" << endl;
	cout << "| 3. Scan" << endl;
	cout << "| 4. C-Scan" << endl;
	cout << "| 5. Look" << endl;
	cout << "| 6. C-Look" << endl;
    cout << "\n\n|-------------------- New --------------------|" << endl;
    cout << "| 1. Bug Fixes" << endl << endl;
}

void mainmenu()
{
	cout << "Please choose an algorithm ;)";
	cout << "\na) CPU Scheduling" << endl;
	cout << "b) Fixed Partition" << endl;
	cout << "c) Disc Management" << endl;
}

void workinprogress()
{
	cout << endl << "-------------------------------------------------" << endl;
	cout << "| Sorry! Work in progress!";
	cout << " Try again next time! |" << endl;
	cout << "-------------------------------------------------\n\n";
	pause();
	clear();
	mainmenu();
}

void CPUworkinprogress()
{
	cout << endl << "-------------------------------------------------" << endl;
	cout << "| Sorry! Work in progress!";
	cout << " Try again next time! |" << endl;
	cout << "-------------------------------------------------\n\n";
	pause();
	clear();
	choiceCPUSchedalgo();
}

void discworkinprogress()
{
	cout << endl << "-------------------------------------------------" << endl;
	cout << "| Sorry! Work in progress!";
	cout << " Try again next time! |" << endl;
	cout << "-------------------------------------------------\n\n";
	pause();
	clear();
	choiceDiscSched();
}

void choiceCPUSchedalgo()
{
	int val = 0;
	char choice = ' ';
	int processCount = 0;

	do
	{
		cout << "Please choose a CPU scheduling algorithm ;)";
		cout << "\n\nNon-Preemptive: " << endl;
		cout << "a) First Come, First Serve (FCFS)" << endl;
		cout << "b) Shortest Job First (SJF)" << endl;
		cout << "c) Priority" << endl;
		cout << "d) High Response Ratio Next (HRRN)" << endl;
		cout << "\n\nPreemptive: " << endl;
		cout << "e) Shortest Remaining Time First (SRTF)" << endl;
		cout << "f) Priority" << endl;
		cout << "g) Round Robin (RR)" << endl;
		cout << "\n\nenter X to return to the main menu." << endl;

		do
		{
			cout << "\nPlease Choose: ";
			cin >> choice;

			switch (choice)
			{
				case 'a':
				case 'A': cout << endl;
				clear();
				askprocess(processCount, choice);
				val = 1;
					break;

				case 'b':
				case 'B': cout << endl;
				clear();
				askprocess(processCount, choice);
				val = 1;
					break;

				case 'c':
				case 'C': cout << endl;
				clear();
				askprocess(processCount, choice);
				val = 1;
					break;

				case 'd':
				case 'D': cout << endl;
				clear();
				askprocess(processCount, choice);
				val = 1;
					break;

				case 'e':
				case 'E': cout << endl;
				clear();
				askprocess(processCount, choice);
				val = 1;
					break;

				case 'f':
				case 'F': cout << endl;
				clear();
				askprocess(processCount, choice);
				val = 1;
					break;

				case 'g':
				case 'G': cout << endl;
				clear();
				askprocess(processCount, choice);
				val = 1;
					break;

				case 'x':
				case 'X': cout << endl;
				clear();
				main();
					break;

				default:
				cout << "\nMisinput!\n\n";
				cin.clear();
    			cin.ignore();
				clear();
				choiceCPUSchedalgo();
			}
		} while(val < 1);
	} while (val < 1);
}

void askprocess (int &P, char choice)
{
	int confirm = 0;
	do
	{
    	cout << "Enter the number of processes: ";
    	cin >> P;

    	if (cin.fail())
			{
				cout << "\nMisinput!\n\n";
    			cin.clear();
    			cin.ignore();
			}
		else
		{
			cout << endl;
			confirm = 1;
		}
	} while (confirm == 0);

	average avg;
	Process processes[P];
	int size = P;
	 
	vector<Process_HRRN> processes_vec(size); //A vector was used for HRRN unlike the others which used arrays
	vector<int> rt(size+1, 0);
	int time_slice = 0;

	for (int i = 0; i < size; i++)
    {
        do
		{
    		cout << "Enter arrival time for process " << i + 1 << ": ";
        	cin >> processes[i].arrival_time;

    		if (cin.fail())
			{
				cout << "\nMisinput!\n";
    			cin.clear();
    			cin.ignore();
			}
			else
			{
				processes_vec[i].arrival_time = processes[i].arrival_time;
				confirm = 1;
			}
		} while (confirm == 0);

		confirm = 0;

		do
		{
    		cout << "Enter burst time for process " << i + 1 << ": ";
        	cin >> processes[i].burst_time;

    		if (cin.fail())
			{
				cout << "\nMisinput!\n";
    			cin.clear();
    			cin.ignore();
			}
			else
			{
				processes_vec[i].burst_time = processes[i].burst_time;
				confirm = 1;
			}
		} while (confirm == 0);

		if (choice == 'c' || choice == 'C' || choice == 'f' || choice == 'F')
		{
			do
			{
    			cout << "Enter priority level for process " << i + 1 << ": ";
        		cin >> processes[i].pl;

	    		if (cin.fail())
				{
					cout << "\nMisinput!\n";
   	 				cin.clear();
   		 			cin.ignore();
				}

				else
				{
					confirm = 1;
				}
			} while (confirm == 0);
		}
        processes[i].pid = i + 1;
        processes_vec[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
		rt[processes[i].pid] = processes[i].burst_time;
        processes[i].start_time = -1; // Initialize as -1 to indicate not started yet
        cout << endl;
    }

	if (choice == 'g' || choice == 'G')
		{	
        	do
			{
				cout << "Enter time slice: ";
        		cin >> time_slice;

    			if (cin.fail())
				{
					cout << "\nMisinput!\n";
    				cin.clear();
    				cin.ignore();
				} 
				else
				{
					confirm = 1;
				}	
			} while (confirm < 1);
		}

    switch (choice)
    {
    	case 'a':
		case 'A': FCFS (processes, avg, size, choice);
			break;

		case 'b':
		case 'B': SJF (processes, avg, size, choice);
			break;

		case 'c':
		case 'C': NPP (processes, avg, size, choice);
			break;

		case 'd':
		case 'D': HRRN (processes_vec, avg, size, choice);
			break;

		case 'e':
		case 'E': SRTF (processes, avg, size, choice);
			break;

		case 'f':
		case 'F': sort(processes, processes + size, compareArrival);
		PP (processes, avg, size, choice);
			break;

		case 'g':
		case 'G': RR (processes, avg, size, rt, time_slice, choice);
			break;

		default:
		cout << "\nMisinput!\n\n";
		pause();
		clear();

	}
}

void FCFS(Process processes[], average avg, int size, char choice)
{
	int time = 0, completed = 0, BT_temp = 0;
    //sort the arrival time
    for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if ((true && processes[j].arrival_time > processes[j+1].arrival_time) || (false && processes[j].pid > processes[j+1].pid))
			{
				swap(processes[j], processes[j+1]);
			}
		}
	}

	int gantt = 0;
    vector<int> vec(100, 0); //symbolizes Process ID
    vector<int> time_stamp(101, 0); //Symbolizes completion time or time stamps

	//table computation
	for (int i = 0; i < size; i++)
    {
    	BT_temp += processes[i].burst_time; // used to total all Burst Time
		processes[i].completion_time = BT_temp; //Get completion time for every burst time added

		time_stamp[gantt+1] = processes[i].completion_time; //time stamp for the gantt chart
		vec[gantt] = processes[i].pid; //Process ID for gantt chart

		if (i == 0) // 0-1=-1, index -1 doesn't work on cpp, therefore if found, start time = 0
		{
			processes[i].start_time = 0;
		}

		else
		{
			processes[i].start_time = processes[i-1].completion_time;
		}
		processes[i].tat = processes[i].completion_time - processes[i].arrival_time;
        processes[i].wt = processes[i].tat - processes[i].burst_time;
        processes[i].rt = processes[i].start_time - processes[i].arrival_time;
        gantt++;

	}

	float total_wt = 0, total_tat = 0, total_rt = 0;

	for (int i = 0; i < size; i++)
    {
        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
        total_rt += processes[i].rt;
    }

	avg.waiting = total_wt / size;
    avg.turnaround = total_tat / size;
    avg.reaction = total_rt / size;


	for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (processes[j].pid > processes[j + 1].pid)
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }

    table(processes, avg, size, gantt, vec, time_stamp, choice);
}

void SJF(Process processes[], average avg, int size, char choice)
{
	float BT_total, total_wt, total_tat, total_rt = 0;
	int gantt = 0;
    vector<int> vec(100, 0);
    vector<int> time_stamp(101, 0);

	vector<bool> completed(size, false);
	int intMAX = 2147483647; //ayaw gumana ng INT_MAX function dito
    int curr = 0, ind = -1, count = 0; // curr = current, ind = index

    while (count != size)
    {
        int minB = INT_MAX;

        ind = -1;
        for (int i = 0; i < size; i++)
        {
            if (processes[i].arrival_time <= curr && !completed[i])
            {
                if (processes[i].burst_time < minB)
                {
                    minB = processes[i].burst_time;
                    ind = i;
                }
                if (processes[i].burst_time == minB)
                {
                    if (processes[i].arrival_time < processes[ind].arrival_time)
                    {
                        minB = processes[i].burst_time;
                        ind = i;
                    }
                }
            }
        }
        if (ind != -1)
        {
            processes[ind].start_time = curr;


            processes[ind].completion_time = processes[ind].start_time + processes[ind].burst_time;
			time_stamp[gantt+1] = processes[ind].completion_time; //time stamp for the gantt chart

			vec[gantt] = processes[ind].pid; //Process ID for gantt chart
            processes[ind].tat = processes[ind].completion_time - processes[ind].arrival_time;

			processes[ind].wt = processes[ind].tat - processes[ind].burst_time;
            processes[ind].rt = processes[ind].start_time - processes[ind].arrival_time;

            completed[ind] = true;

            total_tat += processes[ind].tat;
			total_wt += processes[ind].wt;
            total_rt += processes[ind].rt;

            count++;
            gantt++;
            curr = processes[ind].completion_time;
        }
        else
        {
            curr++;
        }
    }

    avg.turnaround = total_tat / size;
	avg.waiting = total_wt / size;
    avg.reaction = total_rt / size;

	table(processes, avg, size, gantt, vec, time_stamp, choice);
}

void NPP (Process processes[], average avg, int size, char choice)
{
	float BT_total, total_wt, total_tat, total_rt = 0;
	// Sort processes by arrival time, and if equal, by priority
    sort(processes, processes + size, [](Process a, Process b) {
        if (a.arrival_time == b.arrival_time) {
            return a.pl < b.pl; // Higher priority (smaller number) first
        }
        return a.arrival_time < b.arrival_time;
    });

    int gantt = 0; // Keeps track of the current time of the scheduler
    vector<int> vec(100, 0); // Stores the sequence of processes for Gantt chart
    vector<int> time_stamp(101, 0);   // Stores the timeline for Gantt chart
    int current_time = 0;
        

    // Loop through processes to simulate scheduling
    for (int i = 0; i < size; i++) {
        int idx = -1; // Index of the process to be executed next
        for (int j = 0; j < size; j++) {
            if (processes[j].arrival_time <= current_time && processes[j].remaining_time > 0) {
                if (idx == -1 || processes[j].pl < processes[idx].pl) {
                    idx = j;
                }
            }
        }
        // If no process is ready, increment the time
        if (idx == -1) {
            current_time++;
        }
			
        // Execute the selected process
        processes[idx].start_time = current_time;
        processes[idx].completion_time = current_time + processes[idx].burst_time;
        time_stamp[gantt+1] = processes[idx].completion_time;
       	vec[gantt] = processes[idx].pid;
        processes[idx].tat = processes[idx].completion_time - processes[idx].arrival_time; // Turnaround time
        processes[idx].wt = processes[idx].tat - processes[idx].burst_time;               // Waiting time
        processes[idx].rt = processes[idx].start_time - processes[idx].arrival_time;      // Response time
		
        current_time += processes[idx].burst_time; // Update the current time
        processes[idx].remaining_time = 0;         // Mark the process as completed
		total_tat += processes[idx].tat;
		total_wt += processes[idx].wt;
        total_rt += processes[idx].rt;
		gantt++;   
    }
    
    // Sort processes back by process ID for table display
    sort(processes, processes + size, [](Process a, Process b) {
        return a.pid < b.pid; // Sort by Process ID
    });
    
    avg.turnaround = total_tat / size;
	avg.waiting = total_wt / size;
    avg.reaction = total_rt / size;
    
	table(processes, avg, size, gantt, vec, time_stamp, choice);
}

void HRRN(vector<Process_HRRN> &processes_vec, average avg, int size, char choice)
{
	float current_time = 0;
    int completed = 0;
    float total_tat = 0.0, total_wt = 0.0, total_rt = 0.0;
    
	int gantt = 0;
    vector<int> vec(100, 0); //symbolizes Process ID
    vector<int> time_stamp(101, 0); //Symbolizes completion time or time stamps
    
    
    while (completed < size) {
        // Calculate response ratio for each process
        for (auto &p : processes_vec) {
            if (!p.completed && p.arrival_time <= current_time) {
                p.rr = (p.burst_time + (current_time - p.arrival_time)) / p.burst_time;
            } else {
                p.rr = -1; // Mark as ineligible if not yet arrived or completed
            }
        }

        // Find the process with the highest response ratio
        auto it = max_element(processes_vec.begin(), processes_vec.end(), [](const Process_HRRN &a, const Process_HRRN &b) {
            return a.rr < b.rr;
        });

        if (it != processes_vec.end() && it->rr > 0) {
            // Execute the selected process
            Process_HRRN &p = *it;
            current_time = max(current_time, p.arrival_time) + p.burst_time;
            p.start_time = current_time;
            p.completion_time = current_time;
            
			time_stamp[gantt+1] = p.completion_time;
            vec[gantt] = p.pid;// before: processes[completed].pid after: p.pid
            
            p.tat = p.completion_time - p.arrival_time;
            p.wt = p.tat - p.burst_time;
            p.rt = p.start_time - p.arrival_time;

            total_tat += p.tat;
            total_wt += p.wt;
            total_rt += p.rt;

            p.completed = true;
            gantt++;
            completed++;

            //cout << "Time: " << current_time << " - Completed P" << p.id << "\n";
        } else {
            // Advance time if no process is eligible
            current_time++;
        }
    }
    
        cout << left
         << setw(10) << "PID"
         << setw(10) << "AT"
         << setw(10) << "BT";
    cout << setw(10) << "ST"
         << setw(10) << "CT"
         << setw(10) << "TAT"
         << setw(10) << "WT"
         << setw(10) << "RT"
         << endl;

    for (int i = 0; i < size; i++)
    {
        // Print process details
        cout << left
             << setw(10) << processes_vec[i].pid
             << setw(10) << processes_vec[i].arrival_time
             << setw(10) << processes_vec[i].burst_time;
        cout << setw(10) << processes_vec[i].start_time
             << setw(10) << processes_vec[i].completion_time
             << setw(10) << processes_vec[i].tat
             << setw(10) << processes_vec[i].wt
             << setw(10) << processes_vec[i].rt
             << endl;
    }
    
	gantt_chart_hrrn(processes_vec, size, gantt, vec, time_stamp);
}

void SRTF(Process processes[], average avg, int size, char choice)
{
	bool validaiton = true;

	//to sort the Arrival time
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if ((true && processes[j].arrival_time > processes[j+1].arrival_time) || (false && processes[j].pid > processes[j+1].pid))
			{
				swap(processes[j], processes[j+1]);
			}
		}
	}

	int gantt = 0;
    vector<int> vec(100, 0);
    vector<int> time_stamp(101, 0);
    int intMAX = 2147483647; //ayaw gumana ng INT_MAX function dito
	// Function to implement SRTF scheduling
	int time = 0, completed = 0;
    while (completed != size)
    {
        // Find process with shortest remaining time
        int shortest = -1;
        int minRT = INT_MAX;
        for (int i = 0; i < size; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].remaining_time < minRT)
            {
				minRT = processes[i].remaining_time;
				shortest = i;
			}
        }

        // If a process is found, execute it
        if (shortest != -1)
        {
            if (gantt == 0 || vec[gantt - 1] != processes[shortest].pid) //to set up the arrangement for the gnatt chart
            {
            	vec[gantt] = processes[shortest].pid;
            	time_stamp[gantt] = time;
            	gantt++;
			}

			if (processes[shortest].start_time == -1)
            {
                processes[shortest].start_time = time;
            }

            processes[shortest].remaining_time--;

            if (processes[shortest].remaining_time == 0)
            {
				processes[shortest].completion_time = time + 1;
                completed++;
            }
        }
        time++;
    }

    time_stamp[gantt] = time;

    // Calculate TAT, WT, RT, Total WT, Total TAT, Total RT, and averages
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < size; i++)
    {
        processes[i].tat = processes[i].completion_time - processes[i].arrival_time;
        processes[i].wt = processes[i].tat - processes[i].burst_time;
        processes[i].rt = processes[i].start_time - processes[i].arrival_time;

        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
        total_rt += processes[i].rt;
    }

    avg.waiting = total_wt / size;
    avg.turnaround = total_tat / size;
    avg.reaction = total_rt / size;

	//to show original position
	for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (processes[j].pid > processes[j + 1].pid)
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }

    table(processes, avg, size, gantt, vec, time_stamp, choice);
}

void PP(Process processes[], average avg, int size, char choice)
{
	int current_time = 0, completed = 0, gantt = 0;
	float total_wt = 0, total_tat = 0, total_rt = 0;
    vector<int> vec(1000), time_stamp(1000);

    for (int i = 0; i < size; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
    }

    while (completed < size) {
        int shortest = -1, min_priority = INT_MAX;

        for (int i = 0; i < size; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0)
			{
                if (processes[i].pl < min_priority || 
                   (processes[i].pl == min_priority && shortest != -1 && processes[i].arrival_time < processes[shortest].arrival_time)) {
                    min_priority = processes[i].pl;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            current_time++;
        } else {
            if (processes[shortest].start_time == -1) 
			{
                processes[shortest].start_time = current_time;
            }

            if (gantt == 0 || vec[gantt - 1] != processes[shortest].pid)
			{
                vec[gantt] = processes[shortest].pid;
                time_stamp[gantt] = current_time;
                gantt++;
            }

            processes[shortest].remaining_time--;
            current_time++;

            if (processes[shortest].remaining_time == 0) 
			{
                processes[shortest].completion_time = current_time;
                processes[shortest].tat = processes[shortest].completion_time - processes[shortest].arrival_time;
                processes[shortest].wt = processes[shortest].tat - processes[shortest].burst_time;
                processes[shortest].rt = processes[shortest].start_time - processes[shortest].arrival_time;
                
                total_wt += processes[shortest].wt;
        		total_tat += processes[shortest].tat;
       			total_rt += processes[shortest].rt;
       		
                completed++;
            }
        }
    }
    time_stamp[gantt] = current_time;
    
    avg.waiting = total_wt / size;
    avg.turnaround = total_tat / size;
    avg.reaction = total_rt / size;
    
    table(processes, avg, size, gantt, vec, time_stamp, choice);
}

void RR(Process processes[], average avg, int size, vector<int> &rt, int time_slice, char choice)
{
	bool validaiton = true;
	int gantt = 0;
    vector<int> vec(100, 0);
    vector<int> time_stamp(101, 0);
    int curr = 0, count = 0;
	//to sort the Arrival time
	for (int i = 0; i < size - 1; i++) 
	{
		for (int j = 0; j < size - i - 1; j++) 
		{
			if ((true && processes[j].arrival_time > processes[j+1].arrival_time) || (false && processes[j].pid > processes[j+1].pid)) 
			{	
				swap(processes[j], processes[j+1]);
			}
		}
	}
	
	// Function to implement RR scheduling
	queue<int> q;
    vector<int> mark(size, false);
    q.push(0);
    mark[0] = true;
	float total_wt = 0, total_tat = 0, total_rt = 0;
    while (count != size)
    {
        int idx = q.front();
        q.pop();
        if (rt[processes[idx].pid] == processes[idx].burst_time)
        {
            processes[idx].start_time = max(curr, processes[idx].arrival_time);
            curr = processes[idx].start_time;
            if (gantt == 0 || vec[gantt-1] != processes[idx].pid)
            {
            	vec[gantt] = processes[idx].pid;
            	time_stamp[gantt] = curr;
            	gantt++;
			}
        }
        if (rt[processes[idx].pid] - time_slice > 0)
        {
            curr += time_slice;
            rt[processes[idx].pid] -= time_slice;
            
            if (gantt == 0 || vec[gantt-1] != processes[idx].pid || time_stamp[gantt-1] != curr)
            {
            	vec[gantt] = processes[idx].pid;
            	time_stamp[gantt] = curr;
            	gantt++;
			}
        }
			
        else
        {
            curr += rt[processes[idx].pid];
            time_stamp[gantt] = curr;
            vec[gantt] = processes[idx].pid;
            
            rt[processes[idx].pid] = 0;
            count++;

            processes[idx].completion_time = curr;
            
            processes[idx].tat = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].wt = processes[idx].tat - processes[idx].burst_time;
            processes[idx].rt = processes[idx].start_time + processes[idx].arrival_time;

            total_wt += processes[idx].wt;
        	total_tat += processes[idx].tat;
       		total_rt += processes[idx].rt;
       		gantt++;
        }
        
        for (int i = 1; i < size; i++)
        {
            int id=processes[i].pid;
            if (processes[i].arrival_time <= curr && !mark[i] && rt[id] > 0)
            {
                mark[i] = true;
                q.push(i);
            }
        }
        if (rt[processes[idx].pid] > 0)
        {
            q.push(idx);
        }
        if (q.empty())
        {
            for (int i = 1; i < size; i++)
            {
                int id=processes[i].pid;
                if (rt[id] > 0)
                {
                    mark[i] = true;
                    q.push(i);
                }
            }
        }
    }
    
    // Calculate TAT, WT, RT, Total WT, Total TAT, Total RT, and averages
    avg.waiting = total_wt / size;
    avg.turnaround = total_tat / size;
    avg.reaction = total_rt / size;
    
	//to show original position
	for (int i = 0; i < size - 1; i++) 
    {
        for (int j = 0; j < size - i - 1; j++) 
        {
            if (processes[j].pid > processes[j + 1].pid) 
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }
    
    sort(time_stamp.begin(), time_stamp.end() ); //these 2 lines removes all the duplicates from time_stamp
	time_stamp.erase( unique( time_stamp.begin(), time_stamp.end() ), time_stamp.end() );
	
	for (int i = 0; i < gantt; i++)
	{
		if (vec[i] == vec[i+1]) //removes itself if the adjacent PID is the same
		{
			vec.erase(vec.begin()+i);
		}
	}
	
	int zero_count = 0; // counts how many zeroes are present in the updated time_stamp
						// then it deducts itself from gantt so that gantt will only index
						// up until the end of the calculation
	for (int i = 0; i < gantt; i++)
	{
		if (time_stamp[i] == 0)
		{
			zero_count++;
		}
	}
	
	gantt -= zero_count;
    
    table(processes, avg, size, gantt, vec, time_stamp, choice);
}


void table(Process processes[], average avg, int size, int &gantt, vector<int> &vec, vector<int> &time_stamp, char choice)
{
	clear();
    cout << left
         << setw(10) << "PID"
         << setw(10) << "AT"
         << setw(10) << "BT";
         if (choice == 'c' || choice == 'C' || choice == 'f' || choice == 'F')
         {
         	cout << setw(10) << "PL";
		 }
    cout << setw(10) << "ST"
         << setw(10) << "CT"
         << setw(10) << "TAT"
         << setw(10) << "WT"
         << setw(10) << "RT"
         << endl;

    for (int i = 0; i < size; i++)
    {
        // Print process details
        cout << left
             << setw(10) << processes[i].pid
             << setw(10) << processes[i].arrival_time
             << setw(10) << processes[i].burst_time;
             if (choice == 'c' || choice == 'C' || choice == 'f' || choice == 'F')
         	{
         		cout << setw(10) << processes[i].pl;
		 	}
        cout << setw(10) << processes[i].start_time
             << setw(10) << processes[i].completion_time
             << setw(10) << processes[i].tat
             << setw(10) << processes[i].wt
             << setw(10) << processes[i].rt
             << endl;
    }

    cout << "\nAverage Turnaround Time: " << avg.turnaround << endl;
    cout << "Average Waiting Time: " << avg.waiting << endl;
    cout << "Average Response Time: " << avg.reaction << endl;

    gantt_chart(processes, size, gantt, vec, time_stamp);
}

// Gantt chart output
void gantt_chart(Process processes[], int size, int &gantt, vector<int> &vec, vector<int> &time_stamp)
{
	cout << "\nGantt Chart:\n";

	string number[gantt] = {" "};
	string time_str[gantt] = {" "};

	for (int i = 0; i < gantt;i++)
	{
		number[i] = "P" + to_string(vec[i]);
		time_str[i] = to_string(time_stamp[i]);
	}

    // top border
    cout << " ";
    for (int i = 0; i < gantt; i++)
    {
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print dashes on the left side
        {
            cout << "-";
        }

        for (int j = 0; j < number[j].length();j++) //to print dashes in the middle
        {
        	cout << "-";
		}

        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print dashes on the left side
        {
            cout << "-";
        }
        	cout << " ";
    }
    cout << "\n|";

    // process IDs and separator
    for (int i = 0; i < gantt; i++)
    {
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print spaces on the left side
        {
            cout << " ";
        }

        cout << number[i];

        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print spaces on the right side
        {
            cout << " ";
        }
        cout << "|";
    }
    cout << "\n ";

    // bottom border
    for (int i = 0; i < gantt; i++)
    {
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++)
        {
            cout << "-";
        }

        for (int j = 0; j < number[j].length();j++)
        {
        	cout << "-";
		}

        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++)
        {
            cout << "-";
        }
        cout << " ";
    }
    cout << "\n";

	int temp = 0;
    int temp_length = 0;

    // Timeline below the Gantt Chart
    for (int i = 0; i <= gantt; i++)
    {
    	cout << time_stamp[i];
		for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print spaces on the left side
        {
            cout << " ";
        }

        if (time_str[i].length() >= 2) // to adjust for spacing for double-digit numbers
        {
			temp_length = time_str[i].length();
    		temp = time_str[i].length();

			temp = time_str[i].length();
			temp_length--;
			for (int j = 0; j < time_str[j].length();j++)
        	{
        		cout << " ";
			}
			temp_length = temp;
		}

		else
		{
			for (int j = 0; j < number[i].length();j++)
        	{
        		cout << " ";
			}
		}

        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print spaces on the right side
        {
            cout << " ";
        }
    }
    cout << "\n";
}

//gantt chart SPECIFICALLY for vector assigned processes
void gantt_chart_hrrn(vector<Process_HRRN> &processes, int size, int &gantt, vector<int> &vec, vector<int> &time_stamp)
{	
	cout << "\nGantt Chart:\n";
	
	string number[gantt] = {" "};	
	string time_str[gantt] = {" "};
	
	for (int i = 0; i < gantt;i++)
	{
		number[i] = "P" + to_string(vec[i]);
		time_str[i] = to_string(time_stamp[i]);
	}
	
    // top border
    cout << " ";
    for (int i = 0; i < gantt; i++) 
    {
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print dashes on the left side
        {
            cout << "-";
        }
        
        for (int j = 0; j < number[j].length();j++) //to print dashes in the middle
        {
        	cout << "-";
		}
        
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print dashes on the left side
        {
            cout << "-";
        }
        	cout << " ";
    }
    cout << "\n|";

    // process IDs and separator
    for (int i = 0; i < gantt; i++) 
    {
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print spaces on the left side
        {
            cout << " ";
        }
        
        cout << number[i];
        
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print spaces on the right side
        {
            cout << " ";
        }
        cout << "|";
    }
    cout << "\n ";

    // bottom border
    for (int i = 0; i < gantt; i++) 
    {
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) 
        {
            cout << "-";
        }
        
        for (int j = 0; j < number[j].length();j++)
        {
        	cout << "-";
		}
        
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) 
        {
            cout << "-";
        }
        cout << " ";
    }
    cout << "\n";
    
	int temp = 0;
    int temp_length = 0;
    
    // Timeline below the Gantt Chart
    for (int i = 0; i <= gantt; i++) 
    {
    	cout << time_stamp[i];
		for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print spaces on the left side
        {
            cout << " ";
        }
        
        if (time_str[i].length() >= 2) // to adjust for spacing for double-digit numbers
        {
			temp_length = time_str[i].length();
    		temp = time_str[i].length();
			
			temp = time_str[i].length();
			temp_length--;
			for (int j = 0; j < time_str[j].length();j++)
        	{
        		cout << " ";
			}
			temp_length = temp;
		}
		
		else
		{
			for (int j = 0; j < number[i].length();j++)
        	{
        		cout << " ";
			}
		}
        
        for (int j = 0; j < time_stamp[i+1] - time_stamp[i]; j++) //to print spaces on the right side
        {
            cout << " ";
        }
    }
    cout << "\n";
}

void fixedPartition()
{
	int partCount = 0, proCount = 0; //partition count, process count
	int confirm = 0;
	
	cout << "Welcome to the Fixed Partition algorithm!" << endl << endl;

	do
	{
    	cout << "Enter the number of Partitions: ";
    	cin >> partCount;

    	if (cin.fail())
			{
				cout << "\nMisinput!\n\n";
    			cin.clear();
    			cin.ignore();
			}
		else
		{
			cout << endl;
			confirm = 1;
		}
	} while (confirm == 0);
	
	vector<int> partition_size(partCount);
	
	for (int i = 0; i < partCount; i++)
	{
		do
		{
    		cout << "Enter the Partition #" << i+1 << " size: ";
    		cin >> partition_size[i];

    		if (cin.fail())
				{
					cout << "\nMisinput!\n\n";
    				cin.clear();
    				cin.ignore();
				}
			else
			{
				confirm = 1;
			}
		} while (confirm == 0);
	}
	
	clear();
	cout << "Partition sizes(kb): ";
	for (int i = 0; i < partition_size.size(); i++)
	{
		cout << partition_size[i] << "kb ";
	}
	cout << endl << endl;
	do
	{
    	cout << "Enter the number of Processes: ";
    	cin >> proCount;

    	if (cin.fail())
			{
				cout << "\nMisinput!\n\n";
    			cin.clear();
    			cin.ignore();
			}
		else
		{
			cout << endl;
			confirm = 1;
		}
	} while (confirm == 0);
	
	
	vector<int> best_fit(proCount);
	vector<int> worst_fit(proCount);
	vector<int> next_fit(proCount);
	vector<int> first_fit(proCount);
	vector<int> process_pool(proCount);
	int temp = 0;
	
	
	for (int i = 0; i < proCount; i++)
	{
		do
		{
    		cout << "Enter the Partition #" << i+1 << " size: ";
    		cin >> temp;

    		if (cin.fail())
				{
					cout << "\nMisinput!\n\n";
    				cin.clear();
    				cin.ignore();
				}
			else
			{
				process_pool[i] = temp;
				confirm = 1;
			}
		} while (confirm == 0);
	}
	memory_allocation(proCount, partCount, first_fit, best_fit, worst_fit, next_fit, partition_size, process_pool);
}

void memory_allocation(int size, int size2, vector<int> &first_fit, vector<int> &best_fit, vector<int> &worst_fit, vector<int> &next_fit, vector<int> &partition_size, vector<int> &process_pool)
{
	vector<int> int_frag(size);
	vector<int> waiting_FF(size);
	vector<int> waiting_BF(size);
	vector<int> waiting_WF(size);
	vector<int> waiting_NF(size);
	vector<bool> used_FF(size2, false);
	
	FF(int_frag, first_fit, partition_size, waiting_FF, process_pool);
	BF(int_frag, best_fit, partition_size, waiting_BF, process_pool);
    WF(int_frag, worst_fit, partition_size, waiting_WF, process_pool);
	NF(int_frag, next_fit, partition_size, waiting_NF, process_pool);
    
	temp_table(first_fit,best_fit,worst_fit,next_fit,waiting_FF,waiting_BF,
				waiting_WF,waiting_NF, process_pool, partition_size, int_frag);
}

void temp_table(vector<int> &first_fit,vector<int> &best_fit,vector<int> &worst_fit,vector<int> &next_fit,
			vector<int> &waiting_FF,vector<int> &waiting_BF,vector<int> &waiting_WF,vector<int> &waiting_NF
			,vector<int> &process_pool, vector<int> &partition_size, vector<int> &int_frag)
{
	clear();
	cout << "\nTempory Table: ";
	cout << "\nOS(20KB)\tFirst Fit\tBest Fit\tWorst Fit\tNext Fit" << endl;
	for (int i = 0; i < partition_size.size(); i++)
	{
		
		cout << "Job" << i+1 << ": " << partition_size[i] << "(kb)\t";
		cout << first_fit[i] << "(kb)\t\t";
		cout << best_fit[i] << "(kb)\t\t";
		cout << worst_fit[i] << "(kb)\t\t";
		cout << next_fit[i] << "(kb)";
		cout << endl;
	}
	
	cout << "\nWaiting time: \n";
	for (int i = 0; i < process_pool.size(); i++)
	{
		cout << "\t\t";
		
		if (i < waiting_FF.size())
		{
			cout << waiting_FF[i] << "(kb)\t\t";
		}
		
		else if (i > waiting_FF.size())
		{
			cout << "\t\t";
		}
		
		if (i < waiting_BF.size())
		{
			cout << waiting_BF[i] << "(kb)\t\t";
		}
		
		else if (i > waiting_BF.size())
		{
			cout << "\t\t";
		}
		
		if (i < waiting_WF.size())
		{
			cout << waiting_WF[i] << "(kb)\t\t";
		}
		
		else if (i > waiting_WF.size())
		{
			cout << "\t\t";
		}
		
		if (i < waiting_NF.size())
		{
			cout << waiting_NF[i] << "(kb)\t\t";
		}
		
		else if (i > waiting_NF.size())
		{
			cout << "\t\t";
		}
		cout << endl;
	}
	
	memory_deallocation(first_fit,best_fit,worst_fit,next_fit,waiting_FF,waiting_BF,
			waiting_WF,waiting_NF, process_pool, partition_size, int_frag);
}

void final_table(vector<int> &first_fit,vector<int> &best_fit,vector<int> &worst_fit,vector<int> &next_fit,
			vector<int> &waiting_FF,vector<int> &waiting_BF,vector<int> &waiting_WF,vector<int> &waiting_NF
			,vector<int> &process_pool, vector<int> &partition_size, vector<int> &int_frag)
{
	vector<float> frag_FF(partition_size.size()); //stores internal fragmentaion per index
	vector<float> frag_BF(partition_size.size());
	vector<float> frag_WF(partition_size.size());
	vector<float> frag_NF(partition_size.size());
	vector<float> total_frag(4);//1 - FF, 2 - BF, 3 - WF, 4 - NF. Stores total frag per index
	vector<float> ave_frag(4);
	vector<float> MU_FF(partition_size.size()); //Memomry Utilization
	vector<float> MU_BF(partition_size.size());
	vector<float> MU_WF(partition_size.size());
	vector<float> MU_NF(partition_size.size());
	vector<float> total_MU(4);
	vector<float> ave_MU(4);
	vector <int> zero_count(4);//stores how many empty spaces per algorithm
	
	vector<float> partition_temp(partition_size.size());
	
	for (int i = 0; i < partition_temp.size();i++) //Convert partition_size to float to allow calculations
	{
		partition_temp[i] = partition_size[i];
	}
	
	
	//First Fit
	for (int i = 0; i < partition_temp.size();i++) //ex: partition_size = 5
	{
		if (first_fit[i] <= 0 || partition_temp[i] - first_fit[i] == 0)
		{
			zero_count[0] += 1;
			continue;
		}
		frag_FF[i] = partition_temp[i] - first_fit[i];
	}
	
	//Best Fit
	for (int i = 0; i < partition_temp.size();i++) //ex: partition_size = 5
	{
		if (best_fit[i] <= 0 || partition_temp[i] - best_fit[i] == 0)
		{
			zero_count[1] += 1;
			continue;
		}
		frag_BF[i] = partition_temp[i] - best_fit[i];
	}
	
	//Worst Fit
	for (int i = 0; i < partition_temp.size();i++) //ex: partition_size = 5
	{
		if (worst_fit[i] <= 0 || partition_temp[i] - worst_fit[i] == 0)
		{
			zero_count[2] += 1;
			continue;
		}
		frag_WF[i] = partition_temp[i] - worst_fit[i];
	}
	
	//Next Fit
	for (int i = 0; i < partition_temp.size();i++) //ex: partition_size = 5
	{	
		if (next_fit[i] <= 0 || partition_temp[i] - next_fit[i] == 0)
		{
			zero_count[3] += 1;
			continue;
		}
		frag_NF[i] = partition_temp[i] - next_fit[i];
	}
	
	
	for (int i = 0; i < partition_temp.size();i++)
	{
		total_frag[0] += frag_FF[i];
		total_frag[1] += frag_BF[i];
		total_frag[2] += frag_WF[i];
		total_frag[3] += frag_NF[i];
	}
	
		ave_frag[0] = total_frag[0]/(partition_size.size()-zero_count[0]);
		ave_frag[1] = total_frag[1]/(partition_size.size()-zero_count[1]);
		ave_frag[2] = total_frag[2]/(partition_size.size()-zero_count[2]);
		ave_frag[3] = total_frag[3]/(partition_size.size()-zero_count[3]);
	
	//Getting the Memory Utilization for every job/process
	//First Fit
	for (int i = 0; i < partition_temp.size();i++) //ex: partition_size = 5
	{
		if (first_fit[i] == 0)
		{
			MU_FF[i] = 0;
			continue;
		}
		MU_FF[i] = (first_fit[i]/partition_temp[i]) * 100;
		total_MU[0] += MU_FF[i];
	}
	
	//Best Fit
	for (int i = 0; i < partition_temp.size();i++) //ex: partition_size = 5
	{
		if (best_fit[i] <= 0)
		{
			MU_BF[i] = 0;
			continue;
		}
		MU_BF[i] = (best_fit[i]/partition_temp[i]) * 100;
		total_MU[1] += MU_BF[i];
	}
	
	//Worst Fit
	for (int i = 0; i < partition_temp.size();i++) //ex: partition_size = 5
	{
		if (worst_fit[i] <= 0)
		{
			MU_WF[i] = 0;
			continue;
		}
		MU_WF[i] = (worst_fit[i]/partition_temp[i]) * 100;
		total_MU[2] += MU_WF[i];
	}
	
	//Next Fit
	for (int i = 0; i < partition_temp.size();i++) //ex: partition_size = 5
	{	
		if (next_fit[i] <= 0)
		{
			MU_NF[i] = 0;
			continue;
		}
		MU_NF[i] = (next_fit[i]/partition_temp[i]) * 100;
		total_MU[3] += MU_NF[i];
	}
	
	ave_MU[0] = total_MU[0]/partition_temp.size();
	ave_MU[1] = total_MU[1]/partition_temp.size();
	ave_MU[2] = total_MU[2]/partition_temp.size();
	ave_MU[3] = total_MU[3]/partition_temp.size();
	
	clear();
	cout << "\nFinal Table: ";
	cout << "\nOS(20KB)\tFirst Fit\tBest Fit\tWorst Fit\tNext Fit" << endl;
	for (int i = 0; i < partition_size.size(); i++)
	{
		
		cout << "FS" << i+1 << ": " << partition_size[i] << "(kb)\t";
		cout << first_fit[i] << "(kb)\t\t";
		cout << best_fit[i] << "(kb)\t\t";
		cout << worst_fit[i] << "(kb)\t\t";
		cout << next_fit[i] << "(kb)";
		cout << endl;
	}
	
	cout << "\nWaiting time: \n";
	for (int i = 0; i < process_pool.size(); i++)
	{
		cout << "\t\t";
		
		if (i < waiting_FF.size())
		{
			cout << waiting_FF[i] << "(kb)\t\t";
		}
		
		else if (i > waiting_FF.size())
		{
			cout << "\t\t";
		}
		
		if (i < waiting_BF.size())
		{
			cout << waiting_BF[i] << "(kb)\t\t";
		}
		
		else if (i > waiting_BF.size())
		{
			cout << "\t\t";
		}
		
		if (i < waiting_WF.size())
		{
			cout << waiting_WF[i] << "(kb)\t\t";
		}
		
		else if (i > waiting_WF.size())
		{
			cout << "\t\t";
		}
		
		if (i < waiting_NF.size())
		{
			cout << waiting_NF[i] << "(kb)\t\t";
		}
		
		else if (i > waiting_NF.size())
		{
			cout << "\t\t";
		}
		cout << endl;
	}
	
	cout << "\nTotal Internal Fragmentation: " << endl;
	cout << "First Fit: ";
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << frag_FF[i] << "kb";
		if (i == partition_size.size()-1)
		{
			continue;
		}
		cout << " + ";
	}
	cout << " = " << total_frag[0];
	
	cout << "\nBest Fit: ";
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << frag_BF[i] << "kb";
		if (i == partition_size.size()-1)
		{
			continue;
		}
		cout << " + ";
	}
	cout << " = " << total_frag[1];
	
	cout << "\nWorst Fit: ";
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << frag_WF[i] << "kb";
		if (i == partition_size.size()-1)
		{
			continue;
		}
		cout << " + ";
	}
	cout << " = " << total_frag[2];
	
	cout << "\nNext Fit: ";
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << frag_NF[i] << "kb";
		if (i == partition_size.size()-1)
		{
			continue;
		}
		cout << " + ";
	}
	cout << " = " << total_frag[3];
	
	cout << "\n\nAverage Internal Fragmentation: " << endl;
	cout << "First Fit: " << total_frag[0] << "/" << partition_size.size()-zero_count[0] << " = " << ave_frag[0];
	cout << "\nBest Fit: " << total_frag[1] << "/" << partition_size.size()-zero_count[1] << " = " << ave_frag[1];
	cout << "\nWorst Fit: " << total_frag[2] << "/" << partition_size.size()-zero_count[2] << " = " << ave_frag[2];
	cout << "\nNext Fit: " << total_frag[3] << "/" << partition_size.size()-zero_count[3] << " = " << ave_frag[3];
	
	cout << "\n\nMemory Utilization: ";
	cout << "\nFirst Fit: " << endl;
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << "Partition " << i+1 << ": (" << first_fit[i] << "/" << partition_temp[i] << ") x 100 = " << MU_FF[i] << "%" << endl;
	}
	
	cout << "\nBest Fit: " << endl;
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << "Partition " << i+1 << ": (" << best_fit[i] << "/" << partition_temp[i] << ") x 100 = " << MU_BF[i] << "%" << endl;
	}
	
	cout << "\nWorst Fit: " << endl;
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << "Partition " << i+1 << ": (" << worst_fit[i] << "/" << partition_temp[i] << ") x 100 = " << MU_WF[i] << "%" << endl;
	}
	
	cout << "\nNext Fit: " << endl;
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << "Partition " << i+1 << ": (" << next_fit[i] << "/" << partition_temp[i] << ") x 100 = " << MU_NF[i] << "%" << endl;
	}
	
	cout << "\nAverage Memory Utilization: ";
	cout << "\nFirst Fit: " << endl;
	cout << "(";
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << MU_FF[i] << "%";
		if (i == partition_size.size()-1)
		{
			continue;
		}
		cout << " + ";
	}
	cout << ") / " << partition_size.size()  << " = "<< ave_MU[0] << "%";
	
	cout << "\nBest Fit: " << endl;
	cout << "(";
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << MU_BF[i] << "%";
		if (i == partition_size.size()-1)
		{
			continue;
		}
		cout << " + ";
	}
	cout << ") / " << partition_size.size()  << " = "<< ave_MU[1] << "%";
	
	cout << "\nWorst Fit: " << endl;
	cout << "(";
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << MU_WF[i] << "%";
		if (i == partition_size.size()-1)
		{
			continue;
		}
		cout << " + ";
	}
	cout << ") / " << partition_size.size()  << " = "<< ave_MU[2] << "%";
	
	cout << "\nNext Fit: " << endl;
	cout << "(";
	for (int i = 0; i < partition_size.size();i++)
	{
		cout << MU_NF[i] << "%";
		if (i == partition_size.size()-1)
		{
			continue;
		}
		cout << " + ";
	}
	cout << ") / " << partition_size.size()  << " = "<< ave_MU[3] << "%";
	cout << endl << endl << "Thank You for Using!";
	
}

void memory_deallocation(vector<int> &first_fit,vector<int> &best_fit,vector<int> &worst_fit,vector<int> &next_fit,
						vector<int> &waiting_FF,vector<int> &waiting_BF,vector<int> &waiting_WF,vector<int> &waiting_NF
						,vector<int> &process_pool, vector<int> &partition_size, vector<int> &int_frag)
{
	char choice = ' ';
	char choice2 = ' ';
	int askProcess = 0;
	int validation = 0, process_num = 0;
	int confirm = 0;
	
	do
	{
		cout << "\nDeallocate?[y/n]: ";
		cin >> choice;
		
		if (choice == 'n' || choice == 'N')
		{
			confirm = 0;
			break;
		}
		
		else if (choice == 'y' || choice == 'Y')
		{
			do
			{
				cout << "a) First Fit\nb) Best Fit\nc) Worst Fit\nd) Next Fit";
				cout << "\n\nWhich Algorithm?: ";
				cin >> choice2;
				switch(choice2)
				{
					case 'a':
					case 'A': //First Fit
						do
						{
    						cout << "How many process/es?: ";
    						cin >> askProcess;

    						if (cin.fail() || askProcess > partition_size.size() || askProcess < 0 || askProcess == 0)
							{
								cout << "\nMisinput!\n\n";
    							cin.clear();
    							cin.ignore();
							}
							else
							{
								confirm = 1;
							}
						} while (confirm == 0);
						confirm = 0;
						for (int i = 0; i < askProcess; i++)
						{
							do
							{
    							cout << "Which process/es?: ";
    							cin >> process_num;

    							if (cin.fail() || askProcess > partition_size.size() || askProcess < 0 || askProcess == 0)
								{
									cout << "\nMisinput!\n\n";
    								cin.clear();
    								cin.ignore();
								}
								else
								{
									process_num -= 1;
									first_fit[process_num] = 0;
									confirm = 1;
								}
							} while (confirm == 0);
						}
						
						deallocation_FF(int_frag, first_fit, partition_size, waiting_FF, process_pool);
						cout << "\nSuccess!\n";
						pause();
						validation = 1;
						temp_table(first_fit,best_fit,worst_fit,next_fit,waiting_FF,waiting_BF,
								waiting_WF,waiting_NF, process_pool, partition_size, int_frag);
						break;
					case 'b':
					case 'B': //Best Fit
						do
						{
    						cout << "How many process/es?: ";
    						cin >> askProcess;

    						if (cin.fail() || askProcess > partition_size.size() || askProcess < 0 || askProcess == 0)
							{
								cout << "\nMisinput!\n\n";
    							cin.clear();
    							cin.ignore();
							}
							else
							{
								confirm = 1;
							}
						} while (confirm == 0);
						confirm = 0;
						for (int i = 0; i < askProcess; i++)
						{
							do
							{
    							cout << "Which process/es?: ";
    							cin >> process_num;

    							if (cin.fail() || askProcess > partition_size.size() || askProcess < 0 || askProcess == 0)
								{
									cout << "\nMisinput!\n\n";
    								cin.clear();
    								cin.ignore();
								}
								else
								{
									process_num -= 1;
									best_fit[process_num] = 0;
									confirm = 1;
								}
							} while (confirm == 0);
						}
						
						deallocation_BF(int_frag, best_fit, partition_size, waiting_BF, process_pool);
						cout << "\nSuccess!\n";
						pause();
						validation = 1;
						temp_table(first_fit,best_fit,worst_fit,next_fit,waiting_FF,waiting_BF,
								waiting_WF,waiting_NF, process_pool, partition_size, int_frag);
						break;
					case 'c':
					case 'C': //Worst Fit
						do
						{
    						cout << "How many process/es?: ";
    						cin >> askProcess;

    						if (cin.fail() || askProcess > partition_size.size() || askProcess < 0 || askProcess == 0)
							{
								cout << "\nMisinput!\n\n";
    							cin.clear();
    							cin.ignore();
							}
							else
							{
								confirm = 1;
							}
						} while (confirm == 0);
						confirm = 0;
						for (int i = 0; i < askProcess; i++)
						{
							do
							{
    							cout << "Which process/es?: ";
    							cin >> process_num;

    							if (cin.fail() || askProcess > partition_size.size() || askProcess < 0 || askProcess == 0)
								{
									cout << "\nMisinput!\n\n";
    								cin.clear();
    								cin.ignore();
								}
								else
								{
									process_num -= 1;
									worst_fit[process_num] = 0;
									confirm = 1;
								}
							} while (confirm == 0);
						}
						
						deallocation_WF(int_frag, worst_fit, partition_size, waiting_WF, process_pool);
						cout << "\nSuccess!\n";
						pause();
						validation = 1;
						temp_table(first_fit,best_fit,worst_fit,next_fit,waiting_FF,waiting_BF,
								waiting_WF,waiting_NF, process_pool, partition_size, int_frag);
						break;
					case 'd':
					case 'D'://Next Fit
						do
						{
    						cout << "How many process/es?: ";
    						cin >> askProcess;

    						if (cin.fail() || askProcess > partition_size.size() || askProcess < 0 || askProcess == 0)
							{
								cout << "\nMisinput!\n\n";
    							cin.clear();
    							cin.ignore();
							}
							else
							{
								confirm = 1;
							}
						} while (confirm == 0);
						confirm = 0;
						for (int i = 0; i < askProcess; i++)
						{
							do
							{
    							cout << "Which process/es?: ";
    							cin >> process_num;

    							if (cin.fail() || askProcess > partition_size.size() || askProcess < 0 || askProcess == 0)
								{
									cout << "\nMisinput!\n\n";
    								cin.clear();
    								cin.ignore();
								}
								else
								{
									process_num -= 1;
									next_fit[process_num] = 0;
									confirm = 1;
								}
							} while (confirm == 0);
						}
						
						deallocation_NF(int_frag, next_fit, partition_size, waiting_NF, process_pool);
						cout << "\nSuccess!\n";
						pause();
						validation = 1;
						temp_table(first_fit,best_fit,worst_fit,next_fit,waiting_FF,waiting_BF,
								waiting_WF,waiting_NF, process_pool, partition_size, int_frag);
						break;			
					
					default: 
					cout << "\nMisinput!\n\n";
					cin.clear();
    				cin.ignore();
				}
			} while (validation < 1);
		}
		
		else
		{
			cout << "\nMisinput!\n";
		}
	} while (confirm < 1);
	
	final_table(first_fit,best_fit,worst_fit,next_fit,waiting_FF,waiting_BF,
				waiting_WF,waiting_NF, process_pool, partition_size, int_frag);
}

void FF(vector<int> &frag, vector<int> &first_fit, vector<int> &partition_size, vector<int> &waiting, vector<int> &process_pool)
{
	for (int i = 0; i < process_pool.size(); i++)
	{
		int notEqual = 0;
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (process_pool[i] <= partition_size[j] && first_fit[j] == 0) // conditioned if process size fits inside partition size and if there is an empty slot.
			{
				first_fit[j] = process_pool[i];
				break;
			}
			else if (process_pool[i] > partition_size[j] || first_fit[j] != 0) // notEqual + 1 everytime the process size doesn't fit
			{
				notEqual++;
			}
		}
		
		for (int j = 0; j < waiting.size(); j++)
		{
			if (notEqual == partition_size.size() && waiting[j]==0) //then if the notEqual reaches the same size as the amount 
			{														//of partitions. Placae in the waiting pool
				waiting[j] = process_pool[i];
				break;
			}
		}
	}
}

void deallocation_FF(vector<int> &frag, vector<int> &first_fit, vector<int> &partition_size, vector<int> &waiting, vector<int> &process_pool)
{
	for (int i = 0; i < waiting.size(); i++)
	{
		int notEqual = 0;
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (waiting[i] <= partition_size[j] && first_fit[j] == 0) // conditioned if process size fits inside partition size and if there is an empty slot.
			{
				first_fit[j] = waiting[i];
				waiting.erase(waiting.begin()+i);
				break;
			}
			else if (process_pool[i] > partition_size[j] || first_fit[j] != 0) // notEqual + 1 everytime the process size doesn't fit
			{
				notEqual++;
			}
		}
		
		for (int j = 0; j < waiting.size(); j++)
		{
			if (notEqual == partition_size.size() && waiting[j]==0) //then if the notEqual reaches the same size as the amount 
			{														//of partitions. Placae in the waiting pool
				waiting.erase(waiting.begin()+j);
				break;
			}
		}
	}
}

void BF(vector<int> &frag, vector<int> &best_fit, vector<int> &partition_size, vector<int> &waiting, vector<int> &process_pool)
{
	int int_frag[partition_size.size()] = {};//internal fragmentation
	int lowest = 0;
	for (int i = 0; i < process_pool.size(); i++)
	{
		for (int i = 0; i < partition_size.size(); i++) // undo lowest
		{
			int_frag[i] = -1; //initialize as -1 to allow 0
		}
		
		int notEqual = 0;
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (process_pool[i] <= partition_size[j] && best_fit[j] == 0) //finding which process has the least internal fragmentation
			{
				int_frag[j] = partition_size[j] - process_pool[i];
				lowest = j; //lowest = the index of j
				
				for (int a = 0; a < partition_size.size(); a++) // finding lowest
				{
					if (int_frag[a] < int_frag[lowest] && int_frag[a] != -1)
					{
						lowest = a;
					}
				}
			}
			
			else if (process_pool[i] > partition_size[j] || best_fit[j] != 0)
			{
				notEqual++;
			}
		}
		
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (process_pool[i] <= partition_size[j] && best_fit[j] == 0)
                {
                    best_fit[lowest] = process_pool[i];
                }
		}
		
		for (int j = 0; j < waiting.size(); j++)
		{
			if (notEqual == partition_size.size() && waiting[j]==0)
			{
				waiting[j] = process_pool[i];
				break;
			}
		}
	}
}

void deallocation_BF(vector<int> &frag, vector<int> &best_fit, vector<int> &partition_size, vector<int> &waiting, vector<int> &process_pool)
{
	int int_frag[partition_size.size()] = {};//internal fragmentation
	int lowest = 0;
	for (int i = 0; i < waiting.size(); i++)
	{
		for (int i = 0; i < partition_size.size(); i++) // undo lowest
		{	
			int_frag[i] = -1; //initialize as -1 to allow 0
		}
		
		int notEqual = 0;
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (waiting[i] <= partition_size[j] && best_fit[j] == 0) //finding which process has the least internal fragmentation
			{
				int_frag[j] = partition_size[j] - waiting[i];
				lowest = j; //lowest = the index of j
				
				for (int a = 0; a < partition_size.size(); a++) // finding lowest
				{
					if (int_frag[a] < int_frag[lowest] && int_frag[a] != -1)
					{
						lowest = a;
					}
				}
			}
			
			else if (waiting[i] > partition_size[j] || best_fit[j] != 0)
			{
				notEqual++;
			}
		}
		
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (waiting[i] <= partition_size[j] && best_fit[j] == 0)
                {
                    best_fit[lowest] = waiting[i];    
					waiting.erase(waiting.begin()+i);
                }
		}
		
		for (int j = 0; j < waiting.size(); j++)
		{
			if (notEqual == partition_size.size() && waiting[j]==0)
			{
				waiting.erase(waiting.begin()+j);
				break;
			}
		}
	}
}

void WF(vector<int> &frag ,vector<int> &worst_fit, vector<int> &partition_size, vector<int> &waiting, vector<int> &process_pool)
{
	int int_frag[partition_size.size()] = {};//internal fragmentation
	int highest = 0;
	for (int i = 0; i < process_pool.size(); i++)
	{
		for (int i = 0; i < partition_size.size(); i++) // undo lowest
		{
			int_frag[i] = -1; //initialize as -1 to allow 0
		}
		
		int notEqual = 0;
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (process_pool[i] <= partition_size[j] && worst_fit[j] == 0) //finding which process has the least internal fragmentation
			{
				int_frag[j] = partition_size[j] - process_pool[i];
				highest = j; //highest = the index of j
				for (int a = 0; a < partition_size.size(); a++) // finding lowest
				{
					if (int_frag[a] > int_frag[highest] && int_frag[a] != -1)
					{
						highest = a;		
					}
				}
			}
			
			else if (process_pool[i] > partition_size[j] || worst_fit[j] != 0)
			{
				notEqual++;
			}
		}
		
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (process_pool[i] <= partition_size[j] && worst_fit[j] == 0)
                {
                    worst_fit[highest] = process_pool[i];
                }
		}
		
		for (int j = 0; j < waiting.size(); j++)
		{
			if (notEqual == partition_size.size() && waiting[j]==0)
			{
				waiting[j] = process_pool[i];
				break;
			}
		}
	}
}

void deallocation_WF(vector<int> &frag ,vector<int> &worst_fit, vector<int> &partition_size, vector<int> &waiting, vector<int> &process_pool)
{
	
	
	int int_frag[partition_size.size()] = {};//internal fragmentation
	int highest = 0;
	for (int i = 0; i < waiting.size(); i++)
	{
		for (int i = 0; i < partition_size.size(); i++) // undo lowest
		{
			int_frag[i] = -1; //initialize as -1 to allow 0
		}
		
		int notEqual = 0;
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (waiting[i] <= partition_size[j] && worst_fit[j] == 0) //finding which process has the least internal fragmentation
			{
				int_frag[j] = partition_size[j] - waiting[i];
				highest = j; //highest = the index of j
				for (int a = 0; a < partition_size.size(); a++) // finding lowest
				{
					if (int_frag[a] > int_frag[highest] && int_frag[a] != -1)
					{
						highest = a;		
					}
				}
			}
			
			else if (waiting[i] > partition_size[j] || worst_fit[j] != 0)
			{
				notEqual++;
			}
		}
		
		for (int j = 0; j < partition_size.size(); j++)
		{
			if (waiting[i] <= partition_size[j] && worst_fit[j] == 0)
                {
                    worst_fit[highest] = waiting[i];
                    waiting.erase(waiting.begin()+i);
                }
		}
		
		for (int j = 0; j < waiting.size(); j++)
		{
			if (notEqual == partition_size.size() && waiting[j]==0)
			{
				waiting.erase(waiting.begin()+j);
				break;
			}
		}
	}
}



void NF(vector<int> &frag, vector<int> &next_fit, vector<int> &partition_size, vector<int> &waiting, vector<int> &process_pool)
{
    int curr = 0; // Current index

	for (int i = 0; i < process_pool.size(); i++) 
	{
    	int notEqual = 0;
    	int start = curr;

    	for (int j = 0; j < partition_size.size(); j++) 
		{
    	    int index = (start + j) % partition_size.size(); // Circular traversal

    	    if (process_pool[i] <= partition_size[index] && next_fit[index] == 0) 
			{
    	        next_fit[index] = process_pool[i];
    	        curr = (index + 1) % partition_size.size(); // Move to next partition for next allocation
    	        break;
    	    } 
			else 
			{
        	    notEqual++;
        	}
    	}

    	// If notEqual reaches partition_size.size(), it means no partition could accommodate the process
    
		if (notEqual == partition_size.size()) 
		{
        	for (int j = 0; j < waiting.size(); j++) 
			{
            	if (waiting[j] == 0) 
				{
            	    waiting[j] = process_pool[i];
            	    break;
            	}
        	}
    	}
	}
}

void deallocation_NF(vector<int> &frag, vector<int> &next_fit, vector<int> &partition_size, vector<int> &waiting, vector<int> &process_pool)
{
	int curr = 0; // Current index

	for (int i = 0; i < waiting.size(); i++) 
	{
    	int notEqual = 0;
    	int start = curr;

    	for (int j = 0; j < partition_size.size(); j++) 
		{
    	    int index = (start + j) % partition_size.size(); // Circular traversal

    	    if (waiting[i] <= partition_size[index] && next_fit[index] == 0) 
			{
    	        next_fit[index] = waiting[i];
    	        waiting.erase(waiting.begin()+i);
    	        curr = (index + 1) % partition_size.size(); // Move to next partition for next allocation
    	        break;
    	    } 
			else 
			{
        	    notEqual++;
        	}
    	}

    	// If notEqual reaches partition_size.size(), it means no partition could accommodate the process
    
		if (notEqual == partition_size.size()) 
		{
        	for (int j = 0; j < waiting.size(); j++) 
			{
            	if (waiting[j] == 0) 
				{
            	    waiting.erase(waiting.begin()+j);
            	    break;
            	}
        	}
    	}
	}
}

void choiceDiscSched()
{
	int val = 0;
	char choice = ' ';
	int processCount = 0;

	do
	{
		cout << "Please choose a Disc scheduling algorithm ;)";
		cout << "\n\na) First Come, First Serve (FCFS)" << endl;
		cout << "b) Shortest Seek Time First (SSTF)" << endl;
		cout << "c) Scan" << endl;
		cout << "d) C-Scan" << endl;
		cout << "e) Look" << endl;
		cout << "f) C-Look" << endl;
		cout << "\n\nenter X to return to the main menu." << endl;

		do
		{
			cout << "\nPlease Choose: ";
			cin >> choice;

			switch (choice)
			{
				case 'a':
				case 'A': discSchedulingInput(choice);
				val = 1;
					break;

				case 'b':
				case 'B': discSchedulingInput(choice);
				val = 1;
					break;

				case 'c':
				case 'C': discSchedulingInput(choice);
				val = 1;
					break;

				case 'd':
				case 'D': discSchedulingInput(choice);
				val = 1;
					break;

				case 'e':
				case 'E': discSchedulingInput(choice);
				val = 1;
					break;

				case 'f':
				case 'F': discSchedulingInput(choice);
				val = 1;
					break;

				case 'x':
				case 'X': cout << endl;
				clear();
				main();
					break;

				default:
				cout << "\nMisinput!\n\n";
				pause();
				clear();
				choiceDiscSched();
			}
		} while(val < 1);
	} while (val < 1);
}

void discSchedulingInput(char choice)
{
	cout << endl;
	pause();
	clear();
	Computations comp;

    while(true)
    {
       cout << "Disk request size: ";
       cin >> comp.size; //Disk Request count, 1 value
       if (cin.fail())
       {
            cout << "\nMisinput!\n\n";
		    cin.clear();
		    cin.ignore();
       }
       else
       break;
    }
   
   while(true)
    {
       cout << "Direction of the head pointer (right or left): ";
       cin >> comp.direction; //Direction, 1 value
       transform(comp.direction.begin(), comp.direction.end(), comp.direction.begin(),::tolower); //tolower
       if(comp.direction == "left" || comp.direction == "right")
       {
           break;
       }
       else if (cin.fail() || comp.direction != "left" || comp.direction != "right")
       {
            cout << "\nMisinput!\n" << endl;
		    cin.clear();
		    cin.ignore();
       }
    }
       
    while(true)
    {
        cout << "Enter the disk size (max track number): ";
        cin >> comp.disk_size;// Disk Size, 1 value 
            
        if(cin.fail())
        {
            cout << "\nMisinput!\n\n";
    		cin.clear();
    		cin.ignore();
        }

        else
        break;
    }
   
   while(true)
    {
       cout << "Head pointer starting number: ";
       cin >> comp.head; //Head, 1 value
       
       if (cin.fail())
       {
            cout << "\nMisinput!\n\n";
		    cin.clear();
		    cin.ignore();
       }
       else
       break;
    }
    vector<Disk> disk_req(comp.size);

    cout << "Disk requests:\n";

    for (int i = 0; i < comp.size; i++)
    {        while(true)
        {
            cout << i+1 << ". ";
            cin >> disk_req[i].req; //Requests, multiple values

            if(cin.fail())
            {
                cout << "\nMisinput!\n\n";
    		    cin.clear();
    		    cin.ignore();
            }

            else if (disk_req[i].req > comp.disk_size || disk_req[i].req < 0)
            {
                cout << "\nInvalid input!\nPlease Enter a number between 0 and " << comp.disk_size << endl << endl;
                cin.clear();
                cin.ignore();
            }

            else
            break;
        }
    }

    clear();
	
    cout << "\nDisk requests: ";
    for (int i = 0; i < comp.size; i++)
    {
        cout << disk_req[i].req;
        if (i < comp.size - 1) cout << ", ";
    }
    
	int head = comp.head; //starter head
	int diskSize = comp.size; //Request count
	string direction = comp.direction; //Direction, left or right
	vector<int> requests(diskSize);	//A copy for 
	
	for (int i = 0; i < diskSize;i++) //A fucntion to copy values from disk_req[i].req to requests for other algorithms
	{
		requests[i] = disk_req[i].req;
	}    
	
    switch (choice)
    {
    	case 'a':
    	case 'A': FCFS(requests, head, direction, diskSize);
    		break;
    		
    	case 'b':
		case 'B': SSTF(requests, head, direction, diskSize);
			break;
			
		case 'c':
		case 'C': SCAN(disk_req, comp);
			break;

		case 'd':
		case 'D': CSCAN(disk_req, comp);
			break;

		case 'e':
		case 'E': LOOK(requests, head, direction, diskSize);
			break;

		case 'f':
		case 'F': CLOOK(requests, head, direction, diskSize);
			break;

		default:
		cout << "\nMisinput!\n\n";
		pause();
		clear();		
	}
    
}

void FCFS(vector<int> requests, int head, string direction, int diskSize) 
{
    int seek_count = 0;
    int distance, cur_track;
    vector<int> seekSequence(diskSize);

    cout << "\n\nSeek Sequence: ";
    
    for (int i = 0; i < diskSize; i++) 
	{
        cur_track = requests[i];

        // Calculate absolute distance
        distance = abs(cur_track - head);

        // Accumulate seek operations
        seek_count += distance;

        // Move head to the new track
        head = cur_track;
        seekSequence[i] = cur_track;

        cout << seekSequence[i] << " ";
    }
    cout << endl;

    cout << "Total number of seek operations = " << seek_count << endl;
    head = seekSequence[0];
    graph(requests, head, seekSequence);
}

void SSTF(vector<int> &requests, int head, string direction, int diskSize) 
{
    int head_copy = head;
	if (requests.empty()) return;

    int seekcount = 0;
    vector<int> seeksequence; 
    vector<bool> visited(requests.size(), false); // Track visited requests

    for (int i = 0; i < requests.size(); i++) {
        seeksequence.push_back(head); // Store the head before moving

        // Find the nearest unvisited track
        int index = -1, minimum = INT_MAX;
        for (int j = 0; j < requests.size(); j++) {
            if (!visited[j]) {
                int diff = abs(head - requests[j]);
                if (diff < minimum) {
                    minimum = diff;
                    index = j;
                }
            }
        }

        // Move to the nearest track
        if (index != -1) {
            visited[index] = true;
            seekcount += minimum;
            head = requests[index]; // Update head
        }
    }

    seeksequence.push_back(head); // Store the final head position

    // Output results
    cout << "\nTotal number of seek operations = " << seekcount << endl;
    cout << "Seek sequence: ";
    for (int i : seeksequence) cout << i << " ";
    cout << endl;
    
    graph(requests, head_copy, seeksequence);
}

void SCAN(vector<Disk>& disk_req, Computations& comp)
{
    int head = comp.head;

    //includes 0 as part of the vector
    if (comp.direction == "left")
    {
        comp.left.push_back(0);
    }

    //includes the end track to the vector
    else if (comp.direction == "right")
    {
        comp.right.push_back(comp.disk_size);
    }
    //therefore giving us an accurate result


    // Separate disk requests into left and right vectors
    for(int i = 0; i < comp.size; i++)
    {
        if(disk_req[i].req < comp.head)
        {
            comp.left.push_back(disk_req[i].req);
        }
        else if(disk_req[i].req > comp.head)
        {
            comp.right.push_back(disk_req[i].req);
        }
    }

    // Sort left and right vector in ascending order
    sort(comp.left.begin(), comp.left.end());
    sort(comp.right.begin(), comp.right.end());
    // switching the begin() and end() will sort the data into descending order


    int run = 2; //Loop to scan both left and right
    while(run--)
    {
        if(comp.direction == "left")
        {
                
            //Scan left side (descending order)
            for(int i = comp.left.size() - 1; i >= 0; i--)
            {
                comp.curTrack = comp.left[i];

                //append current track to seek sequence
                comp.seek_sequence.push_back(comp.curTrack);

                // Calculate absolute distance
                // abs = computes for the absolute value
                comp.distance = abs(comp.curTrack - comp.head);

                //will increase the total count
                comp.seekCount += comp.distance;

                //accessed track is now the new head
                comp.head = comp.curTrack;
            }

            comp.direction = "right"; // Change direction after completing left scan
        }
        else if(comp.direction == "right")
        {
            // Scan right side (ascending order)
            for(int i = 0; i < comp.right.size(); i++)
            {
                comp.curTrack = comp.right[i];
                comp.seek_sequence.push_back(comp.curTrack);
                comp.distance = abs(comp.curTrack - comp.head);
                comp.seekCount += comp.distance;
                comp.head = comp.curTrack;
            }

            comp.direction = "left"; // Change direction after completing right scan
        }
    }

    cout << "\n\nTotal cylinder movement: = " << comp.seekCount << endl;
    cout << "Direction: " << comp.direction << endl;
    cout << "Seek Sequence: ";
    for(int i = 0; i < comp.seek_sequence.size(); i++)
    {
        cout << comp.seek_sequence[i];
        if(i < comp.seek_sequence.size() - 1) cout << " ";
    }
   cout << endl;
   
    
    vector<int> requests(comp.size);
    for (int  i = 0; i < comp.size; i++)
   {
   		requests[i] = disk_req[i].req;
   }
    
	vector<int> seekSequenceCopy(comp.size);
   for (int  i = 0; i < comp.size; i++)
   {
   		seekSequenceCopy[i] = comp.seek_sequence[i];
   }
   graph(requests, head, seekSequenceCopy);
}

void CSCAN(vector<Disk>& disk_req, Computations& comp)
{
    int head = comp.head;

    // Clear vectors to avoid duplicates
    comp.left.clear();
    comp.right.clear();
    comp.seek_sequence.clear();
    comp.seekCount = 0;

    // Separate disk requests into left and right vectors based on the head position
    for (int i = 0; i < comp.size; i++) {
        if (disk_req[i].req < comp.head) {
            comp.left.push_back(disk_req[i].req);
        } else {
            comp.right.push_back(disk_req[i].req);
        }
    }

    // Sort both vectors in ascending order
    sort(comp.left.begin(), comp.left.end());
    sort(comp.right.begin(), comp.right.end());

    // C-SCAN logic based on direction
    if (comp.direction == "left") {
        // Move left first (descending order)
        for (int i = comp.left.size() - 1; i >= 0; i--) {
            comp.curTrack = comp.left[i];
            comp.seek_sequence.push_back(comp.curTrack);
            comp.distance = abs(comp.curTrack - comp.head);
            comp.seekCount += comp.distance;
            comp.head = comp.curTrack;
        }

	// Jump to the lowest track (0) before jumping to 100
	if (!comp.right.empty()) {
   		int jump_to_zero = abs(comp.head - 0);  // Jump to 0 first
    	comp.seekCount += jump_to_zero;
    	comp.head = 0;
    	comp.seek_sequence.push_back(comp.head);

    	int jump_to_max = abs(comp.head - comp.disk_size);  // Jump to 100
	    comp.seekCount += jump_to_max;
	    comp.head = comp.disk_size;
    	comp.seek_sequence.push_back(comp.head);
	}



        // Move right after the jump (descending order)
        for (int i = comp.right.size() - 1; i >= 0; i--) {
            comp.curTrack = comp.right[i];
            comp.seek_sequence.push_back(comp.curTrack);
            comp.distance = abs(comp.curTrack - comp.head);
            comp.seekCount += comp.distance;
            comp.head = comp.curTrack;
        }
    } else if (comp.direction == "right") {
        // Move right first
        for (int i = 0; i < comp.right.size(); i++) {
            comp.curTrack = comp.right[i];
            comp.seek_sequence.push_back(comp.curTrack);
            comp.distance = abs(comp.curTrack - comp.head);
            comp.seekCount += comp.distance;
            comp.head = comp.curTrack;
        }

        // Jump to the lowest track (0)
        if (!comp.left.empty()) {
            comp.seekCount += abs(comp.head - 0);
            comp.head = 0;
            comp.seek_sequence.push_back(comp.head);
        }

        // Move left after the jump (ascending order)
        for (int i = 0; i < comp.left.size(); i++) {
            comp.curTrack = comp.left[i];
            comp.seek_sequence.push_back(comp.curTrack);
            comp.distance = abs(comp.curTrack - comp.head);
            comp.seekCount += comp.distance;
            comp.head = comp.curTrack;
        }
    }

    // Output results
    cout << "\n\nTotal cylinder movement: " << comp.seekCount << endl;
    cout << "Direction: " << comp.direction << endl;
    cout << "Seek Sequence: ";
    for (int i = 0; i < comp.seek_sequence.size(); i++) {
        cout << comp.seek_sequence[i];
        if (i < comp.seek_sequence.size() - 1) cout << " ";
    }
    cout << endl;

    // Copy seek sequence for graph function
    vector<int> requests(comp.size);
    for (int i = 0; i < comp.size; i++) {
        requests[i] = disk_req[i].req;
    }

    vector<int> seekSequenceCopy(comp.seek_sequence.size());
    for (int i = 0; i < comp.seek_sequence.size(); i++) {
        seekSequenceCopy[i] = comp.seek_sequence[i];
    }
	graph(requests, head, seekSequenceCopy);
}

void LOOK(vector<int> requests, int head, string direction, int diskSize) 
{
    int seek_count = 0;
    int head_copy = head; //keeps the original head position
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;

    // Appending values which are currently at left and right direction from the head.
    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        if (requests[i] > head)
            right.push_back(requests[i]);
    }

    // Sorting left and right vectors for servicing tracks in the correct sequence.
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Process based on the initial direction
    if (direction == "left") {
        // Process tracks to the left of the head
        for (int i = left.size() - 1; i >= 0; i--) {
            cur_track = left[i];
            seek_sequence.push_back(cur_track);
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
        // Process tracks to the right of the head
        for (int i = 0; i < right.size(); i++) {
            cur_track = right[i];
            seek_sequence.push_back(cur_track);
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    } else if (direction == "right") {
        // Process tracks to the right of the head
        for (int i = 0; i < right.size(); i++) {
            cur_track = right[i];
            seek_sequence.push_back(cur_track);
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
        // Process tracks to the left of the head
        for (int i = left.size() - 1; i >= 0; i--) {
            cur_track = left[i];
            seek_sequence.push_back(cur_track);
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    }

    cout << "\n\nTotal cylinder movement: = " << seek_count << endl;
    cout << "Seek Sequence is: ";
    for (int i = 0; i < seek_sequence.size(); i++) {
        cout << seek_sequence[i] << " ";
    }
    cout << endl;
    graph(requests, head_copy, seek_sequence);
}

void CLOOK(vector<int> requests, int head, string direction, int diskSize)
{
	int seek_count = 0;
	int head_copy = head; //keeps the original head position
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;

    // Appending values which are currently at left and right direction from the head.
    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        if (requests[i] > head)
            right.push_back(requests[i]);
    }

    // Sorting left and right vectors for servicing tracks in the correct sequence.
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    
    if (direction == "left") {
        // Process tracks to the left of the head
        for (int i = left.size() - 1; i >= 0; i--) {
            cur_track = left[i];
            seek_sequence.push_back(cur_track);
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
        // Jump to the farthest track on the right
        if (!right.empty()) {
            seek_count += abs(head - right[right.size() - 1]);
            head = right[right.size() - 1];
        }
        // Process tracks to the right of the head
        for (int i = right.size() - 1; i >= 0; i--) {
            cur_track = right[i];
            seek_sequence.push_back(cur_track);
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    } else if (direction == "right") {
        // Process tracks to the right of the head
        for (int i = 0; i < right.size(); i++) {
            cur_track = right[i];
            seek_sequence.push_back(cur_track);
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
        // Jump to the farthest track on the left
        if (!left.empty()) {
            seek_count += abs(head - left[0]);
            head = left[0];
        }
        // Process tracks to the left of the head
        for (int i = 0; i < left.size(); i++) {
            cur_track = left[i];
            seek_sequence.push_back(cur_track);
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    }

    cout << "\n\nTotal cylinder movement: = " << seek_count << endl;
    cout << "Seek Sequence is: ";
    for (int i = 0; i < seek_sequence.size(); i++) {
        cout << seek_sequence[i] << " ";
    }
    cout << endl;
    graph(requests, head_copy, seek_sequence);
}

void graph(vector<int> requests, int head, vector<int> seek_sequence)
{
	cout << endl << endl;
	int size = requests.size();

	
	//Graph making using GNUPLOT
	//GNUPLOT has to be downloaded first before this graph to function.
	//It can be downloaded here: http://www.gnuplot.info/
	//The dir (short for directory) requires to be changed depending on the file path of THIS program.
    string dir = "C:/Users/carlo/OneDrive/Documents/Programming/CodingC++/Sorting Algorithm/All versions/v.2-2.3-3.1.6 (Disc Management Major Update)/";

    // ?? Check if Gnuplot exists
    ifstream gnuplotCheck("C:/Program Files/gnuplot/bin/gnuplot.exe");
    if (!gnuplotCheck) {
        cerr << "Error: Gnuplot executable not found. Check the installation path." << endl;
    }
    gnuplotCheck.close();

    // ?? Save `scan_data.txt` in the correct directory
    ofstream dataFile(dir + "disk_data.txt");
    if (!dataFile) {
        cerr << "Error: Could not create disk_data.txt" << endl;
    }

    int step = 0;
    dataFile << head << " " << step++ << endl; // Mark initial head position
    for (int pos : seek_sequence) {
        dataFile << pos << " " << step++ << endl;
    }
    dataFile.close();

    // ?? Generate `x_labels.gnu`
    ofstream xLabelsFile(dir + "x_labels.gnu");
    if (!xLabelsFile) {
        cerr << "Error: Could not create x_labels.gnu" << endl;
    }

    xLabelsFile << "set xtics (";
    for (size_t i = 0; i < size; i++) {
        xLabelsFile << "\"" << requests[i] << "\" " << requests[i];
        if (i != size - 1) xLabelsFile << ", ";
    }
    xLabelsFile << ")\n";
    xLabelsFile.close();

    // ?? Write `scan_plot.gnu`
    ofstream gnuplotScript(dir + "disk_plot.gnu");
    if (!gnuplotScript) {
        cerr << "Error: Could not create disk_plot.gnu" << endl;
    }

    gnuplotScript << "set title 'Disk Scheduling' font ',14'\n";
    gnuplotScript << "set xlabel 'Disk Position' font ',12'\n";
    gnuplotScript << "set ylabel 'Step' font ',12'\n";
    gnuplotScript << "set ytics font ',10'\n";
    gnuplotScript << "set xtics font ',5'\n";
    gnuplotScript << "load '" + dir + "x_labels.gnu'\n";
    gnuplotScript << "plot '" + dir + "disk_data.txt' using 1:2 with linespoints title 'Disk Head Movement'\n";
    gnuplotScript.close();

    // ?? Execute GNUPlot with properly quoted path
    // Properly escape the command for Windows cmd
	string gnuplotCommand = "cmd /c \"\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist \"" + dir + "disk_plot.gnu\"\"";
	cout << "Running: " << gnuplotCommand << endl;
	system(gnuplotCommand.c_str());
}
