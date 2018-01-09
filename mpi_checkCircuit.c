#include <stdio.h>
#include <mpi.h>

int checkCircuit(int []);
int print(int, int []);
int main(int argc, char* argv[]){
	
	int circuit[16];//circuit
	for(int i = 0;i < 16;i++) {
		circuit[i]=0;	
	}
    /*	a)save 16 bit 0/1 in the circuit array. save integer from 0 to 65535
            a.1) divide 65535 to process 0 ~ p.
                E.g. divide 4 process:
                    process[0] compute 0,4,8,...
                    process[1] compute 1,5,9,...
                    process[2] compute 2,6,10,...
                    process[3] compute 3,7,11,...

    	b)store bit from highest to lowest in binary to circuit array
        c)final: compute circuit to get output, and print the output
            c.1) let process id) circuit
            c.2) let process[0] print total available and total time.
	*/
	int count=0;
    // a)
    // a.1)
    int pid;
    int pnum;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &pnum);

/*    if(pid ==  0) {
        printf("%d", pnum);
    }
*/
    for(int i = 0;i < 65536;i++) {
		int j=0;

		// b)
	  	for(int k = 15; k >= 0; k--) {
	   		int binary = (i >> k) & 1;
	   		circuit[j] = binary;
	   		j++;		
	  	}
		
		// c)
		int output = checkCircuit(circuit);
		if (output == 1) {
            // c.1)
            print(pid, circuit);
            count++;
        }
    }
    
    // c.2)
    if(pid == 0) {
        printf("Process 0 is done\n");
        printf("total: %d\n",count);
    }
    MPI_Finalize();

	return 0;
}

int checkCircuit(int circuit[]) {
    int output = (circuit[0] | circuit[1]) & (!circuit[1] | !circuit[3]) & (circuit[2] | circuit[3]) & (!circuit[3] | !circuit[4]) & (circuit[4] | !circuit[5]) & (circuit[5] | circuit[6]) & (circuit[5] | !circuit[6]) & (circuit[7] | !circuit[8]) & (circuit[8] | circuit[9]) & (circuit[8] | !circuit[9]) & (!circuit[9] | !circuit[10]) & (circuit[10] | circuit[11]) & (circuit[11] | circuit[9]) & (circuit[12] | circuit[13]) & (!circuit[7] | !circuit[13]) & (circuit[13] | !circuit[14]) & (circuit[14] | circuit[15]) & (!circuit[15] | circuit[6]);
    return output;
}
int print(int pid, int circuit[]) {
    printf("%d)", pid);
    for(int k=0;k<16;k++){
        printf("%d", circuit[k]);
    }
    printf("\n");
}