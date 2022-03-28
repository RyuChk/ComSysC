#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

//Thread Data Struct
struct ThreadInfo
{
    int start,stop,result;
};

void *RunningInThread(void *vargc)
{
    struct ThreadInfo *Input = (struct ThreadInfo *)vargc;
    (*Input).result = 0;
    for (int i = (*Input).start; i < (*Input).stop; i++){
        (*Input).result += i;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    //Check Arg Input format
    if (atoi(argv[1]) == 0 || atoi(argv[2]) == 0)
    {
        printf("Error Format or the number which are input is 0\n The format should be in integer : 1...N \n Inputted : %s", argv[0]);
        return EXIT_FAILURE;
    }

    //If 1 return 1
    if (atoi(argv[1]) == 1)
    {
        printf("The answer of sum of N is : 1");
        return 0;
    }

    printf("--------------------------Start-Process--------------------------\n");

    //Create INPUT variable
    int INPUT = atoi(argv[1]);
    int N_Thread = atoi(argv[2]);

    //Check Number of Threads
    if (N_Thread < 2) {
        fprintf(stderr,"The number of Thread is too low -- The minimun is N >= 2 -- \n");
        return EXIT_FAILURE;
    }

    struct ThreadInfo Que[N_Thread];

    printf("CALCULATE SUMATION OF : %d \n", INPUT);
    printf("WITH <%d> THREADS \n", N_Thread);
    //Creating Que;
    int segment = ceil((float)INPUT/N_Thread), locator = segment;
    Que[0].start = 1;
    Que[0].stop = locator;

    for (int i = 1; i < N_Thread - 1 ;i++)
    {
        Que[i].start = locator;
        Que[i].stop = locator + segment;
        locator += segment;
    }
    Que[N_Thread-1].start = locator;
    Que[N_Thread-1].stop = INPUT+1;

    for (int i = 0; i < N_Thread; i++)
    {
        printf("Thread %d Adding from : %d, %d \n",i , Que[i].start, Que[i].stop);
    }
    
    //Creating Thread
    pthread_t Thread_Id;
    for (int i = 0; i < N_Thread; i++)
    {
        if ((pthread_create(&Thread_Id, NULL, RunningInThread, (void *)&Que[i])) != 0)
        {
            perror("Error Create Thread");
        }
        
    }

    //Joining Thread
    pthread_join(Thread_Id, NULL);

    //Sum Result
    int result = 0;
    for (int i = 0; i < N_Thread; i++)
    {
        result += Que[i].result;
    }
    fprintf(stdout, "Result of sum using Threading is : <%d>\n", result);
    printf("---------------------------End-Process---------------------------\n");
    return 0;
}