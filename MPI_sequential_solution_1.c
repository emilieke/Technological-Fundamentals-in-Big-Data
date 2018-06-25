#include <stdio.h>


int main(int argc, char** argv) {
	long num_steps = 100000;

	/* Variable declaration */
	int size, rank, name_len, i;
	double x, pi, my_pi, startwtime, endwtime;
	char p_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(p_name, &name_len); 
	
	 /* Show all processor IDs */
    printf("This is Process-%d/%d running on %s \n",rank,size,p_name);
    fflush(0);
    MPI_Barrier(MPI_COMM_WORLD);

    /* Get Runtime information */
    if(rank == 0) 
    {
        printf("This program uses %d processes\n", size);
        startwtime = MPI_Wtime();
    }

	double step = 1.0/100000.0;
	double sum = 0.0;

	for(i = rank + 1; i < num_steps; i += size) {
		x = (i-0.5)*step;
		sum += 4.0/(1.0+x*x); 
	}
	my_pi = step*sum;

	if (rank == 0) {
		endwtime = MPI_Wtime();
		printf("PI value = %f\n", pi);
		printf("Wall clock time = %f\n", endwtime-startwtime); 
	}
}
