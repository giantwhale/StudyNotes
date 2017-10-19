
Hello Thread
------------------------------------------

Start a new thread:

```c++
#include <iostream>
#include <thread>

int main() {
    std::thread th([]() { // using lambda syntax
        std::cout << "Hello thread!" << std::endl;
    })
    std::cout << "Hello main" << std::endl;
}
```


Shared Memory
------------------------------------------

Shared memory is one of the most effective way to share data in a multithread program. 

Each thread has its **own stack**. Whatever argument was passed to the thread during thread creating, it was copied to the thread's own stack. 


