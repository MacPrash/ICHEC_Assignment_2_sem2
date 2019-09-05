#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 5
	struct pmclass{
	float exam[3][3];
	};

	float det(struct pmclass mat[],int ln){
	float det = 0; 
	det = mat[ln].exam[0][0]*((mat[ln].exam[1][1]*mat[ln].exam[2][2]) - (mat[ln].exam[2][1]*mat[ln].exam[1][2])) -mat[ln].exam[0][1]*(mat[ln].exam[1][0]*mat[ln].exam[2][2] - mat[ln].exam[2][0]*mat[ln].exam[1][2]) + mat[ln].exam[0][2]*(mat[ln].exam[1][0]*mat[ln].exam[2][1] - mat[ln].exam[2][0]*mat[ln].exam[1][1]);
	return(det);
	}

	double submatrix(double temp[4][4])
	{
	int row, col, i;
	struct pmclass *pmc;
	pmc = (struct pmclass*) malloc(4 * sizeof(struct pmclass));
	int sign = 1;
	double ans = 0;
	for(i = 0; i<4;i++) 
	{
		int k =0, j=0;
	   for(row = 0; row<4; row++) 
  	   {
    		for(col = 0; col<4; col++)
    		{
     			if(row != 0 && col != i) 
     			{
     				pmc[i].exam[j][k] = temp[row][col];
					k = k + 1;
				   if(k == 3)
			       {
						k = 0;
						j = j + 1;
			       }
			    } 
    		}

		}
		ans += sign * temp[0][i] * det(pmc, i);
		sign = -sign;
	}
	free(pmc);
	return ans;
	}


int main(int argc, char **argv){
	double D = 0.0;
	int sign = 1;
	int rank, nproc;
	double accum;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double Det = 0.0;
	int row, col, i;
	printf("\n\n");
	double mat[5][5] = {{1.0, -1.0/2.0, -1.0/3.0, -1.0/4.0, -1.0/5.0},
		{-1.0/2.0, 1.0/3.0, -1.0/4.0, -1.0/5.0, -1.0/6.0},
		{-1.0/3.0, -1.0/4.0, 1.0/5.0, -1.0/6.0, -1.0/7.0},
		{-1.0/4.0, -1.0/5.0, -1.0/6.0, 1.0/7.0, -1.0/8.0},
		{-1.0/5.0, -1.0/6.0, -1.0/7.0, -1.0/8.0, 1.0/9.0}
	};
		if (rank == 0)
		{
			int f = rank;
			int row, col, i=rank;
			double temp[4][4];
			int k =0, j=0;
		   for(row = 0; row<5; row++) 
		 	  {
    			for(col = 0; col<5; col++)
    				{
     					if(row != 0 && col != rank) 
     					{
     					temp[j][k] = mat[row][col];
						k = k + 1;
					       if(k == 4)
						    {
								k = 0;
								j = j + 1;
				       		}
			     		} 
    				}


				 }
			sign =  (rank%2==0?1:-1);
			D = sign * mat[0][f] * submatrix(temp);
			printf("D: %lf\tProc:%d\n", D, rank);
			Det = Det + D;
		}
		if(rank == 1)
        {
			int f = rank;
			int row, col, i=rank;
			double temp[4][4];
			int k =0, j=0;
		    for(row = 0; row<5; row++)
		     	{
    				for(col = 0; col<5; col++)
    					{
     						if(row != 0 && col != rank) 
     						{
     							temp[j][k] = mat[row][col];
								k = k + 1;
					       		if(k == 4)
						    	{
									k = 0;
									j = j + 1;
				       			}
			     			}	 
    					}
				}
			sign =  (rank%2==0?1:-1);
			D = sign * mat[0][f] * submatrix(temp);
            printf("D: %lf\tProc:%d\n", D, rank);
        }
		if(rank == 2)
        {
			int f = rank;
			int row, col, i=rank;
			double temp[4][4];
			int k =0, j=0;
		    for(row = 0; row<5; row++) 
		     	{
    				for(col = 0; col<5; col++)
    					{
     						if(row != 0 && col != rank) 
     						{
     							temp[j][k] = mat[row][col];
								k = k + 1;
					       		if(k == 4)
						    	{
									k = 0;
									j = j + 1;
				       			}
			     			}	 
    					}
				}
			sign =  (rank%2==0?1:-1);
			D = sign * mat[0][f] * submatrix(temp);
            printf("D: %lf\tProc:%d\n", D, rank);
        }
		if(rank == 3)
        {
			int f = rank;
			int row, col, i=rank;
			double temp[4][4];
			int k =0, j=0;
		    for(row = 0; row<5; row++) 
		     	{
    				for(col = 0; col<5; col++)
    					{
     						if(row != 0 && col != rank) 
     						{
     							temp[j][k] = mat[row][col];
								k = k + 1;
					       		if(k == 4)
						    	{
									k = 0;
									j = j + 1;
				       			}
			     			}	 
    					}
				}
			sign =  (rank%2==0?1:-1);
			D = sign * mat[0][f] * submatrix(temp);
            printf("D: %lf\tProc:%d\n", D, rank);
        }
		if(rank == 4)
        {
			int f = rank;
			int row, col, i=rank;
			double temp[4][4];
			int k =0, j=0;
		    for(row = 0; row<5; row++) 
		     	{
    				for(col = 0; col<5; col++)
    					{
     						if(row != 0 && col != rank) 
     						{
     							temp[j][k] = mat[row][col];
								k = k + 1;
					       		if(k == 4)
						    	{
									k = 0;
									j = j + 1;
				       			}
			     			}	 
    					}
				}
			sign =  (rank%2==0?1:-1);
			D = sign * mat[0][f] * submatrix(temp);
            printf("D: %lf\tProc:%d\n", D, rank);
        }
	if(rank!=0)
		MPI_Send(&D,1,MPI_DOUBLE,0,1,MPI_COMM_WORLD);
	else
	{
		for(int j=1;j<nproc;j=j+1){
			MPI_Recv(&accum,1,MPI_DOUBLE,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,&status);
			printf("Accum:\t%lf\t\t%lf\n", accum, Det);
			Det = Det + accum;
		}
	}


	if(rank == 0)
	{
		printf("Determinant of the matrix is : %lf\n", Det);
		printf("Actual Result: %lf\n\n", -2678797333.0/88905600000.0);
	}
	MPI_Finalize();
	return 0;
}



