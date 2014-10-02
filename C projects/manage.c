/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENT Benjamin HUang*/


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

share* mem;
int shmid;
int queue;
//signal handler

void handler(int signum){

	if (signum == SIGINT){
		int i;
		int stat;
		for(i=0;i<20;i++){
			if(mem->proc[i].pid==0) break;
			kill(mem->proc[i].pid,SIGINT);
			//waitpid(mem->proc[i].pid,stat,0);

		}

		sleep(5);
		if(shmdt(mem)==-1){
			perror("shmdt error");
			exit(0);
		}
		if(shmctl(shmid,IPC_RMID,0)==-1){
			perror("shmctl error");
			exit(0);
		}
		if(msgctl(queue,IPC_RMID,0)==-1){
			perror("msgctl error");
		}
		exit(0);

	}


}    

void main(int argc, char *argv[]){

	void handler();

	shmid = shmget(KEY, sizeof (share), IPC_CREAT| 0660);
	mem = (share*) shmat(shmid,0,0);

	queue = msgget(KEY, IPC_CREAT | 0660);


	if(shmid==-1){
		perror("shmget error\n");
		exit(0);
	}
	if(mem==(share*)-1){
		perror("shmat error\n");
		exit(0);
	}

	if(queue==-1){
		perror("msgget error\n");
		exit(0);
	}

	mem->manPid=(long)getpid();

	msg meg;

	int i;

        while(1){
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		signal(SIGHUP, handler);                 

		msgrcv(queue, &meg, sizeof(meg.data),0,0);
		if(meg.type == 1){
			if(meg.data < 0) break;

			for(i=0; i<20;i++){
				if(mem->proc[i].pid == 0){
					mem->proc[i].pid = meg.data;
					printf("Currently proccessing Entry: %d, pid: %ld\n", i, mem->proc[i].pid);
					break;
				}
			}

			if(i==20)printf("No more process.\n");

                }


		else if(meg.type == 3){
                        if(meg.data < 0) break;
                        while(mem->per[i] != 0){
				i++;
                        }

			if(i<20) mem->per[i] = meg.data;

		}
	}
}
