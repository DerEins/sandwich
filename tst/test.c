#include "../src/world.h"

//prendre comme cmd WIDTH=3 HEIGHT=4 make test_project
struct world world_init();

void world_disp(struct world w);

int main()
{
    struct world w;
    w = world_init();
    w.t[0] = 2;
    w.t[4] = 20;
    world_disp(w);
    return 0;
}