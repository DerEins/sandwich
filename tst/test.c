#include "../src/world.h"
#include "../src/world_ext.h" 

//prendre comme cmd WIDTH=3 HEIGHT=4 make test_project
int main(int argc, char **argv)
{
    struct world w;
    w = world_init();
    w.t[0]=2;
    w.t[4]=20;
    world_disp(w);
    return 0;
}