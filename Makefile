WIDTH ?= 40
HEIGHT ?= 30
CFLAGS = -Wall -Wextra -std=c99 -ggdb3
SANDWICH_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)

all: project

test : test_queue test_rule test_world test_conflict

project: src/project.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/world.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/rule.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/queue.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/utils.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/project.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/conflict.c  
	gcc $(CFLAGS) $(SANDWICH_FLAGS) queue.o world.o rule.o project.o utils.o conflict.o -o project

test_queue : tst/test_queue.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/queue.c 
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) tst/test_queue.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) -o test_queue queue.o test_queue.o

test_rule :
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/rule.c 
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 tst/test_rule.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/world.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/queue.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/utils.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 src/conflict.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 tst/utils_test.c
	gcc $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 -o test_rule queue.o rule.o world.o utils.o test_rule.o utils_test.o conflict.o

test_world :
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/rule.c 
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 tst/test_world.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/world.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 src/utils.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 tst/utils_test.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 src/conflict.c
	gcc $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 -o test_world rule.o world.o utils.o test_world.o conflict.o utils_test.o

test_conflict :
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 src/rule.c 
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 tst/test_conflict.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 src/world.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 src/utils.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 src/queue.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 src/conflict.c
	gcc -c $(CFLAGS) -DWIDTH=3 -DHEIGHT=3 tst/utils_test.c
	gcc $(CFLAGS) -DWIDTH=3 -DHEIGHT=5 -o test_conflict queue.o rule.o world.o utils.o conflict.o test_conflict.o utils_test.o

clean:
	rm -f project test_* *.o vgcore* animation
