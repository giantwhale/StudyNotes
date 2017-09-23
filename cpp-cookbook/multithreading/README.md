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

see [00_hello_thread.cpp](https://github.com/giantwhale/StudyNotes/blob/master/cpp-cookbook/multithreading/00_hello_thread.cpp) for a demo. 

### Creating thread using std::async 

`std::async` is included in header `#<future>`. On the surface, it is a syntax sugar that 
initialize a new thread and return a future whose value, when ready, will be set to the 
return value of the thread function. 

`std::async` is more than just a syntax sugar. Read Bartosz Milewski's blog post (Async
 Tasks in C++11: Not Quite There Yet)[https://bartoszmilewski.com/2011/10/10/async-tasks-in-c11-not-quite-there-yet/] for more details.

* For usage of promise and futures, see demo (02_promise_n_future.cpp)[https://github.com/giantwhale/StudyNotes/blob/master/cpp-cookbook/multithreading/02_promise_n_future.cpp]
* For usage of async as a syntax sugar, see demo (03_async.cpp)[https://github.com/giantwhale/StudyNotes/blob/master/cpp-cookbook/multithreading/03_async.cpp]

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

