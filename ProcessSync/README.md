# Thread Documentation

This file will explain how the I impliement Process Sync for Assignment 9: Process Synchronization

**Table**
- [Instruction](#Instruction)
- [Dining Philosophers Problem Explaination](#diningProblem)

> **Note:** There also .pdf file in directory `*./Document.pdf*`

  

## <a name="instruction"></a> Instruction

Describe how semaphores can handle the dining philosopher problem as well as implement the sample application by using POSIX APIs.

**What to submit:**

-   A document file: discuss the following topics.
-   What is the dining philosopher problem?
-   How to use semaphores to handle this problem? Provide the example.
-   A source code and example output. Please discuss why you get the output like that.

## <a name="DiningProblem"></a> Dining Problem Philosophers

**Dining Philosophers Problem** is a problem which use to demonstrate classic problem of synchronization.

Represent in 5 philosophers who sit on a dining table with 5 spoon for each person by having a bowl of noodle in the middle of the table. [link]()
![DiningPhilosophersImage](https://static.javatpoint.com/operating-system/images/os-dining-philosophers-problem.gif)
*<a name="Figure "></a>Figure 1*

Philosopher is demanded to think and eat he/she is hungry. There is a condition, philosopher can only eat if he/she can hold fork on the both hand. This mean if the fork is not aviable they cannot eat and go back to thinking.
## Usage