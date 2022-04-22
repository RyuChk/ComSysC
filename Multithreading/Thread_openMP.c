#include <stdio.h>
#include <omp.h>

// gcc summationLoop.c -o summationLoop.o -fopenmp

int main(int argc, char *argv[]) {
    //Check Arg Input format
    if (atoi(argv[1]) == 0)
    {
        printf("Error Format or the number which are input is 0\n The format should be in integer : 1...N \n Inputted : %s", argv[0]);
        return EXIT_FAILURE;
    }

    //If 1 return 1
    if (atoi(argv[1]) == 1)
    {
        printf("The answer of sum of N is : 1 \n");
        return 0;
    }

    printf("--------------------------Start-Process--------------------------\n");

    //Create INPUT variable
    int INPUT = atoi(argv[1]);

    int i, sum = 0;
    int ThreadOutput[omp_get_max_threads()];

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        ThreadOutput[tid] = 0;

        #pragma omp for
        for (i = 1; i <= INPUT; i++)
        {
            printf("Processing Thread : <%d\n>", omp_get_thread_num() + 1);
            ThreadOutput[tid] += i;
        }
    }
    
    for (i = 0; i < omp_get_max_threads(); i++) {
        sum += ThreadOutput[i];
    }
        
    fprintf(stdout, "Result of sum using Threading is : <%d>\n", sum);
    printf("---------------------------End-Process---------------------------\n");
}
