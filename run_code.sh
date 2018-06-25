# Run 5 tests of the OpenMP_solution_1 with np from 1 to 10

gcc -fopenmp -o OpenMP_solution_1 OpenMP_solution_1.c

for i in $(seq 1 5) do 
	for j in $(seq 1 10) do 
		export OMP_NUM_THREADS=j
		./OpenMP_solution_1 
	done 
done


# Run 5 tests of the MPI_solution_1 with np from 1 to 8

mpicc -o MPI_solution_1 MPI_solution_1.c

for i in $(seq 1 5) do 
	for j in $(seq 1 8) do 
		mpirun -np $j ./MPI_solution_1 
	done 
done

# Run 5 tests of the MPI_solution_2 with np from 1 to 8

mpicc -o MPI_solution_2 MPI_solution_2.c

for i in $(seq 1 5) do 
	for j in $(seq 1 8) do 
		mpirun -np $j ./MPI_solution_2
	done 
done