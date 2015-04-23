NAME = riemann

all: secuencial

secuencial:
	gcc  riemann_secuencial.c -std=c99 -ggdb -o $(NAME)

run:
	./$(NAME) 1 10

clean:
	rm -rf $(NAME) data.dat


