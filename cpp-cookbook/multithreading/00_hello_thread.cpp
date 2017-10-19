#include <iostream>
#include <thread>
#include <cstdlib>
#include <chrono>

using std::cout;
using std::endl;

int main() {
    std::thread th([]() {
        cout << "Hello thread" << endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Hello main" << endl;
    th.join();

    std::exit(0);
}
