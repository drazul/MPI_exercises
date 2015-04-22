#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void create_random_file(char* filename, int problem_size) {
  FILE *fp;
  fp = fopen(filename, "w");

  for (int i = 0; i < problem_size; i++)
    fprintf(fp, "%d%d", rand() % 10, rand() % 10);

  fclose(fp);
}


int main(int argc, char *argv[]){

  if (argc != 3) {
    printf("Worng number of arguments.\nYou may execute with number of processors and problem size.\n\n./riemann number_processors problem_size\n\n");
    return -1;
  }

  int number_processors = atoi(argv[1]);
  int problem_size = atoi(argv[2]);

  printf("Number of processors: %d\n", number_processors);
  printf("Problem size: %d\n", problem_size);


  char *filename = "data.dat";

  create_random_file(filename, problem_size);

}
