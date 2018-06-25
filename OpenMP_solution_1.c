#include <stdio.h>
#include <omp.h>
int main (){
	/* Variable declaration */
	long num_steps = 100000;
	double step = 1.0/100000.0;
	int i;
	double x, pi, sum = 0.0;

	#pragma omp parallel private(x)
	{
		/* Split into threads, calculate part of the sum */
 		#pragma omp for reduction (+:sum)
 			for (i=0; i<num_steps; ++i) {
 				x = (i-0.5)*step;
 				sum += 4.0/(1.0+x*x);
 			}
 			pi = step*sum;
 	} 

 	/* All threads join master thread, final pi value is calculated and terminate */
 	printf("PI value = %f\n", pi);
	
}
