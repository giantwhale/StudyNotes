#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using std::exit;
using std::cout;
using std::endl;

int main() {

    int fd;

    if ((fd = open("textfile", O_RDONLY)) < 0) {
        exit(1);
    }
    char buff;

    while (read(fd, (void*)&buff, sizeof(char)) > 0) {
        cout << buff << ' ';
    }
    cout << endl;

    close(fd);
    
    exit(0);
}