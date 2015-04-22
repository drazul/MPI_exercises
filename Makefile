NAME = riemann

all:
	gcc  riemann.c -std=c99 -o $(NAME)

run:
	./$(NAME) 1 10

clean:
	rm -rf $(NAME) data.dat


