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


int main() {
    std::promise<int> prms;
    std::future<int> ftr = prms.get_future();

    thread th([](std::promise<int> &prms) {
        prms.set_value(527);
    }, std::ref(prms));

    int val = ftr.get();
    cout << "Get Value from the thread via promise/future: " << val << endl;

    std::exit(0);
}
