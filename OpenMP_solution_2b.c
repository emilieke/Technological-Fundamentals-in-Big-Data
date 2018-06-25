#include <stdio.h>
#include <omp.h>
int main (){
	/* Variable declaration */
	FILE * fp;
 	int i, size, counter = 0;
 	char buf[10000];

 	/* Read file “test_file.txt” and store it in buf[] */
 	fp = fopen("test_file.txt","r");
 	fseek(fp, 0L, SEEK_END);
 	size = ftell(fp);
 	fseek(fp, 0L, SEEK_SET);
 	fread (buf,1,size,fp);
	#pragma omp parallel private(i)
	{
		/* Split into threads, count number of spaces */
 		#pragma omp for reduction (+:counter)
 			for(i=0; i <= size; ++i) {
 				if (buf[i] ==' ')
 					counter = counter + 1;
 			}
 	} 
 	/* All threads join master thread and terminate */
 	printf("Number of spaces in the file is %d\n", counter);
}