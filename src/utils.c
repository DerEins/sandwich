#include "utils.h"
#include <stdlib.h>

int modulo(int x, int n)
{
    if (x < 0) {
        return n + (x % n);
    } else
        return x % n;
}

unsigned int chose_change(unsigned int nb_change)
{
    unsigned int r = rand();
    return r % nb_change;
}
