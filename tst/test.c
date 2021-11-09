#include "../src/world.h"
#include "../src/world.c"

int main(int argc, char **argv)
{
    struct world w = init_world();
    w.t[4]=20;
    world_disp(w);
    return 0;
}