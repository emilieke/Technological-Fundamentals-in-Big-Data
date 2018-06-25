#include <mpi.h> 
#include <stdio.h>


int main(int argc, char** argv) {
	long num_steps = 100000;

	/* Variable declaration */
	int size, rank, name_len, i;
	double x, pi, my_pi;
	char p_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(p_name, &name_len); 
	MPI_Barrier(MPI_COMM_WORLD);

    	/* Shared intervals */
	/* MPI_Bcast(&num_steps, 1, MPI_INT, 0, MPI_COMM_WORLD); */
	double step = 1.0/100000.0;
	double sum = 0.0;
	for(i = rank + 1; i < num_steps; i += size) {
		x = (i-0.5)*step;
		sum += 4.0/(1.0+x*x); 
	}
	my_pi = step*sum;

	/* Consolidate and get final result */
	MPI_Reduce(&my_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 
	if (rank == 0) {
		printf("PI value = %f\n", pi);
		printf("This program uses %d processes\n", size); 
	}
	MPI_Finalize();
}
