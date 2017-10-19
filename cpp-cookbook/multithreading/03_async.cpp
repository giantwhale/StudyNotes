/* 
std::async is not just a syntax sugar for promise/future. Please read
Bartosz Milewski's blog post Async Tasks in C++11: Not Quite There Yet 
for more details:

https://bartoszmilewski.com/2011/10/10/async-tasks-in-c11-not-quite-there-yet/
*/

#include <iostream>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>
#include <future>

using std::cout;
using std::endl;
using std::thread;

int thFunc() {
    return 527;
}

int main() {
    // It is recommended to always use std::launch::async instead of the default
    // std::launch::async | std::launch::deferred
    // auto ftr = std::async(std::launch::async, &thFunc);
    auto ftr = std::async(&thFunc);
    int val = ftr.get();
    cout << "Get Value from the thread via promise/future: " << val << endl;
    std::exit(0);
}
