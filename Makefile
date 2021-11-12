WIDTH ?= 40
HEIGHT ?= 30
CFLAGS = -Wall -Wextra -std=c99 -g3
SANDWICH_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)

all: project

project: src/project.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) src/project.c -o project

test_project: tst/test.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/world.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) tst/test.c
	gcc -c $(CFLAGS) $(SANDWICH_FLAGS) src/rule.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) test.o world.o rule.o -o test_project

clean:
	rm -f project test_project *.o