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
has similar effect [link](https://docs.oracle.com/javase/tutorial/essential/concurrency/syncmeth.html). 
(In java, each method has its own mutex.)

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


### Condition Variable

A condition variable (referred to as `cond` in the code below) allows communication
between a **producer** and one or multiple **consumers**. The producer can use either
`notify_one()`, or `notify_all()` to wake up the consumer. If no consumer is 
`wait()`ing, the notification is ignored. 

Since the condition variable doesn't carray any useful information, we typically 

```c++
// Producer
{
    lock_guard(mtx); 
    v = true;  // the shared state
}
cond.notify_one();
```


First consumer implementation: the consumer implementation below isn't thread safe, 
because the loop body isn't atomic. Consider the following sequence of execution:

* consumer checks `v` and found it is false
* producer sets `v` to true
* producer calls `notify()`, which is ignore by the consumer
* consumer waits forever.

```c++
// Consumer
unique_lock lck(mtx);
for(;;) {
    if (v) break;   // check if the state has been set by the producer
    cond.wait(lck)  // unlock the lock, allowing the producer to set the state
                    // variable v, and wait for the producer for notification.
}
v = false; // reset v
```

To avoid the data race condition above, the C++11 standard allows an alternative
way to call `wait()`:

```c++
unique_lock lck(mtx);
cond.wait(lck, [&v]{return v;});
v = false;
```

#### Blocking Messages Queue
Let's use condition_variable to implement a blocking message queue that is thread safe.

```c++
#include <deque>
#include <condition_variable>

template<class T>
class MsgQueue {
    std::deque<T> _queue;
    std::condition_variable _cond;
    std::mutex _mutex;
public:
    void send(T && msg) {
        // will need to notify the receiver that
        // the message is ready
        {
            std::lock_guard<std::mutex> lck(_mutex);
            _queue.push_front(std::move(msg));
        }
        _cond.notify_one();
    }
    T recv() {
        // if queue is empty, wait for the msg to be ready
        std::unique_lock<std::mutex> lck(_mutex);
        // wake up when the queue is not empty
        _cond.wait(lck, [this]{ return !_queue.empty(); });
        T msg = std::move(_queue.back());
        _queue.pop_back();
        return msg; 
    }
};
```


