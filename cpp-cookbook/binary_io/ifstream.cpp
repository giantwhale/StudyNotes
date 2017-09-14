#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main() {

    vector<char> v(32);

    ifstream in("textfile");

    in.read(reinterpret_cast<char *>(&v[0]), sizeof(int)*32);
    if (in.eof()) {
        cout << "Reached the EOF" << endl;
    } else {
        cout << "Didn't reach the EOF" << endl;
    }

    cout << "size: " << v.size() << endl;
    int cnt = 0;
    for (auto it=v.begin(); it!=v.end(); ++it) {
        cout << cnt++ << ":\t" << *it << endl;
    }

    exit(0);
}