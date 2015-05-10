NAME = riemann
FILENAME = data.dat
PROBLEM_SIZE = 10000
PROCESS_NUMBER = 4

all: sequential parallel

run_all: run_sequential run_parallel

sequential:
	gcc  riemann_sequential.c -std=c99 -ggdb -o $(NAME)_sequential

parallel:
	mpicc  riemann_parallel.c -std=c99 -o $(NAME)_parallel

run_sequential_without_file:
	./$(NAME)_sequential $(PROBLEM_SIZE)

run_sequential:
	./$(NAME)_sequential $(PROBLEM_SIZE) data.dat

run_parallel:
	 mpirun -np $(PROCESS_NUMBER) $(NAME)_parallel $(PROBLEM_SIZE) data.dat

clean:
	rm -rf $(NAME)_sequential $(NAME)_parallel data.dat


