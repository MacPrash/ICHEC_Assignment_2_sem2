#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv)
{

    // Defining the rank, number of process
    int myRank, ierror, number_of_process;
    // Initializing sum to 0
    int sum = 0;
    //initilaizing status messages
    MPI_Status rcv_stat, snd_stat;
    //initializing request
    MPI_Request send_request;     
    //Initializing MPI Environment
    ierror = MPI_Init(&argc, &argv);
    //Using rank we identify different process within the communicator
    ierror = MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    //Number of processes contained within a communicator
    ierror = MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);
    int val = 0;
    //Loop to calculate sum value 
    while(val < number_of_process)
    {
	//MPI_Ireduce Reduces values on all processes to a single value in a nonblocking way
	MPI_Ireduce(&myRank, &sum, 1, MPI_INT, MPI_SUM, val, MPI_COMM_WORLD, &send_request);
	MPI_Wait(&send_request, &rcv_stat);
	val = val + 1;
    }

	printf("Using IReduce \t Processor: %d \t Sum: %d\n", myRank,sum);
	//Terminates MPI execution environment
	ierror = MPI_Finalize();

  	return 0;
}
