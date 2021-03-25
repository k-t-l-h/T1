#include "check.h"

#include <stdio.h>
#include <string.h>

//наивная реализация с передаваемым числом
size_t check(int (*f)(int), int* arr, size_t arr_size) {
    size_t result = 0;

    if (arr == NULL || f == NULL) {
        return result;
    }

    for (int i = 0; i < arr_size; ++i) {
        if (f(arr[i])) {
            result++;
        }
    }
    return result;
}