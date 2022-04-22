# Thread Documentation
This file will explain how the I implement Thread for assignment 8 : Threads.

> **Note:** There also .pdf file in directory `*./Document.pdf*`

## Instruction
Let write a multithreaded program in POSIX to calculate the sum(n) if sum(n) = 1 + 2 + 3 + ... + n, where n is a positive integer. The program must be parsed with 2 inputs: m and n, where m is 2 as the number of calculating threads and n is for sum(n).

How the calculating threads work : 
-   Assume m = 2 and n = 10
-   Thread 1: calculate sum1 = 1 + 2 + 3 + 4 + 5
-   Thread 2: calculate sum2 = 6 + 7 + 8 + 9 + 10
-   Main thread: calculate sum = sum1 + sum2 and display the result.

**Extra Credit ( 5 point )**
-   m can be any positive integer, and m >= 2.

## Usage
#### Argument

	    ./ThreadOutput.out <Sum of N> <Number of Thread>

> **Note :** Number of Thread must be ( N >= 2 )

Example : 

        ./ThreadOutput.out 30 10

Output :

    --------------------------Start-Process--------------------------
    CALCULATE SUMATION OF : 30
    WITH <4> THREADS
    Thread 0 Adding from : 1, 8
    Thread 1 Adding from : 8, 16
    Thread 2 Adding from : 16, 24
    Thread 3 Adding from : 24, 31
    Result of sum using Threading is : <465>
    ---------------------------End-Process---------------------------
## Implimentation

### 1. Ques
Create Array of Que with size of **Thread(n)** which identify each thread start, stop and result.

    struct  ThreadInfo
    {
    int  start,stop,result;
    };
    struct Que[N_Thread]
The ques is start from **1** to **( Sum of (n) / Thread )**
Exmaple : 

    int  segment  =  ceil((float)INPUT/N_Thread);

### 2. Thread
Using Loop to create **Thread(N)** by using `pthread_create(ThreadId)`. Then using `pthread_join(ThreadId)` to wait for thread to finish calculate.

> **Note :** Thread id can be recycle

Each thread will calculate the number from specify starting point to stoping point. Then write the result into struct.

Example : 

    for (int  i  = (*Input).start; i < (*Input).stop; i++){
    (*Input).result  +=  i;
    }
    
### 3. Result
Lastly looping through Ques array and sum the result from each thread to print our solution.