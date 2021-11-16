#include "../src/world.h"
#include "../src/rule.h"
#include "../src/queue.h"
#include <stdio.h>
#define M 5 //le nombre d'images generees

//prendre comme cmd WIDTH=3 HEIGHT=4 make test_project
struct world world_init();

void world_disp(struct world w);

int main()
{
    struct world w;
    w = world_init();
    /**w.t[0] = 2;
    w.t[4] = 20;
    world_disp(w);
    rules_init();
    printf("%d %d\n", WIDTH, HEIGHT);
    for(int i=0; i<M; i++)
    {
        q = queue_init();
        for(int k=0; k<HEIGHT; k++)
        {
            for(int l=0; l<WIDTH, l++)
            {
                for(int j=0, j<rules_count(), j++)
                {
                    if(rule_match(w, r, k, l))
                    {
                        queue_append(q, r, k, l);
                    }
                }
            }
        } */
    }
    return 0;
}