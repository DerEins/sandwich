WIDTH ?= 40
HEIGHT ?= 30
CFLAGS = -Wall -Wextra -std=c99 -ggdb3
SANDWICH_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)

all: project

project: src/project.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) src/project.c -o src/project

test_project: tst/test.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) tst/test.c -o test_project

test_queue : tst/test_queue.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/queue.c 
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) tst/test_queue.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) -o test_queue queue.o test_queue.o

clean:
	rm -f project test_project test_queue *.o vgcore*