#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int *array = malloc(sizeof(int)*100);;
    free(array);
    array[0] = 0; // BOOM
	printf("you reached end of program\n");
	return 0;
}
