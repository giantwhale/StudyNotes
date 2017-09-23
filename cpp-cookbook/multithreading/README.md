C++ Multithreading
===========================================

Thread Basics
-------------------------------------------
Each thread has its **own stack**. 


Difference between threads and processes:

* threads (of the same process) run in a shared memory space, while processes run in 
  separate memory spaces.



Shared Memory
-------------------------------------------
Shared memory is one of the most effective way to share data in a multithread program.
Although it is recommended to use move-and-swap technique over shared memory to pass data 
among threads, sometimes using shared_memory is unavoidable.
