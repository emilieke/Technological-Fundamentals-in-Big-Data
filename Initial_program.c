#include <stdio.h>

/* Variable declaration */
long num_steps = 100000;
double step = 1.0/100000.0;

int main() {
	/* Variable declaration */
	int i;
	double x, pi, sum = 0.0;

	/* Sequential process */
	for(i = 0; i < num_steps; ++i) {
 		x = (i-0.5)*step;
 		sum += 4.0/(1.0+x*x);
	}
	pi = step*sum;
	printf("PI value = %f\n", pi);
}
