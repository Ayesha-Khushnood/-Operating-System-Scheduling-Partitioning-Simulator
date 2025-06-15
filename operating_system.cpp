
//Instruction: Run in full screen please

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
const int MAX_PROCESSES = 100;


using namespace std;

class Scheduler {
private:
    struct Process {
        string name;
        int arrivalTime;
        int burstTime;
        int remainingTime;
        int completionTime;
    };

    Process processes[100]; // Assuming a maximum of 100 processes
    int numProcesses = 0;
    int completionTime[100] = {0}; // Completion time of processes

public:
	//preemptive
	void sjfPreemptive() {
    // Sort processes based on arrival time
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = i + 1; j < numProcesses; ++j) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                swap(processes[i], processes[j]);
            }
        }
    }

    // Simulate SJF preemptive
    int currentTime = 0;
    int remainingTime[MAX_PROCESSES];
    for (int i = 0; i < numProcesses; ++i) {
        remainingTime[i] = processes[i].burstTime;
    }
    int completed = 0;
    while (completed != numProcesses) {
        int shortest = -1;
        int shortestTime = INT_MAX;
        for (int i = 0; i < numProcesses; ++i) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] < shortestTime && remainingTime[i] > 0) {
                shortest = i;
                shortestTime = remainingTime[i];
            }
        }
        if (shortest == -1) {
            currentTime++;
            continue;
        }
        remainingTime[shortest]--;
        currentTime++;
        if (remainingTime[shortest] == 0) {
            completionTime[shortest] = currentTime;
            completed++;
        }
    }
    
}

void roundRobin() {
    // Calculate Round Robin preemptive
    int quantum;
    cout << "Enter time quantum for Round Robin: ";
    cin >> quantum;

    int remainingBurstTime[MAX_PROCESSES];
    for (int i = 0; i < numProcesses; ++i) {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    while (true) {
        bool done = true;
        for (int i = 0; i < numProcesses; ++i) {
            if (remainingBurstTime[i] > 0) {
                done = false; // There are pending processes
                if (remainingBurstTime[i] > quantum) {
                    currentTime += quantum;
                    remainingBurstTime[i] -= quantum;
                } else {
                    currentTime += remainingBurstTime[i];
                    completionTime[i] = currentTime;
                    remainingBurstTime[i] = 0;
                }
            }
        }
        if (done) // All processes are done
            break;
    }
    
}

    void determinePreemptiveAlgorithm() {
    // Input processes
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Enter name for process " << i + 1 << ": ";
        cin >> processes[i].name;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    // Calculate SJF preemptive
    sjfPreemptive();
    double avgWaitingSJF = getAvgWaitingTime();

    // Calculate Round Robin preemptive
    roundRobin();
    double avgWaitingRR = getAvgWaitingTime();

    // Determine which algorithm has the lower average waiting time
    string chosenAlgorithm;
    double chosenAvgWaiting;
    if (avgWaitingSJF < avgWaitingRR) {
        chosenAlgorithm = "SJF Preemptive";
        chosenAvgWaiting = avgWaitingSJF;
    } else if (avgWaitingRR < avgWaitingSJF) {
        chosenAlgorithm = "Round Robin Preemptive";
        chosenAvgWaiting = avgWaitingRR;
    } else {
        chosenAlgorithm = "Both algorithms have the same average waiting time";
        chosenAvgWaiting = avgWaitingSJF;
    }

    // Display the output in tabular form
    cout << "\n\nOptimal Algorithm: " << chosenAlgorithm << endl;
    cout << "Average Waiting Time: " << chosenAvgWaiting << endl;
    cout << "\nDetails:\n";
    cout << setw(10) << "Process" << setw(15) << "Arrival Time" << setw(15) << "Burst Time" << setw(20) << "Completion Time" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        cout << setw(10) << processes[i].name << setw(15) << processes[i].arrivalTime << setw(15) << processes[i].burstTime << setw(20) << completionTime[i] << endl;
    }
}

void displayProcesses() {
    cout << "Process\tTurnaround Time\tWaiting Time\n";
        double totalTurnaroundTime = 0;
        double totalWaitingTime = 0;
        for (int i = 0; i < numProcesses; ++i) {
            int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
            int waitingTime = turnaroundTime - processes[i].burstTime;
            cout << processes[i].name << "\t" << turnaroundTime << "\t\t" << waitingTime << endl;
            totalTurnaroundTime += turnaroundTime;
            totalWaitingTime += waitingTime;
        }

        cout << "Average Turnaround Time: " << fixed << setprecision(2) << totalTurnaroundTime / numProcesses << endl;
        cout << "Average Waiting Time: " << fixed << setprecision(2) << totalWaitingTime / numProcesses << endl;
        //system("cls");
}
void takeInput() {
 cout << "Enter the number of processes: ";
    cin >> numProcesses;
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Enter name for process " << i + 1 << ": ";
        cin >> processes[i].name;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
}
system("cls");
}




double getAvgWaitingTime() {
    double totalWaitingTime = 0;
    for (int i = 0; i < numProcesses; ++i) {
        totalWaitingTime += completionTime[i] - processes[i].arrivalTime - processes[i].burstTime;
    }
    return totalWaitingTime / numProcesses;
}
//non preemptive
    void displayProcessesnon() {
        int completionTime[100] = {0}; // Completion time of processes
        double totalTurnaroundTime = 0;
        double totalWaitingTime = 0;

        for (int i = 0; i < numProcesses; ++i) {
            if (i == 0 || processes[i].arrivalTime > completionTime[i - 1]) {
                completionTime[i] = processes[i].arrivalTime + processes[i].burstTime;
            } else {
                completionTime[i] = completionTime[i - 1] + processes[i].burstTime;
            }
            int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
            int waitingTime = turnaroundTime - processes[i].burstTime; // Calculate waiting time properly
            totalTurnaroundTime += turnaroundTime;
            totalWaitingTime += waitingTime;
        }

        cout << "Process\tTurnaround Time\tWaiting Time\n";
        for (int i = 0; i < numProcesses; ++i) {
            cout << processes[i].name << "\t" << completionTime[i] - processes[i].arrivalTime << "\t\t" << (completionTime[i] - processes[i].arrivalTime) - processes[i].burstTime << endl;
        }

        cout << "Average Turnaround Time: " << fixed << setprecision(2) << totalTurnaroundTime / numProcesses << endl;
        cout << "Average Waiting Time: " << fixed << setprecision(2) << totalWaitingTime / numProcesses << endl;
       
        
    }

void determineNonPreemptiveAlgorithm() {
    // Input processes
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Enter name for process " << i + 1 << ": ";
        cin >> processes[i].name;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    // Calculate FCFS non-preemptive
    fcfsNonPreemptive();
    double avgWaitingFCFS = getAvgWaitingTime();

    // Calculate SJF non-preemptive
    sjfNonPreemptive();
    double avgWaitingSJF = getAvgWaitingTime();

    // Determine which algorithm has the lower average waiting time
    string chosenAlgorithm;
    double chosenAvgWaiting;
    if (avgWaitingFCFS < avgWaitingSJF) {
        chosenAlgorithm = "FCFS Non-Preemptive";
        chosenAvgWaiting = avgWaitingFCFS;
    } else if (avgWaitingSJF < avgWaitingFCFS) {
        chosenAlgorithm = "SJF Non-Preemptive";
        chosenAvgWaiting = avgWaitingSJF;
    } else {
        chosenAlgorithm = "Both algorithms have the same average waiting time";
        chosenAvgWaiting = avgWaitingFCFS;
    }

    // Display the output in tabular form
    cout << "\n\nOptimal Algorithm: " << chosenAlgorithm << endl;
    cout << "Average Waiting Time: " << chosenAvgWaiting << endl;
    cout << "\nDetails:\n";
    cout << setw(10) << "Process" << setw(15) << "Arrival Time" << setw(15) << "Burst Time" << setw(20) << "Completion Time" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        cout << setw(10) << processes[i].name << setw(15) << processes[i].arrivalTime << setw(15) << processes[i].burstTime << setw(20) << completionTime[i] << endl;
    }
}


 void fcfsNonPreemptive() {

        // Sort processes by arrival time
        for (int i = 0; i < numProcesses; ++i) {
            for (int j = i + 1; j < numProcesses; ++j) {
                if (processes[j].arrivalTime < processes[i].arrivalTime) {
                    swap(processes[i], processes[j]);
                }
            }
        }

        // Calculate completion time
        double totalTurnaroundTime = 0;
        double totalWaitingTime = 0;
        for (int i = 0; i < numProcesses; ++i) {
            if (i == 0 || processes[i].arrivalTime > completionTime[i - 1]) {
                completionTime[i] = processes[i].arrivalTime + processes[i].burstTime;
            } else {
                completionTime[i] = completionTime[i - 1] + processes[i].burstTime;
            }
            int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
            int waitingTime = turnaroundTime - processes[i].burstTime;
            totalTurnaroundTime += turnaroundTime;
            totalWaitingTime += waitingTime;
        }

       
    }

    void sjfNonPreemptive() {
       
        // Sort processes by burst time
        for (int i = 0; i < numProcesses; ++i) {
            for (int j = i + 1; j < numProcesses; ++j) {
                if (processes[j].burstTime < processes[i].burstTime) {
                    swap(processes[i], processes[j]);
                }
            }
        }

        // Calculate completion time
        double totalTurnaroundTime = 0;
        double totalWaitingTime = 0;
        for (int i = 0; i < numProcesses; ++i) {
            if (i == 0 || processes[i].arrivalTime > completionTime[i - 1]) {
                completionTime[i] = processes[i].arrivalTime + processes[i].burstTime;
            } else {
                completionTime[i] = completionTime[i - 1] + processes[i].burstTime;
            }
            int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
            int waitingTime = turnaroundTime - processes[i].burstTime;
            totalTurnaroundTime += turnaroundTime;
            totalWaitingTime += waitingTime;
        }

       
    }

   void preemptiveMenu() {
    while (true) {
       

        cout<<"\n\n\t\t\t\t\t\tPlease,  Choose from the following Options: \n\n";
        cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
        cout<<"\t\t\t\t\t\t|                                           	                  |\n";
        cout<<"\t\t\t\t\t\t|              PREEMPTIVE SCHEDULING                              |\n";
        cout<<"\t\t\t\t\t\t|             1  >> Automatically Determine                       |\n";
        cout<<"\t\t\t\t\t\t|             2  >> Round Robin                                   |\n";
        cout<<"\t\t\t\t\t\t|             3  >> Shortest Job First (SJF - Preemptive)         |\n";
        cout<<"\t\t\t\t\t\t|             4  >> Return to Main Menu                           |\n";
        cout<<"\t\t\t\t\t\t|             5  >> Quit                                          |\n";
        cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n";
       
        int choice;
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                determinePreemptiveAlgorithm();
                break;
            case 2:
            	takeInput();
                roundRobin();
                displayProcesses();
                break;
            case 3:
            	takeInput();
                sjfPreemptive();
                displayProcesses();
                break;
            case 4:
                return;
            case 5:
                exit(0);
            default:
                cout << "Invalid choice!\n";
        }
    }
}
    void nonPreemptiveMenu() {
    while (true) {
       
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
        cout<<"\t\t\t\t\t\t|                                           	                  |\n";
        cout<<"\t\t\t\t\t\t|               Non-Preemptive Scheduling Menu                    |\n";
        cout<<"\t\t\t\t\t\t|             What would you like to do?                          |\n";
        cout<<"\t\t\t\t\t\t|             Press desired number for the task:                  |\n";
        cout<<"\t\t\t\t\t\t|             1  >> Automatically Determine                       |\n";
        cout<<"\t\t\t\t\t\t|             2  >> First Come First Serve (FCFS)                 |\n";
        cout<<"\t\t\t\t\t\t|             3  >> Shortest Job First (SJF - Non-Preemptive)     |\n";
        cout<<"\t\t\t\t\t\t|             4  >> Main Menu                                     |\n";
        cout<<"\t\t\t\t\t\t|             5  >>  Quit                                         |\n";
        cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n";
       
        int choice;
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                determineNonPreemptiveAlgorithm();
                break;
            case 2:
            	takeInput();
                fcfsNonPreemptive();
                displayProcessesnon();
            
                break;
            case 3:
            	takeInput();
                 sjfNonPreemptive();
				 displayProcessesnon();
				 
                break;
            case 4:
                return;
            case 5:
                exit(0);
            default:
                cout << "Invalid choice!\n";
        }
    }
}

    void schedulingMenu() {
        while (true) {
          
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
        cout<<"\t\t\t\t\t\t|                                           	                  |\n";
        cout<<"\t\t\t\t\t\t|                  Scheduling Menu                                |\n";
        cout<<"\t\t\t\t\t\t|             What would you like to do?                          |\n";
        cout<<"\t\t\t\t\t\t|             Press desired number for the task:                  |\n";
        cout<<"\t\t\t\t\t\t|             1  >> Non-Preemptive                                |\n";
        cout<<"\t\t\t\t\t\t|             2  >> Preemptive                                    |\n";
        cout<<"\t\t\t\t\t\t|             3  >> Main Menu                                     |\n";
        cout<<"\t\t\t\t\t\t|             4  >> Quit                                          |\n";
        cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n";
            
            int choice;
            cin >> choice;
            system("cls");

            switch (choice) {
                case 1:
                    nonPreemptiveMenu();
                    break;
                case 2:
                    preemptiveMenu();
                    break;
                case 3:
                    return;
                case 4:
                    exit(0);
                default:
                    cout << "Invalid choice!\n";
            }
        }
    }


    void partitioningMenu() {
        while (true) {
            
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"\n\n\t\t\t\t\t\tPlease,  Choose from the following Options: \n\n";
        cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
        cout<<"\t\t\t\t\t\t|                                           	                  |\n";
        cout<<"\t\t\t\t\t\t|                  Partitioning Menu                              |\n";
        cout<<"\t\t\t\t\t\t|             What would you like to do?                          |\n";
        cout<<"\t\t\t\t\t\t|             Press desired number for the task:                  |\n";
        cout<<"\t\t\t\t\t\t|             1  >> Fixed Size Partitioning                       |\n";
        cout<<"\t\t\t\t\t\t|             2  >> Variable Size Partitioning                    |\n";
        cout<<"\t\t\t\t\t\t|             3  >> Main Menu                                     |\n";
        cout<<"\t\t\t\t\t\t|             4  >> Quit                                          |\n";
        cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n";
            
            int choice;
            cin >> choice;
            system("cls");

            switch (choice) {
                case 1:
                    fixedPartitioning();
                    break;
                case 2:
                    variablePartitioning();
                    break;
                case 3:
                    return;
                case 4:
                    exit(0);
                default:
                    cout << "Invalid choice!\n";
            }
        }
    }

    void mainMenu() {
        while (true) {
        	
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
     cout<<"\n\n\t\t\t\t\t\tPlease,  Choose from the following Options: \n\n";
        cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
        cout<<"\t\t\t\t\t\t|                                           	                  |\n";
        cout<<"\t\t\t\t\t\t|                  MAIN MENU                                      |\n";
        cout<<"\t\t\t\t\t\t|             What would you like to do?                          |\n";
        cout<<"\t\t\t\t\t\t|             Press desired number for the task:                  |\n";
        cout<<"\t\t\t\t\t\t|             1  >> Scheduling                                    |\n";
        cout<<"\t\t\t\t\t\t|             2  >> Partitioning                                  |\n";
        cout<<"\t\t\t\t\t\t|             3  >> Quit                                          |\n";
        cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n";
            
            int choice;
            cin >> choice;
            system("cls");

            switch (choice) {
                case 1:
                    schedulingMenu();
                    break;
                case 2:
                    partitioningMenu();
                    break;
                case 3:
                     cout << "Exiting the program..." << endl;
               cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
cout<<"\t\t\t\t\t@@ _______________________________________________________________________________________ @@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                      GOODBYE!                                         |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
cout<<"\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n\t\t\t\t\t";
               
                    return;
                default:
                    cout << "Invalid choice!\n";
            }
        }
    }
    
    void fixedPartitioning() {
    int totalMemorySize, numProcesses;
    cout << "Enter the total memory size: ";
    cin >> totalMemorySize;

    int numPartitions;
    cout << "Enter the number of partitions: ";
    cin >> numPartitions;

    int partitionSizes[numPartitions];
    cout << "Enter the size of each partition:\n";
    for (int i = 0; i < numPartitions; ++i) {
        cout << "Size of Partition " << i + 1 << ": ";
        cin >> partitionSizes[i];
    }

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    int processSizes[numProcesses];
    cout << "Enter the size of each process:\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Size of Process " << i + 1 << ": ";
        cin >> processSizes[i];
    }

    int internalFragmentation[numPartitions] = {0}; // Internal fragmentation for each partition

    cout << "\nMemory Allocation for Fixed Size Partitioning:\n";
    cout << "Total Memory Size: " << totalMemorySize << endl;
    cout << "Number of Partitions: " << numPartitions << endl;

    cout << "\nMemory Allocation Details:\n";
    cout << "Partition\tProcess\tAllocated Memory\tInternal Fragmentation\n";
    
    // Initialize an array to track if a partition is already allocated
    bool allocatedPartitions[numPartitions] = {false};
    
    for (int i = 0; i < numProcesses; ++i) {
        bool processAllocated = false; // Flag to check if process is allocated
        for (int j = 0; j < numPartitions; ++j) {
            if (!allocatedPartitions[j] && processSizes[i] <= partitionSizes[j]) {
                allocatedPartitions[j] = true; // Mark partition as allocated
                internalFragmentation[j] = partitionSizes[j] - processSizes[i];
                cout << "Partition " << j + 1 << "\tProcess " << i + 1 << "\t" << processSizes[i] << "\t\t" << internalFragmentation[j] << endl;
                processAllocated = true; // Mark process as allocated
                break; // Exit the loop once allocation is done
            }
        }
        if (!processAllocated) {
            cout << "Process " << i + 1 << " cannot be allocated due to insufficient memory\n";
        }
    }

    // Count unallocated partitions to calculate external fragmentation
    int unallocatedPartitions = 0;
    for (int j = 0; j < numPartitions; ++j) {
        if (!allocatedPartitions[j]) {
            unallocatedPartitions++;
        }
    }

    cout << "\nExternal Fragmentation: " << unallocatedPartitions << " partition(s)\n";
}



   void variablePartitioning() {
   	int i;
        int totalMemorySize, numProcesses, processSize[i], allocatedMemory = 0;
        cout << "Enter the total memory size: ";
        cin >> totalMemorySize;
        cout << "Enter the number of processes: ";
        cin >> numProcesses;
        cout << "Enter the size of each process:\n";
        for (int i = 0; i < numProcesses; ++i) {
            cin >> processSize[i];
            if (processSize[i] <= totalMemorySize - allocatedMemory) {
                cout << "Process " << i + 1 << " allocated\n";
                allocatedMemory += processSize[i];
            } else {
                cout << "Process " << i + 1 << " can't be allocated due to insufficient memory\n";
            }
        }
        cout << "Total allocated memory: " << allocatedMemory << endl;
        cout << "Total unallocated memory: " << totalMemorySize - allocatedMemory << endl;
        cout << "External Fragmentation: " << totalMemorySize - allocatedMemory << endl;
    }

};

int main() {
	system("color 0A");
        	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout<<"\t\t\t\t\t@@ _______________________________________________________________________________________ @@\n";
    cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout<<"\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout<<"\t\t\t\t\t@@|                                  OPERATING SYSTEM LAB                                 |@@\n";
    cout<<"\t\t\t\t\t@@|                                       PROJECT                                         |@@\n";
    cout<<"\t\t\t\t\t@@|                              SCHEDULING AND PARTITIONING                              |@@\n";
    cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
    cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
    cout<<"\t\t\t\t\t@@|                                                -BY: Ayesha Khushnood                  |@@\n";
    cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
    cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
    cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
    cout<<"\t\t\t\t\t@@|                                                                                       |@@\n";
    cout<<"\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n\t\t\t\t\t";
    system("pause");
    system("cls");
    Scheduler scheduler;
    scheduler.mainMenu();

    return 0;
}

