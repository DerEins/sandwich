#include "../src/world.h"
#include "../src/rule.h"
#include "../src/queue.h"
#include <stdio.h>

struct world world_init();

void world_disp(struct world w);

int main()
{
    struct world w;
    w = world_init();
    return 0;
}