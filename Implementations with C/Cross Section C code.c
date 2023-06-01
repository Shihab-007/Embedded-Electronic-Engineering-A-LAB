#include <stdio.h>

#define N 6 //number of cars

int list[N+1];
int len;

int cars[n];

int blocks[4]; //4 blocks in the cross section

int leftarr[N]; //what the incoming car wants to do
int rightarr[N];
int straightarr[N];

int prioritylow[N]; //priority of the incoming car
int prioritymid[N];   
int priorityhigh[N];

int locA[N]; //location from where a car can come from
int locB[N];
int locC[N];
int locD[N];

int cango=0; //variable to check if car can cross or not

void spawn()
{

}

void dequeue()
{
        int i = 0;
        len -= 1;
        while (i < len)
        {
                list[i] = list[i + 1];
                i++;
        }
        list[i] = 0;
}

void enqueue()
{
}

int main()
{ 


    return 0;
}