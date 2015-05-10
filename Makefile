NAME = riemann

all: sequential parallel

run_all: run_sequential run_parallel

sequential:
	gcc  riemann_sequential.c -std=c99 -ggdb -o $(NAME)_sequential

parallel:
	mpicc  riemann_parallel.c -std=c99 -o $(NAME)_parallel

run_sequential_without_file:
	./$(NAME)_sequential 10

run_sequential:
	./$(NAME)_sequential 10 data.dat

run_parallel:
	 mpirun -np 10 $(NAME)_parallel 10 data.dat

clean:
	rm -rf $(NAME)_sequential $(NAME)_parallel data.dat


