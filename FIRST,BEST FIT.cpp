#include<iostream>
#include<bits/stdc++.h>
using namespace std;


void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    memset(allocation, -1, sizeof(allocation));
    for (int i=0; i<n; i++)
    {
        int temp = -1;
        for (int j=0; j<m; j++)
        {
            if (blockSize[j]>=processSize[i])
                {
                    if(temp==-1|| blockSize[j]<blockSize[temp]){
                        temp=j;
                    }
                    allocation[i]=j;
                    blockSize[j]-=processSize[i];
                    break;
                }
            }
        }


 /*void bestfit(int blockSize[], int m, int processSize[], int n)
{

    int allocation[n];

    memset(allocation, -1, sizeof(allocation));

    for (int i=0; i<n; i++)
    {
        int temp=-1;
        int frag=0;
        for (int j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (temp == -1)
                {
                    temp = j;
                    frag=blockSize[j]-processSize[i];
                }
                else if (frag>blockSize[j]-processSize[i])
                    temp = j;
                frag=blockSize[j]-processSize[i];

            }
        }

        if (temp != -1)
        {

            allocation[i] = temp;

            blockSize[temp] -= processSize[i];
        }
    }
*/



    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << "   " << i+1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}



int main()
{
    int blockSize[] = {200,350,100};
    int processSize[] = {100,150,200,50,150};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);
    cout<<"Applying Best Fit we get : "<<endl;
    firstFit(blockSize, m, processSize, n);
    //bestfit(blockSize, m, processSize, n);
    return 0 ;
}

