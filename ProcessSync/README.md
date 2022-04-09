
# Process Synchronization Documentation

This file will explain how the I implement Process Sync for Assignment 9: Process Synchronization

**Table**
- [Instruction](#Instruction)
- [Dining Philosophers Problem Explaination](#diningProblem)
- [Implimentation](#Implimentation)

> **Note:** The code is a reference from the website [geeksforgeeks](https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/#:~:text=The%20Dining%20Philosopher%20Problem%20%E2%80%93%20The,two%20chopsticks%20adjacent%20to%20him.).

  

## <a name="instruction"></a> Instruction

Describe how semaphores can handle the dining philosopher problem as well as implement the sample application by using POSIX APIs.

**What to submit:**

-   A document file: discuss the following topics.
-   What is the dining philosopher problem?
-   How do use semaphores to handle this problem? Provide an example.
-   A source code and example output. Please discuss why you get the output like that.

## <a name="DiningProblem"></a> Dining Problem 
Philosophers

**Dining Philosophers Problem** is a problem which use to demonstrate the classic problem of synchronization.

Represent in 5 philosophers who sit on a dining table with 5 spoon for each person by having a bowl of noodle in the middle of the table. [link]()
![DiningPhilosophersImage](https://static.javatpoint.com/operating-system/images/os-dining-philosophers-problem.gif)
*<a name="Figure "></a>Figure 1*

The philosopher is demanded to think and eat he/she is hungry. There is a condition, a philosopher can only eat if he/she can hold a fork in both hands. This means if the fork is not available they cannot eat and go back to thinking.

## <a name="Implimentation"></a>Implimentation

### Create Thread

First I create a Thread for every philosopher, in this case, 5, by using `pthread_create()` function.

	//Create Thread
    for (int  i  =  0; i  <  5; i++){
	pthread_create(&ThreadId[i], NULL,philoFunction, &Phi_i[i]);
	}
	//Join Thread
	for (int  i  =  0; i  <  5; i++){
	pthread_join(ThreadId[i], NULL);
	}

### Dining Philosopher Implementation
As we create a thread for each `i` philosopher, They will all want to eat so all their state is hungry. But first, we need to check if the fork is available or not.

#### 1. Check Fork Function

We need to check if the fork on the left and right of the philosopher is available or not. In case the fork is available, a philosopher is allowed to eat otherwise, a philosopher needs to go back to thinking.

By using `sem_wait()` function we create a lock to our process to make the current thread safely enter the critical section.

As we now safely enter the critical section we can check if the fork is available or not.

#### 2. Test Fork Function
Now we check if the state of current is `1` which is **Hungry State** or the current philosopher is in another state. We also need to check if the **LEFT** and **RIGHT** fork is available

Example :

    if (state[pID] ==  1  &&  state[LEFT] !=  1  &&  state[RIGHT] !=  1) 
    {
        state[pID] =  1;
    }

After we check we can eat the food

#### 3. Returning Fork Function

Now we need to return the fork state to 0 if the state is finished and also set the state of the current philosopher to thinking.