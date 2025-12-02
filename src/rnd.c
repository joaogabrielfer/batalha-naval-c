#include <stdlib.h>
#include <time.h>
#include "rnd.h"

void init_random() {
    srand(time(NULL));
}

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}
