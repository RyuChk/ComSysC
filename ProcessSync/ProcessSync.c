#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>


int main(int argc, char *argv[] )
{
    int Pid[10];

    //Create Process P1
    if((Pid[0] = fork()) == 0)
    {
        
    }
    return 0;
}