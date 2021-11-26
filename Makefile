WIDTH ?= 40
HEIGHT ?= 30
CFLAGS = -Wall -Wextra -std=c99 -ggdb3
SANDWICH_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)

all: project

test : test_queue 

project: src/project.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/world.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/rule.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/queue.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/project.c 
	gcc $(CFLAGS) $(SANDWICH_FLAGS) queue.o world.o rule.o project.o -o src/project

test_queue : tst/test_queue.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/queue.c 
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) tst/test_queue.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) -o test_queue queue.o test_queue.o

test_rule :
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/rule.c 
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 tst/test_rule.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/world.c
	gcc $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 -o test_rule rule.o world.o test_rule.o

test_world :tst/ test_world.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/rule.c 
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 tst/test.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/world.c
	gcc $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 -o test_world rule.o world.o test_world.o

clean:
	rm -f src/project test_* *.o vgcore*
