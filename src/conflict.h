#ifndef __CONFLICT_H__
#define __CONFLICT_H__

/** Concrete struct storing the number of conflict for a cell and the number of conflict to process */
struct conflict {
    unsigned int nb_conflicts;
    unsigned int conflict_to_process;
};

/** Initialize an array of conflict */
void construct_t_conflicts(struct conflict* t);

/** Solve a conflict by returning a booleen. 
* If there is no conflict on the cell (i,j) return 1 (true), else return true or false with an equiprobability. 
* If the change is refused (false) then conflict_to_process =  conflict_to_process - 1*/
int solve_conflict(struct conflict t_conflicts[], unsigned int i, unsigned int j);

#endif // __CONFLICT_H__