#include <iostream>
#include <thread>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
    vector<thread> v;
    for (int i=0; i<10; i++) {
        // copy constructor in thread is disabled.
        v.push_back(thread([i]() {
            cout << "hello world " << i << endl;
        }));
    }

    cout << "hello main" << endl;

    for_each(v.begin(), v.end(), [](thread &th) {
        th.join();
    });

    exit(0);
}
