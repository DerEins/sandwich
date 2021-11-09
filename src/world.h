#ifndef __WORLD_H__
#define __WORLD_H__

/** The width of a 2D world (i.e the number of columns) */
#ifndef WIDTH
  #define WIDTH 40
#endif

/** The height of a 2D world (i.e the number of lines) */
#ifndef HEIGHT
  #define HEIGHT 30
#endif

/** Concrete struct representing a world for a cellular automaton */
struct world {
  unsigned int t[WIDTH*HEIGHT];
};

#endif // __WORLD_H__
