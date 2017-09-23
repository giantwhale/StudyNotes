#include <iostream>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::thread;


int main() {

    auto stime = std::chrono::system_clock::now();

    std::vector<thread> threads;

    for (size_t i=0; i<5; i++) {
        threads.push_back(thread([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(1527));
            cout << "Hello from thread " << i << ", thread id: " << std::this_thread::get_id() << endl;
        }));
    }

    std::for_each(threads.begin(), threads.end(), [](thread &th) {
        th.join();
    });

    cout << "Hello from main" << endl;

    auto etime = std::chrono::system_clock::now();
    auto dur = etime - stime;

    cout << "Running for " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() 
         << " milliseconds.\n";

    std::exit(0);
}
