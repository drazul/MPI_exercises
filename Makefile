NAME = riemann

all: sequential

sequential:
	gcc  riemann_sequential.c -std=c99 -ggdb -o $(NAME)

parallel:
	mpic  riemann_parallel.c -o $(NAME)

run_sequential:
	./$(NAME) 10

run_parallel:
	 mpirun -np 2 riemann 10 

clean:
	rm -rf $(NAME) data.dat


