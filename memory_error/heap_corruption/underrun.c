#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *arr;
    char *ptr;
    int i;
    size_t offset[] = {1, 2, 3, 4};

    // buffer underrun
    for (i = 0; i < 4; i++) {
        printf("%s:%d: OOB(underrun) test. offset: %lu\n", __func__, __LINE__, offset[i]);
        arr = (char *)malloc(sizeof(char) * 256);
        printf("%s:%d: after alloc. arr:%p\n", __func__, __LINE__, arr);
		ptr = arr - offset[i];
        *ptr = 0;
        free(arr);
        // printf("%s:%d: after free\n", __func__, __LINE__);
        printf("%s:%d: go to next\n", __func__, __LINE__);
    }
	printf("%s:%d: you reach end of program.\n", __func__, __LINE__);
}
