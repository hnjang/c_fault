/* Code by ephemient
 * Please refer to ephemient's answer on below S.O. page
 *  - https://stackoverflow.com/questions/2069450/how-to-get-a-bus-error
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    FILE *f = tmpfile();
    int *m = mmap(0, 4, PROT_WRITE, MAP_PRIVATE, fileno(f), 0);
    printf("%s:%d: write 0 to m(%p)\n", __func__, __LINE__, m);
    *m = 0;

    printf("%s:%d: you reach end of program.\n", __func__, __LINE__);
}
