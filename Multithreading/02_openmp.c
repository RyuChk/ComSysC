#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    #pragma omp parallel
    {
        printf("This is a parallel session.\n");       
        printf("Thread #%d.\n", omp_get_thread_num());
    }

    printf("This is from a sequential session.\n");

    return 0;
}