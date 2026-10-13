# DSA Lab 06 — Stacks and Queues

This repository contains four C++ programs covering stack and queue implementations.

## Task 1 — Expression Conversion and Evaluation

`task1.cpp` implements an array-based stack to convert infix expressions to postfix and prefix, convert postfix expressions back to infix, and evaluate postfix and prefix expressions using `+`, `-`, `*`, `/`, and `^`.

**Limitation:** Operands are single characters, and evaluation supports single-digit numbers.

## Task 2 — Expression Validators

`task2.cpp` uses a custom array-based stack for:

- Checking whether `()`, `{}`, and `[]` are balanced and correctly nested.
- Checking nesting and matching of tags in simplified HTML/XML markup.

It reports mismatched tags, unclosed tags, unmatched closing tags, and a missing `>`. This is a simplified checker; self-closing tags such as `<br/>` are not supported.

## Task 3 — Print Server Request Handling

`task3.cpp` implements a dynamically resized circular queue. Each print request stores an ID, arrival time, and processing time. The queue grows when full and shrinks when it becomes sparse while preserving FIFO order.

The program displays queue state after enqueue and dequeue operations and calculates the average waiting time of processed requests.

## Task 4 — Waiting Room Management

`task4.cpp` implements a fixed-capacity, array-based circular queue for patients. It assigns unique IDs starting from 1, serves patients in first-come, first-served order, cancels all currently waiting patients, checks whether the queue is empty, and displays waiting IDs in sorted order.

Cancelling the waiting list does not reset the patient ID counter.

## Compile and Run

Compile and run each task separately from the repository folder:

```bash
g++ -std=c++11 task1.cpp -o task1 && ./task1
g++ -std=c++11 task2.cpp -o task2 && ./task2
g++ -std=c++11 task3.cpp -o task3 && ./task3
g++ -std=c++11 task4.cpp -o task4 && ./task4