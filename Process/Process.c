#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

int SumOfLoop(int Start, int Finish) 
{
    int result = 0;
    for (int i = Start; i < Finish; i++)
    {
        result += i;
    }
    return result;
}

int main(int argc, char *argv[] )
{
    int C1ID, C2ID, CP1[2], CP2[2];
    
    //Check Argc Input Length
    if (argc > 2) 
    {
        fprintf(stderr, "Too many argument %d \n", argc);
        return EXIT_FAILURE;
    }

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

    //Create INPUT variable
    int INPUT = atoi(argv[1]);

    //creating pipe
    if(pipe(CP1) < 0 || pipe(CP2) < 0)
    {
        fprintf(stderr, "-- Error creating pipe --");
        return EXIT_FAILURE;
    }

    //Child 1
    if((C1ID = fork()) == 0)
    {
        int result = SumOfLoop(1, (int)ceil(INPUT/2));
        printf("Child 1 Start from 1 --> %d \n", (int)ceil(INPUT/2));
        write(CP1[1], &result, sizeof(int));
        exit(0);
    } else if ((C2ID = fork()) == 0) //Child 2
    {
        int result = SumOfLoop((int)ceil(INPUT/2), INPUT+1);
        printf("Child 2 Start from %d --> %d \n", (int)ceil(INPUT/2), INPUT);
        write(CP2[1], &result, sizeof(int));
        exit(0);
    } else if ((C1ID = fork()) < 0 || (C2ID = fork()) < 0)
    {
        fprintf(stderr, "-- Error creating child process! --");
        return EXIT_FAILURE;
    } else 
    {
        wait(NULL);
        int Result1, Result2;
        read(CP1[0], &Result1, sizeof(int));
        read(CP2[0], &Result2, sizeof(int));
        printf("The answer of sum of N is : %d", (Result1+Result2));
    }
    return 0;
}