#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv)
{
  // defining the rank
  int Rank, ierror;

  // Defining number of process, left procees id and right process id
  int number_of_process, left_process_id, right_process_id;

  //defining sum to store to total sum value, tmp to store left side of current process sum value, val to store rank and check until myRank != myRank  
  int sum,tmp, val;

  //initilaizing status messages
  MPI_Status rcv_stat, snd_stat;

  //initializing request
  MPI_Request send_request;

  //Initializing MPI environment
  ierror = MPI_Init(&argc, &argv);

  //Using rank we identify different process within the communicator
  ierror = MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

  //Number of processes contained within a communicator
  ierror = MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);

  //left process id is previous process id in chain
  left_process_id=(Rank-1);
  // right process id is next process id in chain
  right_process_id=(Rank+1);

  //Checking is left process id less than zero then assgin number of process - 1 as this will be the previous process 
  if (left_process_id < 0)
  {
   left_process_id = number_of_process-1;
  }

  //Similarly if right process id equal to number of process then assigning zero process id as right process to number of process - 1 process. 
  if (right_process_id == number_of_process)
  {
   right_process_id = 0;
  }
  //Assign the process rank to val and initialize sum to 0 
  val = Rank;
  sum = 0;
   // Non-blocking Synchronous Send
   MPI_Issend(&val,1,MPI_INT,right_process_id,99,MPI_COMM_WORLD,&send_request);
   // Receive
   MPI_Recv(&tmp,1,MPI_INT,left_process_id,99,MPI_COMM_WORLD,&rcv_stat);

   MPI_Wait(&send_request,&snd_stat);
   //Assigning the received value to tmp variable
   //Adding the received process number value from tmp to sum
   val = tmp;
   sum += val;
  int count = 0;
  while(val != Rank) {
    // Non-blocking Synchronous Send 
    MPI_Issend(&val,1,MPI_INT,right_process_id,100,MPI_COMM_WORLD,&send_request);
    // Receive
    MPI_Recv(&tmp,1,MPI_INT,left_process_id,100,MPI_COMM_WORLD,&rcv_stat);
    MPI_Wait(&send_request,&snd_stat);
    //Assigning the received value to tmp variable
    val = tmp;
    //Adding the received process number value from tmp to sum
    sum += val;
  }

  printf("Process id:  %d \t Sum : %d \n", Rank, sum);
  //Terminates MPI execution environment
  ierror = MPI_Finalize();

  return 0;
}
