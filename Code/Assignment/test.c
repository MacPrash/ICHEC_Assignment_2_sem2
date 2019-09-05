#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

//double determinant(struct pmclass1 pmc1[]);
//:void submatrix(double matp[5][5]);

struct pmclass{
float exam[3][3];
};


struct pmclass1{
float exam[4][4];
};


double determinant(struct pmclass1 pmc1[]);
void submatrix(double matp[5][5]);



float det(struct pmclass mat[],int ln){
float det = 0; 
det = mat[ln].exam[0][0]*((mat[ln].exam[1][1]*mat[ln].exam[2][2]) - (mat[ln].exam[2][1]*mat[ln].exam[1][2])) -mat[ln].exam[0][1]*(mat[ln].exam[1][0]*mat[ln].exam[2][2] - mat[ln].exam[2][0]*mat[ln].exam[1][2]) + mat[ln].exam[0][2]*(mat[ln].exam[1][0]*mat[ln].exam[2][1] - mat[ln].exam[2][0]*mat[ln].exam[1][1]);
return(det);
}

int main(int argc, char *argv[]){
int row, col, i;
printf("Hilbert Matrix is : \n\n");
double mat[5][5] = {{1.0, -1.0/2.0, -1.0/3.0, -1.0/4.0, -1.0/5.0},
		{-1.0/2.0, 1.0/3.0, -1.0/4.0, -1.0/5.0, -1.0/6.0},
		{-1.0/3.0, -1.0/4.0, 1.0/5.0, -1.0/6.0, -1.0/7.0},
		{-1.0/4.0, -1.0/5.0, -1.0/6.0, 1.0/7.0, -1.0/8.0},
		{-1.0/5.0, -1.0/6.0, -1.0/7.0, -1.0/8.0, 1.0/9.0}
	};
double D = 0.0;
int sign = 1;
int rank, nproc;
double accum;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &nproc);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
double Det = 0.0;
//submatrix(mat);
struct pmclass1 *pmc1;
submatrix(mat);
if(rank == 0)
{
	int f = rank;
	sign =  (rank%2==0?1:-1);
	D = sign * mat[0][f] * determinant(pmc1[f]);
	printf("D: %lf\tProc:%d\n", D, rank);
	Det = Det + D;
}
if(rank == 1)
{
	int f = rank;
	sign =  (rank%2==0?1:-1);
	D = sign * mat[0][f] * determinant(*pmc1[f]);
	printf("D: %lf\tProc:%d\n", D, rank);
 }
if(rank == 2){
	int f = rank;
	sign =  (rank%2==0?1:-1);
	D = sign * mat[0][f] * determinant(*pmc1[f]);
	printf("D: %lf\tProc:%d\n", D, rank);
}
if(rank == 3)
{
	int f = rank;
	sign =  (rank%2==0?1:-1);
	D = sign * mat[0][f] * determinant(*pmc1[f]);
	printf("D: %lf\tProc:%d\n", D, rank);
}
if(rank == 4)
{
	int f = rank;
	sign =  (rank%2==0?1:-1);
	D = sign * mat[0][f] * determinant(*pmc1[f]);
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



double determinant(struct pmclass1 pmc1[]){
int col,row,i;
struct pmclass *pmc;
pmc = (struct pmclass*) malloc(4 * sizeof(struct pmclass));
int sign = 1;
float ans = 0;
for(i = 0; i<4;i++) //For each of the struct we are creating 3x3 matrix.
{
int k =0, j=0;
  for(row = 0; row<4; row++) //row and col to obtain the particular values from hilbert matrix.
  {
    for(col = 0; col<4; col++)
    {
     if(row != 0 && col != i) //Here we are ignoring the first row and particular column to for each 3x3 matrix.
     {
     pmc[i].exam[j][k] = pmc1[i].exam[row][col];
     k = k + 1;
       if(k == 3)
       {
	k = 0;
	j = j + 1;
       }
     } 
    }

  }

ans += sign * pmc[i].exam[0][i] * det(pmc[i], i);
sign = -sign;
}
return ans;
}


void submatrix(double mat[5][5]){

int col,row,i;
struct pmclass1 *pmc1;
pmc1 = (struct pmclass1*) malloc(5 * sizeof(struct pmclass1));
int sign = 1;
for(i = 0; i<5;i++) //For each of the struct we are creating 3x3 matrix.
{
int k =0, j=0;
  for(row = 0; row<5; row++) //row and col to obtain the particular values from hilbert matrix.
  {
    for(col = 0; col<5; col++)
    {
     if(row != 0 && col != i) //Here we are ignoring the first row and particular column to for each 3x3 matrix.
     {
     pmc1[i].exam[j][k] = mat[row][col];
	k = k + 1;
       if(k == 3)
       {
	k = 0;
	j = j + 1;
       }
     } 
    }
  }
}
}



