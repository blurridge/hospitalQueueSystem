# hospitalQueueSystem

## Context
This is a program that automatically dequeues and adjusts priority depending on the given prio number. The program utilizes a 
doubly linked-list as the data structure for queue implementation. 

## How it works
1. Every time the program enqueues a new prescription, it is sorted according to priority.
2. Once max capacity is reached which is 5, it dequeues the front node and adjusts all priority numbers by decremention.
3. If a new prescription is inserted with a priority number that is less than 5, all priority numbers greater than it
undergoes incremention. It then dequeues the former tail.