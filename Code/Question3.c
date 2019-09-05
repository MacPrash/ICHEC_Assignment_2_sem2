#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

FILE *fr;
int main(int argc, char **argv){
double time1, time2;
double last;
int i, ierr, rank, nprocs;
long elapsed_seconds;
int indata[25];
char buf[256];
ierr = MPI_Init(&argc,&argv);
time1 = MPI_Wtime();
ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
ierr = MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
if (rank == 0 ) {
/* open the file for reading */
fr = fopen ("values.dat", "rt");
/* fill indata */
i = 0;
while (!feof(fr)) {
fscanf(fr, "%d", &indata[i]);
i = i + 1;
}
// close the file */
fclose(fr);
}
ierr = MPI_Bcast( indata, 25, MPI_INT, 0, MPI_COMM_WORLD);

// output process rank 0 in file output.0
// // output process rank 1 in file output.1
// // output process rank 2 in file output.2
// // and so on ...
snprintf(buf, sizeof(buf), "output.%d", rank);
// /* open the file for reading */
fr = fopen (buf, "wt");
// /* fill indata */
i = 0;
while ( i<25 ) {
fprintf(fr, "%d\n", indata[i]);
i = i + 1;
} 
// * close the file */
fclose(fr);
time2 = MPI_Wtime();
ierr = MPI_Finalize();
//printf("Completed Successfully with %f seconds \n",time2-time1);
return 0;
}
