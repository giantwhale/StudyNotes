# Read/Write Binary Files

## Endianness

Todo


## Read Binary Files

There are many options to read binary files in C/C++:

* The standard C function `read`.
* The standard C function `fread`
* C++ `ifstream`, very similar to `fread`.
* Memory mapping.

We dicuss each in details

### The UNIX `read()`

The function is available in the unix header file `<unistd.h>`. To open/create files, we also need to use functions from `<fcntl.h>`.


```c++

#include <fcntl.h>

int open(const char* path, int oflag, ... /* mode_t mode */ ); 
// Most oftenly used modes are O_RDONLY, O_WRONLY, O_RDWR, O_APPEND, O_CREAT
// Refer to APUE for a full list of modes.

int create(const char *path, mode_t mode);

#include <unistd.h>

int close(int fd);

off_t lseek(int fd, off_t offset, int whence);
// whence can be SEEK_SET, SEEK_CUR, or SEEK_END


// all functions return -1 on error

```

