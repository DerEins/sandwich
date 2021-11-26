#ifndef __UTILS_H__
#define __UTILS_H__

#include "world.h"

enum state {
    EMPTY = 0,
    SAND = 16777215,
    GRASS = 65280,
    RANDOM_COLOR = 4294967295,
    STATE_COUNT = 4,
    FIRST_STATE = EMPTY
};

#endif // __UTILS_H__