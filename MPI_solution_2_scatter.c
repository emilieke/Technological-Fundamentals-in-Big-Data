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
 	int i, f_size, total, n_elements, elements_per_process;
 	char buf[10000];

 	/* Read file “test_file.txt” and store it in buf[] */
	fp = fopen("test_file.txt","r");
	fseek(fp, 0L, SEEK_END);
	f_size = ftell(fp);
	n_elements = f_size + 1;
	fseek(fp, 0L, SEEK_SET);

	elements_per_process = n_elements/size;
	char sub_buf[10000];

	if (rank == 0) { 	
 		fread (buf,1,f_size,fp);
	}

 	/* Shared intervals */
 	MPI_Scatter(buf, elements_per_process, MPI_INT, sub_buf, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
 	int counter = 0;

 	for (i=0; i < elements_per_process; i++) {
 		if (sub_buf[i]==' ')
 			counter = counter + 1;
 	}

	/*MPI_Gather(&counter, 1, MPI_INT, counters, 1, MPI_INT, 0, MPI_COMM_WORLD);*/

 	/* Consolidate and get final result */
	MPI_Reduce(&counter, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
	if (rank == 0) {
		printf("Number of spaces in the file is %d\n", total); 
		printf("This program uses %d processes\n", size);
	}


	MPI_Finalize();
}
