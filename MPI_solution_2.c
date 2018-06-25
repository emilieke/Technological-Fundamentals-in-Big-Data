#include <mpi.h> 
#include <stdio.h>

int main(int argc, char** argv) {

	/* Variable declaration */
	int size, rank, name_len;
	char p_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(p_name, &name_len); 
    	MPI_Barrier(MPI_COMM_WORLD);

	FILE * fp;
 	int i, f_size, total;
 	char buf[10000];

 	/* Read file “test_file.txt” and store it in buf[] */
 	fp = fopen("test_file.txt","r");
 	fseek(fp, 0L, SEEK_END);
 	f_size = ftell(fp);
 	fseek(fp, 0L, SEEK_SET);
 	fread (buf,1,f_size,fp);

 	/* Shared intervals */
 	/*MPI_Bcast(&f_size, 1, MPI_INT, 0, MPI_COMM_WORLD);*/
 	int counter = 0;

 	for(i = rank + 1; i <= f_size; i += size) {
 		if (buf[i]==' ')
 			counter = counter + 1;
 	}

 	/* Consolidate and get final result */
	MPI_Reduce(&counter, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
	if (rank == 0) {
		printf("Number of spaces in the file is %d\n", total); 
		printf("This program uses %d processes\n", size);
	}

	MPI_Finalize();
}
