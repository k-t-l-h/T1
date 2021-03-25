#include "check_p.h"
#include <string.h>

//наивная реализация с передаваемым числом
size_t check_p(int (*f)(int), int* arr, size_t arr_size, int threads) {

    size_t result = 0;

    if (arr == NULL) {
        return result;
    }
    for (int i = 0; i < arr_size; ++i) {
        if (f(arr[i])) {
            result++;
        }
    }

    //TODO: разбить на несколько частей массив
    //TODO: для каждой части запустить поток
    //TODO: получить из потока число
    //TODO: число вернуть
    return result;
}