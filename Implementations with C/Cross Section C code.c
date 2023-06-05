#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6 //number of cars

int car1,car2,car3,car4,car5,car6;

bool c1,c2,c3,c4,c5,c6;

int list[N+1];
int len;

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

int nmbr_events = 1000;

int generateCarID() {
    static int carCounter = 0;
    return ++carCounter;
}

void spawn()
{   
    if (c1 ==false)
    {
        car
    }
}


int randomizer(nmbr_events)
{
    int event;
    time_t t;
    srand((unsigned) time(&t));
    event = rand() % nmbr_events;
    printf("%d\n", event);
    return event;
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

typedef enum {
    FREE,
    OCCUPIED,
    CHECKING
} State;

int state = 0;

int main()
{       
    switch(state) {
        case FREE:
            printf("State = FREE.\n\n");
            
            
            
            
            break;
        case OCCUPIED:
            printf("The state is OCCUPIED.\n");
            break;
        case CHECKING:
            printf("The state is PROCESSING.\n");
            break;
        default:
            printf("Invalid state.\n");
    }

    return 0;
}
