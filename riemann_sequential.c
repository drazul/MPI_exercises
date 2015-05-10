#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void create_random_file(char* filename, int problem_size) {
  FILE *fp;
  fp = fopen(filename, "w");

  double tmp = 0, previous = 0;

  for (int i = 0; i < problem_size; i++){
    while (tmp <= previous)
      tmp = (double) rand() / (double) rand();
    previous = tmp;
    fprintf(fp, "%f %f ", tmp, (double)rand() / (double)rand());

  }
  fclose(fp);
}

void read_data_from_file(char* filename, int problem_size, double *data) {
  FILE *fp;
  fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "Can't open input file!\n\n");
    exit(1);
  }

  float tmp1;
  char tmp;
  for (int i = 0; i < (problem_size * 2); i++) {
    fscanf(fp, "%f ", &tmp1);
    data[i] = tmp1;
  }

  fclose(fp);
}

void print_data(double *data, int size) {
  printf("\nx(i)\t\tf(x(i))\n");
  for (int i = 0; i < size ; i++)
    printf("%f\t%f\n", data[i * 2], data[i * 2 + 1]);
  printf("\n");
}

double left_riemann(double *data, int size) {
  double result = 0;
  for (int i = 1; i < size; i++){
    // result += f(xi-1) * (xi - xi-1);
    result += data[(i * 2) - 1] * (data[(i * 2)] - data[(i * 2) - 2]);

  }
  return result;
}

double right_riemann(double *data, int size) {
  double result = 0;
  for (int i = 1; i < size; i++){
    // result += f(xi) * (xi - xi-1);
    result += data[(i * 2) + 1] * (data[(i * 2)] - data[(i * 2) - 2]);
  }
  return result;
}

double trapezoidal_riemann(double *data, int size) {
  double result = 0;
  for (int i = 1; i < size; i++){
    // result += ((f(xi - 1) + f(xi)) / 2) * (xi - xi-1);
    result += ((data[(i * 2) - 1] + data[(i * 2) + 1]) / 2) * 
            (data[(i * 2)] - data[(i * 2) - 2]);
  }
  return result;
}

int main(int argc, char *argv[]){
  printf("\n");

  if (argc < 2) {
    printf("Worng number of arguments.\nYou may execute with problem size.\n\n./riemann problem_size\n\nYou can also execute with data file\n\n./riemann problem_size filename\n\n");
    return -1;
  }

  int problem_size = atoi(argv[1]);

  char *filename = "data.dat";

  if (argc == 2) 
    create_random_file(filename, problem_size);

  else
    filename = argv[2];
    
  double * data = malloc(sizeof(double) * problem_size * 2);

  read_data_from_file(filename, problem_size, data);

  //printf("Problem size: %d\n", problem_size);
  //print_data(data, problem_size);

  double result;
  clock_t time = clock ();

  result = left_riemann(data, problem_size);
  printf("Left Riemann: %f\n", result);

  result = right_riemann(data, problem_size);
  printf("Right Riemann: %f\n", result);

  result = trapezoidal_riemann(data, problem_size);
  printf("Trapezoidal Riemann: %f\n", result);

  time = clock() - time;

  printf("\nTime spent: %f seconds\n\n", ((double) time / CLOCKS_PER_SEC));

  return 0;
}




