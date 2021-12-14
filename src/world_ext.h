#ifndef __WORLD_EXT_H__
#define __WORLD_EXT_H__

#include "conflict.h"
#include "rule.h"
#include "world.h"

struct world world_init(char opt, int seed);

void world_disp(struct world* w);

void world_apply_rule(struct world* w, struct rule* r, int i, int j, unsigned int idx_change, struct conflict t_conflicts[]);

#endif // __WORLD_EXT_H__
