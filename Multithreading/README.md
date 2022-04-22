# Thread-OpenMP Document

This file will explain how the I implement program calculate sum of N using openMP which are rewrite from assignment 8 : Threads.

>  **Note:** There also .pdf file in directory `*./Document.pdf*`

**Table**
- [Instruction](#Instruction)
- [Usage](#usage)
	- [Multi-threading (Semaphore)](#m-usage)
	- [Thread rewrite using openMP](#t-usage)
- [Dining Philosophers Problem Explanation](#diningProblem)
- [Implementation](#Implementation)
	- [Multi-threading (Semaphore)](#Multi-threading)
	- [Thread rewrite using openMP](#openMP)
  

## <a name="instruction"></a> Instruction


1.  Task 1: edit 01_race_condition.c (but keep line 18-20 the same) so that there is no more the race condition.
2.  Task 2: if you're using VM, assign 2 processors or more to your VM. Then, implement Assignment #8 again by using OpenMP APIs.

## <a name="usage"></a> Usage

**Table**
- [Multi-threading (Semaphore)](#m-usage)
- [Thread rewrite using openMP](#t-usage)

### 1.Multi-threading <a name="m-usage"></a>
#### Argument

    ./<File-Name> <Sum of N>
    
Example :

    linux~: ./RaceCondition
    OK! cnt is [2000000]

Output:

	OK! cnt is [2000000]

![Multi-ThreadingOutputPicture](https://github.com/RyuChk/ComSysC/blob/main/Multithreading/img/RaceConditionOuput.jpg)
    
### 2. Thread <a name="t-usage"></a>
#### Argument
 
    ./<File-Name> <Sum of N>

>  **Note :** Number of Thread must be ( N >= 2 )
  
Example :

    linux~: ./Thread_Rerun 30

    Sum = 465

Output :

    linux~: ./Thread_Rerun 30
    Iteration 1 is processed by thread 1
    Iteration 2 is processed by thread 1
    Iteration 3 is processed by thread 1
    Iteration 4 is processed by thread 1
    Iteration 5 is processed by thread 1
    Iteration 6 is processed by thread 2
    Iteration 7 is processed by thread 2
    Iteration 8 is processed by thread 2
    Iteration 9 is processed by thread 2
    Iteration 10 is processed by thread 2
    Result of sum using Threading is : <55>
    ---------------------------End-Process---------------------------

![ThreadOutputPicture](https://github.com/RyuChk/ComSysC/blob/main/Multithreading/img/ThreadOutput.jpg)

## <a name="Implementation"></a> Implementation
**Link :**
- [Multi-threading (Semaphore)](#Multi-threading)
- [Thread rewrite using openMP](#openMP)
  
### <a name="Multi-threading"></a> Multi-threading ( Using semaphore )
#### 1. Initialize
in-order to use semaphore we need to declare **mutex** which is type of `sem_t`

	sem_t Mutex;

After declare **Mutex** we will use it to init semaphore address point to Mutex using `sem_init()`

	sem_init(&Mutex, 0, 1) //  **int sem_init(sem_t ***_sem_**, int** _pshared_**, unsigned int** _value_**);**

#### 2.Implement into the code.
by using `sem_wait` and `sem_post` I can create lock on critical section where the share data will be written so no other thread can interfere including reading the data.

**sem_wait**
`sem_wait` is function that will hold the function and wait until **mutex** become zero. As the wait is finish `sem_wait` will add 1 to **mutex** which identicated that there is process running so other thread need to be waited

**sem_post**
qsem_postq will deduct 1 from **mutex** identicated thread is finish calculate or running in critical section

Example :

	void * Count(void * a)
	{
		int i, tmp;
		sem_wait(&mutex); // check aviable before enter critical section
		
		for(i = 0; i < NITER; i++)
		{
			tmp = cnt; /* copy the global cnt locally */
			tmp = tmp+1; /* increment the local copy */
			cnt = tmp; /* store the local value into the global cnt */
		}
		
		sem_post(&mutex); // Finish calculate exit critical section
	}

---

### <a name="openMP"></a> Thread Rewrite using openMP

#### 1. What is openMP `<omp.h>`
OpenMP api will create **Thread** , `pthread_create()`, and **join Thread** ,`pthread_join()`, by itself. Also openMP will automatically using different thread to calculate for us using only one for loop

Exmaple :

	  
	#pragma  omp  parallel
	{
		int tid = omp_get_thread_num(); //Get Maximum Thread device can handle
		ThreadOutput[tid] = 0;

		#pragma  omp  summation
		for (i = 1; i <= INPUT; i++)
			{
				printf("Processing Thread : <%d\n>", omp_get_thread_num() + 1);
				ThreadOutput[tid] += i; // adding 1 to selected thread output
			}
	}

#### 2. Initialize openMP
Delare Which part of code we want to run in parallel using openMP.

  	#pragma  omp  parallel
	{
		//Content
	}

In this case, inside the function I create a array with size of `N_Thread` which will hold the sum of individual thread output. etc `Thread[1] sum = 1`

	#pragma  omp  parallel
	{
		int tid = omp_get_thread_num(); //Get Maximum Thread device can handle
		ThreadOutput[tid] = 0;
	}


#### 3. Loop for adding number:
I create for loop to literate from 1 to N which openMP will automatically decide which thread will take care on calculation part.

	#pragma  omp  parallel
	{
		int tid = omp_get_thread_num(); //Get Maximum Thread device can handle
		thread_sum[tid] = 0;

		#pragma  omp  summation
		for (i = 1; i <= INPUT; i++)
			{
				printf("Processing Thread : <%d\n>", omp_get_thread_num() + 1);
				ThreadOutput[tid] += i; // adding 1 to selected thread output
			}
	}

and after the loop is finish I will add all the thread result and print the final result.

	for (i = 0; i < omp_get_max_threads(); i++) {
		sum += ThreadOutput[i];
	}

	fprintf(stdout, "Result of sum using Threading is : <%d>\n", sum);
	printf("---------------------------End-Process---------------------------\n");

