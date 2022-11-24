# Usefull paths
SRC= src
TST= tst
DOC= doc

# SDL library path
SDL?= ./sdl.linux.x86-64

# World size
WIDTH ?= 40
HEIGHT ?= 30

# Compilations parameters
CC=gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb3
CPPFLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)

# LaTeX Doc compiler
TEX=pdflatex

all: project

test : test_world test_rule test_queue test_conflict
	./test_world
	./test_rule
	./test_queue
	./test_conflict | $(SDL) -f 100

*.o : *.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

project: $(SRC)/project.o $(SRC)/world.o $(SRC)/rule.o $(SRC)/queue.o $(SRC)/conflict.o $(SRC)/utils.o 
	$(CC) $^ -o $@

test_queue:  $(SRC)/queue.o $(TST)/test_queue.o
	$(CC) $^ -o $@

# Pour test{rule,world,conflict}, on est obligé de dépendre des .c qui doivent être recompilés à cause du
# changement de la taille du monde spécifique à ces tests.
test_rule : $(SRC)/rule.c $(SRC)/world.c $(SRC)/queue.c $(SRC)/utils.c $(SRC)/conflict.c $(TST)/test_rule.c $(TST)/utils_test.c
	$(CC) -DWIDTH=3 -DHEIGHT=3 $(CFLAGS) $^ -o $@

test_world : $(SRC)/rule.c $(SRC)/world.c $(SRC)/utils.c $(SRC)/conflict.c $(TST)/test_world.c $(TST)/utils_test.c
	$(CC) -DWIDTH=3 -DHEIGHT=3 $(CFLAGS) $^ -o $@

test_conflict : $(SRC)/rule.c $(SRC)/world.c $(SRC)/queue.c $(SRC)/utils.c $(SRC)/conflict.c $(TST)/test_conflict.c $(TST)/utils_test.c
	$(CC) -DWIDTH=3 -DHEIGHT=3 $(CFLAGS) $^ -o $@

doc : $(DOC)/report.tex
	cd $(DOC) && $(TEX) report.tex && $(TEX) report.tex && rm -R *.aux *.log *.toc *.out

clean:
	rm -f project test_* *.o **/*.o vgcore* animation 
	cd $(DOC) && rm -f *.aux *.log *.toc *.out
