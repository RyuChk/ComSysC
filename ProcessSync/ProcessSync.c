#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

//Dining Philosopher
//Define Constant Value

//Thinking = 2
//Eating = 1
//Hungry = 0

#define LEFT (pID + 4)%5 // getting left fork of each philosopher
#define RIGHT (pID + 1)%5 // getting right fork of each pholosopher

int state[5];

sem_t mutex;
sem_t S[5];

void test(int pID)
{
    //Check If fork is using or not
    if (state[pID] == 1 && state[LEFT] != 1 && state[RIGHT] != 1) {
        state[pID] = 1;
 
        sleep(2);
 
        printf("Philosopher %d takes fork %d and %d\n",
                      pID + 1, LEFT + 1, pID + 1);
 
        printf("Philosopher %d is Eating\n", pID + 1);
 
        sem_post(&S[pID]);
    }
}

void ReturnFork(int pID)
{
 
    sem_wait(&mutex);
 
    // Set Thinking State
    state[pID] = 2;
 
    printf("Philosopher %d putting fork %d and %d down\n", pID + 1, LEFT + 1, pID + 1);
    printf("Philosopher %d is thinking\n", pID + 1);
 
    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void CheckFork(int pID)
{
 
    sem_wait(&mutex);
 
    // state that hungry
    state[pID] = 1;
 
    printf("Philosopher %d is Hungry\n", pID + 1);
 
    // Check if Fork Aviable
    test(pID);
 
    sem_post(&mutex);
 
    // if unable to eat wait to be signalled
    sem_wait(&S[pID]);

    sleep(1);
}

void* philoFunction (void * id)
{
    while (1)
    {
        int * philoId = id;
        sleep(1);
        CheckFork(*philoId);
        sleep(0);
        ReturnFork(*philoId);
    }
}

int main(int argc, char *argv[] )
{
    int Phi_i[5] = {0,1,2,3,4};

    pthread_t ThreadId[5];
    //Create pThread
    for (int i = 0; i < 5; i++){
        pthread_create(&ThreadId[i], NULL,philoFunction, &Phi_i[i]);
    }

    //Create pThread
    for (int i = 0; i < 5; i++){
        pthread_join(ThreadId[i], NULL);
    }
    return 0;
}

//References
//https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/#:~:text=The%20Dining%20Philosopher%20Problem%20%E2%80%93%20The,two%20chopsticks%20adjacent%20to%20him.