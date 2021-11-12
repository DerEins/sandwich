#include <stdio.h>
#include "world.h"

/** */
int get_cell(struct world w, unsigned int i, unsigned int j)
{

    return 0;
}

/** Create a new world with value 0 (and I want random value)*/
struct world world_init()
{   
    struct world w;
    for(int i=0; i<WIDTH*HEIGHT; i++)
         {
             w.t[i]=0;
         }
    return w;
}

/** display a world according to the rules specified*/
void world_disp(struct world w)
{
    printf("#\n");
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        if((i%WIDTH) == (WIDTH-1))
        {
            printf("%d \n", w.t[i]);
        }
        else
            printf("%d ", w.t[i]);
    }    
}
