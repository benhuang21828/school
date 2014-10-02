/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS Benjamin Huang*/


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define KEY (key_t) 12098

typedef struct{
	long pid;
	int perfect;
	int tested;
	int notTested;
}process;

typedef struct{
	int bit[8000];
	int per[20];
	process proc[20];
	long manPid;
}share;

void main(int argc, char *argv[]){
	int shmid=shmget(KEY, sizeof(share), IPC_CREAT|0660);


	share *mem=(share*)shmat(shmid,0,0);


        if(shmid == -1){
                perror("shmget error \n");
                exit(0);
        }

	if(mem==(share*)-1){
		perror("shmat error \n");
		exit(0);
	}

	if(argc>=1){
		int i;
		int perfect;
		int testtotal;
		int pids;

		for(i=0;i<20;i++){
			perfect=mem->per[i];
			if(perfect!=0){
				printf("The perfect number: %d\n",perfect);
			}
			else{
				break;
			}
		}

		for(i=0;i<20;i++){
			testtotal = testtotal+mem->proc[i].tested;
		}
		printf("The total number tested: %d\n",testtotal);

		for(i=0;i<20;i++){
			pids = mem->proc[i].pid;
			if(pids!=0){
				printf("The PID: %d\n",pids);
			}
		}

		if(argc!=1&&strcmp(argv[1],"-k")==0){

			int stat;
			kill(mem->manPid,SIGINT);
		//	waitpid(mem->manPid,stat,0);
		}
	}
	if(shmdt(mem)==-1){
		perror("shmdt error");
		exit(0);
	}

}
