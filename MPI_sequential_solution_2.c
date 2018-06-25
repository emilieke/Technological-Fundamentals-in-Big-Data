#include <stdio.h>

int main(int argc, char** argv) {
	/* Variable declaration */
	int size, rank, name_len;
	char p_name[MPI_MAX_PROCESSOR_NAME];
	double startwtime, endwtime;

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

	FILE * fp;
 	int i, size, total;
 	char buf[10000];

 	/* Read file “test_file.txt” and store it in buf[] */
 	fp = fopen("test_file.txt","r");
 	fseek(fp, 0L, SEEK_END);
 	size = ftell(fp);
 	fseek(fp, 0L, SEEK_SET);
 	fread (buf,1,size,fp);
 	int counter = 0;

 	for(i = rank + 1; i <= size; i += size) {
 		if (buf[i]==' ')
 			counter = counter + 1;
 	}

	if (rank == 0) {
		endwtime = MPI_Wtime();
		printf("Number of spaces in the file is %d\n", total);
		printf("Wall clock time = %f\n", endwtime-startwtime); 
	}
}
