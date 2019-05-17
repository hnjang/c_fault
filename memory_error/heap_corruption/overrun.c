#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buffer_overrun_test(size_t size) {
    char *arr;
    printf("%s:%d: OOB test size:%lu\n", __func__, __LINE__, size);
    arr = (char *)malloc(sizeof(char) * size);
    if (arr == NULL) {
        printf("%s:%d: malloc() failed. arr:%p\n", __func__, __LINE__, arr);
        return;
    }
    printf("%s:%d: after alloc. arr:%p\n", __func__, __LINE__, arr);
    arr[size] = 0;
    free(arr);
}

void run_overrun_tc() {
    int i;
    size_t size_arr[] = {1, 2, 3, 5, 6, 7, 9, 10, 4, 128, 256, 512};
    for (i = 0; i < 12; i++) {
        buffer_overrun_test(size_arr[i]);
        printf("%s:%d: go to next\n", __func__, __LINE__);
    }
}

int main(int argc, char *argv[]) {
    size_t size;
    if (argc <= 1) {
        run_overrun_tc();
    } else {
        size = atoi(argv[1]);
        printf("%s:%d: your input is %lu\n", __func__, __LINE__, size);
        buffer_overrun_test(size);
    }
    printf("%s:%d: end of program.\n", __func__, __LINE__);
}
