#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
  float tmp1, tmp2;
  char tmp;
  for (int i = 0; i < (problem_size * 2); i++) {
    fscanf(fp, "%f ", &tmp1);
    data[i] = tmp1;
  }

  fclose(fp);
}

void print_data(double *data, int size) {
  for (int i = 0; i < size ; i++)
    printf("%f %f\n", data[i * 2], data[i * 2 + 1]);
}

double left_riemann(double *data, int size) {
  double result = 0;
  for (int i = 1; i < (size - 1); i++){
    // result += f(xi-1) * (xi - xi-1);
    result += data[i - 1] * (data[i] - data[i - 2]);
  }
  return result;
}

double right_riemann(double *data, int size) {
  double result = 0;
  for (int i = 1; i < (size - 1); i++){
    // result += f(xi) * (xi - xi-1);
    result += data[i + 1] * (data[i] - data[i - 2]);
  }
  return result;
}

double trapezoidal_riemann(double *data, int size) {
  double result = 0;
  for (int i = 1; i < (size - 1); i++){
    // result += ((f(xi - 1) + f(xi)) / 2) * (xi - xi-1);
    result += ((data[i - 1] + data[i + 1]) / 2) * 
            (data[i] - data[i -2]);
  }
  return result;
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

  double * data = malloc(sizeof(double) * problem_size * 2);

  read_data_from_file(filename, problem_size, data);

  print_data(data, problem_size);

  double result;

  result = left_riemann(data, problem_size);
  printf("Left Riemann: %f\n", result);

  result = right_riemann(data, problem_size);
  printf("Right Riemann: %f\n", result);

  result = trapezoidal_riemann(data, problem_size);
  printf("Trapezoidal Riemann: %f\n", result);
}




