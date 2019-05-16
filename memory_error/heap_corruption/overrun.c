#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *arr;
    int i;
    size_t size_arr[] = {1, 2, 3, 5, 6, 7, 9, 10, 4, 128, 256, 512};

    // buffer overrun
    for (i = 0; i < 12; i++) {
        printf("%s:%d: OOB test size:%lu\n", __func__, __LINE__, size_arr[i]);
        arr = (char *)malloc(sizeof(char) * size_arr[i]);
        printf("%s:%d: after alloc. arr:%p\n", __func__, __LINE__, arr);
        arr[size_arr[i]] = 0;
        free(arr);
        printf("%s:%d: go to next\n", __func__, __LINE__);
    }
	printf("%s:%d: you reach end of program.\n", __func__, __LINE__);
}
