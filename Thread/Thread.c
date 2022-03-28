#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

static int result = 0;   

void *RunningInThread(void *vargc)
{
    sleep(1);
    int *intinput = (int *)vargc;
    printf("Calculate from <%d> to <%d> \n", intinput[0], intinput[1]-1);
    for (int i = (int)intinput[0]; i < (int)intinput[1]; i++){
        result += i;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    //Check Arg Input format
    if (atoi(argv[1]) == 0)
    {
        fprintf(stderr, "Error Format or the number which are input is 0\n The format should be in integer : 1...N \n Inputted : %s", argv[0]);
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
    int FH[2] = {0,ceil(INPUT/2)};
    int LH[2] = {ceil(INPUT/2), INPUT+1};
    
    pthread_t Thread_Id;
    fprintf(stdout, "Creating Thread.... \n");

    //Creating Thread
    pthread_create(&Thread_Id, NULL, RunningInThread, (void *)&FH);
    pthread_create(&Thread_Id, NULL, RunningInThread, (void *)&LH);

    //Joining Thread
    fprintf(stdout, "Finish Creating Thread! \n");
    pthread_join(Thread_Id, NULL);
    fprintf(stdout, "Result of sum using Threading is : <%d>\n", result);
    printf("---------------------------End-Process---------------------------\n");
    return 0;
}