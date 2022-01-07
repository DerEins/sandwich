#ifndef __WORLD_EXT_H__
#define __WORLD_EXT_H__

#include "conflict.h"
#include "rule.h"
#include "world.h"

/** Initialize a 2D world */
struct world world_init(char opt, int seed);

/** Display a 2D world adapted for sdl expected input*/
void world_disp(struct world* w);

/** Apply a change of state for the cell (i,j) in the world (with gestion of conflict) */
void world_apply_rule(struct world* w, struct rule* r, int i, int j, unsigned int idx_change, struct conflict t_conflicts[]);

#endif // __WORLD_EXT_H__
