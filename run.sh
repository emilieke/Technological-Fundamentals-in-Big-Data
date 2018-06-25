#Run this file in cmd to retrieve the results from the tests

mpicc -o MPI_solution_2 MPI_solution_2.c

for j in $(seq 1 8) 
do 
for i in $(seq 1 5) 
do 
time mpirun -np $j ./MPI_solution_2
done 
done

