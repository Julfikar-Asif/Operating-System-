#include<iostream>
using namespace std;

const int MAX_PROCESS = 10;
const int MAX_RESOURCE = 10;

void safety(int alloc[MAX_PROCESS][MAX_RESOURCE], int max_mat[MAX_PROCESS][MAX_RESOURCE], int avail[MAX_RESOURCE], int need[MAX_PROCESS][MAX_RESOURCE], int num_processes, int num_resources)
{
    bool finish[MAX_PROCESS] = {false};
    int safe_sequence[MAX_PROCESS] = {0};
    int work[MAX_RESOURCE];

    // Initialize work array with available resources
    for(int i = 0; i < num_resources; i++)
    {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < num_processes)
    {
        bool found = false;
        for (int i = 0; i < num_processes; i++)
        {
            if (!finish[i])
            {
                bool can_allocate = true;
                for (int j = 0; j < num_resources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate)
                {
                    for (int j = 0; j < num_resources; j++)
                    {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = true;
                    safe_sequence[count++] = i;
                    found = true;
                }
            }
        }
        if (!found)
        {
            cout << "System is in unsafe state." << endl;
            return;
        }
    }

    cout << "System is in safe state." << endl;
    cout << "Safe sequence is: ";
    for (int i = 0; i < num_processes; i++)
    {
        cout << safe_sequence[i] << " ";
    }
    cout << endl;
}

void resourceRequest(int alloc[MAX_PROCESS][MAX_RESOURCE], int avail[MAX_RESOURCE], int need[MAX_PROCESS][MAX_RESOURCE], int process_id, int request[MAX_RESOURCE], int num_processes, int num_resources)
{
    bool grant = true;

    // Check if request can be granted
    for (int i = 0; i < num_resources; i++)
    {
        if (request[i] > need[process_id][i] || request[i] > avail[i])
        {
            grant = false;
            break;
        }
    }

    if (grant)
    {
        // Simulate resource allocation
        for (int i = 0; i < num_resources; i++)
        {
            avail[i] -= request[i];
            alloc[process_id][i] += request[i];
            need[process_id][i] -= request[i];
        }

        // Check if the system is in a safe state after resource allocation
        safety(alloc, alloc, avail, need, num_processes, num_resources);
    }
    else
    {
        cout << "Request cannot be granted." << endl;
    }
}

int main()
{
    int num_processes, num_resources;

    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the number of resource types: ";
    cin >> num_resources;

    int alloc[MAX_PROCESS][MAX_RESOURCE], max_mat[MAX_PROCESS][MAX_RESOURCE], avail[MAX_RESOURCE], need[MAX_PROCESS][MAX_RESOURCE];

    cout << "Enter allocation matrix:" << endl;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            cin >> alloc[i][j];
        }
    }

    cout << "Enter max matrix:" << endl;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            cin >> max_mat[i][j];
        }
    }

    cout << "Enter available resources:" << endl;
    for (int i = 0; i < num_resources; i++)
    {
        cin >> avail[i];
    }

    // Calculate need matrix
    cout<< "need matrix :\n ";
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            need[i][j] = max_mat[i][j] - alloc[i][j];
            cout<<need[i][j]<<" ";
        }
        cout<<"\n";

    }

    int choice;
    cout << "Choose algorithm to execute (1: Safety Algorithm, 2: Resource Request Algorithm): ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        safety(alloc, max_mat, avail, need, num_processes, num_resources);
        break;
    }
    case 2:
    {
        int process_id;
        cout << "Enter process ID for resource request: ";
        cin >> process_id;

        int request[MAX_RESOURCE];
        cout << "Enter resource request: ";
        for (int i = 0; i < num_resources; i++)
        {
            cin >> request[i];
        }

        resourceRequest(alloc, avail, need, process_id, request, num_processes, num_resources);
        break;
    }
    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

 /*Allocation Mat

       0 1 0
       2 0 0
       3 0 2
       2 1 1
       0 0 2       */

 /*  Max mat

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3       */


