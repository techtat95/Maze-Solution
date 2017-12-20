CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
#PROFFLAG = -pg
#DEFINES = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
VALGRIND = valgrind --tool=memcheck --leak-check=full
VALGRIND += --verbose --track-origins=yes  --log-file=
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(DEFINES)
#OBJS = pa10.o 

all: pa10

pa10: pa10.o maze.o path.o solver.o list.o mazehelper.o
	$(GCC) pa10.o maze.o path.o solver.o list.o mazehelper.o -o pa10 -lm

pa10.o: pa10.c maze.h path.h solver.h #paths.h
	$(GCC) -c pa10.c -o pa10.o

list.o: list.c list.h
	$(GCC) -c list.c -o list.o

mazehelper.o: mazehelper.c mazehelper.h
	$(GCC) -c mazehelper.c mazehelper.h  

maze.o: maze.c maze.h
	$(GCC) -c maze.c -o maze.o

path.o: path.c path.h mazehelper.h
	$(GCC) -c path.c -o path.o

solver.o: solver.c solver.h path.h mazehelper.h list.h
	$(GCC) -c solver.c -o solver.o

test: pa10
	for n in 1 2 3 ; do \
	  echo "Testing Maze #$$n" ; \
	./pa10 inputs/maze$$n inputs/path$$n ; \
	done

clean: 
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa10
	/bin/rm -f vallog
	/bin/rm -f inputs/path*
	/bin/rm -f memory

memory: pa10
	$(VALGRIND)vallog ./pa10 inputs/maze1 inputs/path1


