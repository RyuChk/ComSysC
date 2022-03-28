#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void strslice(const char * str, char * buffer, size_t start, size_t end)
{
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

int CheckBuffer(const char * buffer)
{
    if(atoi(buffer) == 0 && strcmp(buffer, "0") != 0) 
    {
        fprintf(stderr, "!error! Invalid Input Usage : %s <N>", buffer);
        return 1;
    }
    return 0;
}

int main()
{
    char INPUT[20];
    int pid, p[2], Length;// p[2] == pipe array

    if (pipe(p) < 0) //identicate error
    {
        fprintf(stderr, "Error Creating pipe");
        return EXIT_FAILURE;
    } //Retrun on error creating error process

    printf("Please enter Input for adding \n :: ");
    scanf("%19s", INPUT);
    Length = strlen(INPUT);
    printf("Char length inputed %d/20 \n", Length);

    //Child Process
    if ((pid = fork()) == 0) {
        close(p[0]);
        int result = 0;
        for (size_t i = 0; i < Length; i++)
        {
            char * currentIndex, * buffer;
            int Locator;
            strslice(INPUT, currentIndex, i, i);

            if (strcmp(currentIndex, "+") == 0)
            {
                strslice(INPUT, buffer, Locator, i-1);
                if (CheckBuffer(buffer) == 1)
                {
                    return EXIT_FAILURE;
                } else {
                    result += atoi(buffer);
                }
                Locator = i+1;
            } else if (i == Length - 1 || (strcmp(currentIndex, "=")) == 0){
                strslice(INPUT, buffer, Locator, i);
                if (CheckBuffer(buffer) == 1)
                {
                    return EXIT_FAILURE;
                } else {
                    result += atoi(buffer);
                }
            }
        }
        write(p[1], &result, sizeof(int));
        exit(0);
    } else if ((pid = fork()) < 0) {
        fprintf(stderr, "Error Create Child Process \n");
        return EXIT_FAILURE;
    } else if ((pid = fork()) > 0) {
        //Parent Process
        int ans = 0;
        wait(NULL); // wait for child process to finish
        printf("Child Process has finish calculate result \n");
        read(p[0], &ans, sizeof(int));
        printf("ANS is : %d \n", ans);
        return 0;
    }
}