#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
    char INPUT[20];
    int pid;
    printf("Please enter Input for adding \n :: ");
    scanf("%19s", INPUT);
    if ((pid = fork()) == 0) {
        printf("I'm a child !!! %d ----- <> ----- ", pid);
        return EXIT_SUCCESS;
    }

    printf("I'm not a CHild I'm a parent ;; %d ", pid);
    return 0;
}

int add(int a, int b)
{
    int result = a + b;
    return result;
}