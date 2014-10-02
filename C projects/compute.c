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

typedef struct {
	long type;
	int data;
}msg;


int whichInt(int n){
        int INT;
        INT = (n - 1)/32;
        return INT;
}

int whichBit(int n){
	int BIT = 31 - (n-1)%32;
	return BIT;	
}


void setBit(int n, share* mem){	

	int b = whichInt(n);
	int c = whichBit(n);

	mem->bit[b] |= 1 << c;

}


int testBit(int n, share* mem){


	int b = whichInt(n);
	int c = whichBit(n);
	if(mem->bit[b] & 1 << c)
		return 1;
	else
		return 0;

}


int testper(int n){
	int i=2,sum=1;
	while(i<n){
		if(n%i==0){
			sum=sum+i;
		}
		i++;
	}
	if(sum==n)
		return 1;
	else
		return 0;
}

share *mem;

//signal handler
void handler(int signum){
        int i;
	pid_t ppid = getpid();


	if (signum == SIGINT||signum == SIGQUIT||signum == SIGHUP){
		for(i=0;i<20;i++){
			if(mem->proc[i].pid==ppid){
				mem->proc[i].pid = 0;
				break;
			}
		}

		if(shmdt(mem)==-1){
			perror("shmdt error");
			exit(0);
		}
		exit(0);
	}
/*
	if (){
		if(shmdt(mem)==-1){
			perror("shmdt error");
			exit(0);
		}
		exit(0);
	}

	if (){
		if(shmdt(mem)==-1){
			perror("shmdt error");
			exit(0);
		}
		exit(0);
	}*/

}       



void main(int argc, char *argv[]){

	int shmid = shmget(KEY,sizeof(share),IPC_CREAT|0660);
	mem = (share*)shmat(shmid,0,0);



	if(argv[1]==NULL){
		perror("input error\n");
		exit(0);
	}	

	int num=atoi(argv[1]);

//	void handler();

	signal(SIGINT,handler);
	signal(SIGQUIT,handler);
	signal(SIGHUP,handler);

	if(shmid==-1){
		perror("shmget error\n");
		exit(0);
	}
	else if(mem==(share*)-1){
		perror("shmat error\n");
		exit(0);
	}
	else{
		int pids = getpid();
		int queue=msgget(KEY,IPC_CREAT|0660);
		msg meg;
		if(queue==-1){
			perror("msgget error\n");
			exit(0);
		}
		meg.type=1;
		meg.data=(long)pids;
		msgsnd(queue,&meg,sizeof(meg.data),0);

		int i;
		sleep(1);
		for(i=0;i<20;i++){
			if(mem->proc[i].pid==(long)pids){
				int j = num;
				while(testBit(j,mem)&&j<256000){
					mem->proc[i].notTested++;
					j++;
				}
				while(j<256000){
					if(!testBit(j,mem)){
						if(testper(j)){
							meg.type=3;
							meg.data=j;
							msgsnd(queue,&meg,sizeof(meg.data),0);
							printf("perfect number sent: %d\n", j);
						}
						mem->proc[i].tested++;
						setBit(j,mem);
					}

					j++;
				}

			}
		}
		return;

	}
}
