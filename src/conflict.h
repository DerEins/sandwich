#ifndef __CONFLICT_H__
#define __CONFLICT_H__

struct conflict {
    unsigned int nb_conflicts;
    unsigned int conflict_to_process;
};

void construct_t_conflicts(struct conflict* t);

int solve_conflict(struct conflict t_conflicts[], unsigned int i, unsigned int j);

#endif // __CONFLICT_H__