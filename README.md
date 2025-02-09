# Philosophers - 42 Project

![Philosophers](https://img.shields.io/badge/status-completed-brightgreen)
![Language](https://img.shields.io/badge/language-C-blue)
![Grade](https://img.shields.io/badge/grade-100%2F100-brightgreen)

## Table of Contents

1. [Introduction](#introduction)
2. [Overview](#overview)
3. [Requirements](#requirements)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Rules](#rules)
7. [Implementation Details](#implementation-details)

---

## Introduction

The **Philosophers** project is a classic problem in computer science that simulates the dining philosophers problem. This problem is a well-known example in concurrent programming and synchronization. The goal is to prevent deadlocks and ensure that all philosophers can eat without starving.

This project is part of the 42 school curriculum and aims to teach students about threading, mutexes, and resource management in a multi-threaded environment.

---

## Overview

In this project, you will implement a solution to the dining philosophers problem using threads and mutexes. The program will simulate a number of philosophers sitting around a table, each with a fork on their left and right. Philosophers alternate between thinking and eating, but they need two forks to eat. The challenge is to ensure that no philosopher starves and that no deadlocks occur.

---

## Requirements

- The program must be written in **C**.
- The program must use **threads** and **mutexes**.
- The program must handle a variable number of philosophers and forks.
- The program must avoid deadlocks and ensure that no philosopher starves.
- The program must display the state of each philosopher in real-time.

---

## Installation

To compile the project, follow these steps:

1. Clone the repository:
   
   git clone git@github.com:Rpepi/philosopherss.git
   
2. Compile the program using make
3. 
   The executable philo will be generated.

## Usage
   
Run the program with the following command:

  ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_meals> 

<number_of_philosophers>: The number of philosophers (and forks).

<time_to_die>: The maximum time a philosopher can go without eating (in milliseconds).

<time_to_eat>: The time it takes for a philosopher to eat (in milliseconds).

<time_to_sleep>: The time a philosopher spends sleeping (in milliseconds).

[number_of_meals] (optional): The number of meals each philosopher must eat before the program ends.

Example:

./philo 5 800 200 200 7

This command will simulate 5 philosophers, with a time to die of 800ms, a time to eat of 200ms, a time to sleep of 200ms, and each philosopher will eat 7 meals.

## Rules
Each philosopher must eat a certain number of times (if specified).

No philosopher should starve.

No deadlocks should occur.

The program must display the state of each philosopher in real-time.

## Implementation Details
Threads: Each philosopher is represented by a thread.

Mutexes: Each fork is protected by a mutex to ensure that only one philosopher can hold it at a time.

Timing: The program uses usleep to simulate the time it takes for philosophers to eat, sleep, and think.

State Display: The program prints the state of each philosopher (e.g., "is eating", "is sleeping", "is thinking") in real-time.
