#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void createFile(char* filename, int problem_size) {
  FILE *fp;
  fp = fopen(filename, "w");

  double tmp = 0, previous = 0;

  int i;
  for(i = 0; i < problem_size; i++) {
    while(tmp <= previous) {
      tmp = (double) rand() / (double) rand();
    }
    previous = tmp;

    fprintf(fp, "%f %f ", tmp, (double)rand() / (double)rand());
  }

  fclose(fp);
}

void readFile(char* filename, int problem_size, double *data) {
  FILE *fp;
  fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "Can't open input file!\n\n");
    exit(1);
  }

  float tmp1;
  char tmp;
  int i;
  for (i = 0; i < (problem_size * 2); i++) {
    fscanf(fp, "%f ", &tmp1);
    data[i] = tmp1;
  }

  fclose(fp);
}

int main(int argc, char** argv) {
  int id; 
  int processors_number;  

  double left_riemann = 0.0;
  double right_riemann = 0.0;
  double trapezoidal_riemann = 0.0;

  double total_left_riemann, total_right_riemann, total_trapezoidal_riemann;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &processors_number);
  MPI_Comm_rank(MPI_COMM_WORLD, &id); 

  int problem_size = atoi(argv[1]);
  double data[problem_size * 2];

  if(id == 0) {
    char *filename = "data.dat";

    if(argc == 2)
      createFile(filename, problem_size);
    else
      filename = argv[2];

    readFile(filename, problem_size, data);
  }

  MPI_Bcast(&data, problem_size * 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  
  clock_t time = clock();
  double time_mpi = MPI_Wtime();

  for(int i = id + 1; i < problem_size; i += processors_number) {
    left_riemann += data[(i * 2) - 1] * (data[(i * 2)] - data[(i * 2) - 2]);
    right_riemann += data[(i * 2) + 1] * (data[(i * 2)] - data[(i * 2) - 2]);
    trapezoidal_riemann += ((data[(i * 2) - 1] + data[(i * 2) + 1]) / 2) * (data[(i * 2)] - data[(i * 2) - 2]);
  }
  

  MPI_Reduce(&left_riemann, &total_left_riemann, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&right_riemann, &total_right_riemann, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&trapezoidal_riemann, &total_trapezoidal_riemann, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  time = clock() - time;
  time_mpi = MPI_Wtime() - time_mpi;

  if(id == 0) {
    printf("\nLeft Riemann: %f\n", total_left_riemann);
    printf("Right Riemann: %f\n", total_right_riemann);
    printf("Trapezoidal Riemann: %f\n\n", total_trapezoidal_riemann);

    printf("\nTime spent (c measurement): %f seconds", ((double) time / CLOCKS_PER_SEC));
    printf("\nTime spent (mpi measurement): %f seconds\n\n", time_mpi);
  }

  MPI_Finalize();

  return 0;
}