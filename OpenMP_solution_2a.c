#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	/* Variable declaration */
	FILE * fp;
 	int size,i;
 	char buf[10000];

 	/* Read file “test_file.txt” and store it in buf[] */
 	fp = fopen("test_file.txt","r");
 	fseek(fp, 0L, SEEK_END);
 	size = ftell(fp);
 	fseek(fp, 0L, SEEK_SET);
 	fread (buf,1,size,fp);

 	/* Count number of spaces in buf[] */
 	int counter = 0;
 	for(i=0; i <= size; ++i) {
 		if (buf[i]==' ')
 			counter = counter + 1;
 	}
 	printf("Number of spaces in the file is %d\n", counter);
}
