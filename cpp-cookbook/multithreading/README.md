C++ Multithreading
===========================================


Thread Basics
-------------------------------------------
Each thread has its **own stack**. 


Difference between threads and processes:

* threads (of the same process) run in a shared memory space, while processes run in 
  separate memory spaces.

### References

* Anthony Williams (the author of c++11 compatible library `just::thread`), C++ Concurrency in Action. 
* Maurice Herlihy, Nir Shavit, The Art of Multiprocessor Programming. (More theoretical)

### Debugger

So far the only non-commercial debugger I can find is [Helgrind](http://valgrind.org/docs/manual/hg-manual.html)

corensic has a commericla debugger **Jinx**.


Hello Thread
-------------------------------------------
In C++11, thread can be initialized in a variety of ways:

### Creating thread using std::thread

see [00_hello_thread.cpp](https://github.com/giantwhale/StudyNotes/blob/master/cpp-cookbook/multithreading/00_hello_thread.cpp) for a demo. 

### Creating thread using std::async 

`std::async` is included in header `#<future>`. On the surface, it is a syntax sugar that 
initialize a new thread and return a future whose value, when ready, will be set to the 
return value of the thread function. 

`std::async` is more than just a syntax sugar. Read Bartosz Milewski's blog post [Async
 Tasks in C++11: Not Quite There Yet](https://bartoszmilewski.com/2011/10/10/async-tasks-in-c11-not-quite-there-yet/) for more details.

* For usage of promise and futures, see demo [02_promise_n_future.cpp](https://github.com/giantwhale/StudyNotes/blob/master/cpp-cookbook/multithreading/02_promise_n_future.cpp)
* For usage of async as a syntax sugar, see demo [03_async.cpp](https://github.com/giantwhale/StudyNotes/blob/master/cpp-cookbook/multithreading/03_async.cpp)

Shared Memory
-------------------------------------------
Shared memory is one of the most effective way to share data in a multithread program.
Although it is recommended to use move-and-swap technique over shared memory to pass data 
among threads, sometimes using shared_memory is unavoidable.

**For shared_memory to be safe, we need to synchronize the work flow.**

### Mutex and Monitor

**Monitor** is data structure that helps synchronize instructions in a multithreading 
environment. The code snippet below shows the C++ implementation. In Java, the keyword `synchronized` 
has similar effect [link](https://docs.oracle.com/javase/tutorial/essential/concurrency/syncmeth.html). (In java, each method has its own mutex.)

```c++
#include <mutex>
class Monitor {
    std::mutex _mutex;
public:
    void synchronized_function(int input) {
        std::lock_guard<std::mutex> lock(_mutex);
        // ...
    }
};
```


### Conditional Variable

A conditional variable (referred to as `cond` in the code below) allows communication
between a **producer** and one or multiple **consumers**. The producer can use either
`notify_one()`, or `notify_all()` to wake up the consumer. If no consumer is 
`wait()`ing for the notification, it gets thrown away.

```c++
// Producer
{
    lock_guard(mtx);
    v = true;  // the shared variable
}
cond.notify_one();
```



```c++
// Consumer
unique_lock lck(mtx);
while (1) {
    if (v) break;   // check if the state has been set by the producer
    cond.wait(lck)  // unlock the lock, allowing the producer to set the state
                    // variable v, and wait for the producer for notification.
}
```