#ifndef __RULE_H__
#define __RULE_H__

#include "world.h"

/** Abstract struct representing a rule for a cellular automaton */
struct rule;

/** Initializes the rules; is called at the start of the program; may
 * do nothing */
void rules_init();

/** Returns the number of rules */
unsigned int rules_count();

/** Returns the k-th rule */
struct rule *rule_get(unsigned int i);

/** Returns a boolean telling if the rule `r` matches at the cell
 * `(i,j)` of the world `w`. */
int rule_match(const struct world *w, const struct rule *r, unsigned int i,
               unsigned int j);

/** Returns the number of changes for a given rule. */
unsigned int rule_num_changes(const struct rule *r);

/** Return the change of index `idx` of the rule `r`, namely the color
 * of the modified cell. `idx` must be strictly less than
 * `rule_num_changes(r)`. */
unsigned int rule_change_to(const struct rule *r, unsigned int idx);

/** Return the displacement of index `idx` of the rule `r`, namely the
 * change in x (resp.y). `idx` must be strictly less than
 * `rule_num_changes(r)`. */
int rule_change_dx(const struct rule *r, unsigned int idx);
int rule_change_dy(const struct rule *r, unsigned int idx);

#endif // __RULE_H__
