#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {

    FILE *f;
    if ((f = fopen("textfile", "r")) == NULL) {
        exit(1);
    }

    char buff[11];
    size_t n;

    while ((n=fread((void *)buff, 1, 10, f)) > 0) {
        buff[n] = '\0';
        cout << "Read " << n << " elems\n";
        cout << "# " << buff << ".\n";
    }

    exit(0);
}

