C++ Multithreading
===========================================

Thread Basics
-------------------------------------------
Each thread has its **own stack**. 


Difference between threads and processes:

* threads (of the same process) run in a shared memory space, while processes run in 
  separate memory spaces.


Hello Thread
-------------------------------------------
In C++11, thread can be initialized in a variety of ways:

### Creating thread using std::thread

see (00_hello_thread.cpp)[https://github.com/giantwhale/StudyNotes/blob/master/cpp-cookbook/multithreading/00_hello_thread.cpp] for a demo. 



Shared Memory
-------------------------------------------
Shared memory is one of the most effective way to share data in a multithread program.
Although it is recommended to use move-and-swap technique over shared memory to pass data 
among threads, sometimes using shared_memory is unavoidable.

* Using shared memory is safe as long as 

**Monitor** is data structure that helps synchronize instructions in a multithreading 
environment. 

```c++
#include <mutex>
class Monitor {
public:
    void synchronized_function(int input) {
        std::lock_guard<std::mutex> lock;
        // ...
    }
};
```

