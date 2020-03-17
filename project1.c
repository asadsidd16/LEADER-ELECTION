//Samantha Yee & Asad Siddiqui
#include <stdio.h>
#include <mpi.h>
#include <time.h>

#define N 8
int main(int argc, char* argv[]){
        int cont, msg1, msg2, rank, size, val;

        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        srand(time(NULL)+rank);

        if(rank==0){
                val = rand();
                if(val < 0){
                        val = abs(val);
                }
                if(val < 10){
                        val += 10;
                }
                if(val > 100){
                        val %= 100;
                }
                cont = 1000 + (100*rank) + val;

                if(val % 2 != 0){
                        msg1=cont;
                        msg2 = 19990;
                }
                if(val%2==0){
                        msg2 = cont;
                        msg1 = 19999;
                }
                MPI_Send(&msg1, 1,MPI_INT, (rank+1)%2,0, MPI_COMM_WORLD);
                printf("Process %d sent odd %d from process %d \n", rank,msg1, rank+1);
                MPI_Send(&msg2, 1,MPI_INT, (rank+1)%2,1, MPI_COMM_WORLD);
                printf("Process %d sent even %d from process %d\n", rank,msg2, rank+1);
                }
        else{
                MPI_Recv(&msg1, 1,MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Process %d recieved  %d from process %d \n", rank,msg1, rank-1);
                MPI_Recv(&msg2, 1, MPI_INT,rank-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Process %d recieved even %d  from process %d \n", rank,msg2, rank-1);

                val = rand();

                if(val < 0){
                        val = abs(val);
                }
                if(val > 100){
                       val = val%100;
                }
                 if(val < 10){
                        val+= 10;
                }
                cont = 1000 + (100*rank)+ val;
                {
                if(msg1>cont&& cont%2!=0){
                        msg1 = cont;
                }
                if(cont%2 == 0&&msg2>cont){
                        msg2= cont;
                }
                MPI_Send(&msg1, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);
                printf("Process %d sent odd %d to process %d\n",rank, msg1, rank+1);
                MPI_Send(&msg2, 1, MPI_INT, (rank+1)%size,1, MPI_COMM_WORLD);
                printf("Process %d sent even %d to process %d\n",rank, msg2, rank+1);

                MPI_Send(&msg1, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);
                printf("Process %d sent odd %d to process %d\n",rank, msg1, rank+1);
                MPI_Send(&msg2, 1, MPI_INT, (rank+1)%size, 1, MPI_COMM_WORLD);
                printf("Process %d sent even %d to process %d\n",rank, msg2, rank+1);
                }
        }

        if(rank==0){
                MPI_Recv(&msg1, 1, MPI_INT,size-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                printf("President: %d \n",msg1);
                MPI_Recv(&msg2, 1, MPI_INT,size-1,1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                printf("Vice President: %d \n",msg2);
        }
        MPI_Finalize();
                return 0;
}
