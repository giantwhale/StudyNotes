#include <stdlib.h>

float *compute(int size) {
    int *array;
    array = malloc(sizeof(int) * size);
    int i;
    for (i=0; i<size; i++) {
        array[i] = i;
    }
    return array;
}
