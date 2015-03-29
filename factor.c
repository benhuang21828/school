/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING

A TUTOR OR CODE WRITTEN BY OTHER STUDENTS Benjamin Huang*/





#include <stdlib.h>
#include <stdio.h>


typedef struct _seg {  /* definition of new type "seg" */

    int  bits[256];
    struct _seg  *next;        
      }seg  ;



#define BITSPERSEG  (8*256*sizeof(int))



void clearbits(seg *, int);

seg* whichseg(int, seg *);

int whichint(int);

int whichbit(int);

void setbit(int, seg *);

int testbit(int, seg *); 

int IsPrime(int);

int NextPrm(int);





void main (int argc, char *argv[]) {



    seg *head;

	seg *pt;

	int	 i;

	int  prm;

	int mul;

	int howmany;

	int count = howmany;

	int segmentamount, n;

	

	

	

	

	

	sscanf(argv[1],"%d",&howmany);

		//else scanf("%d",&howmany);
	segmentamount = (howmany + BITSPERSEG -1)/BITSPERSEG;

	head= (  seg * ) malloc(sizeof(seg));

	pt=head;

	for (i=1;i<segmentamount;i++) {

		pt->next = (  seg *) malloc(sizeof (seg)); 

		pt=pt->next;

		}

	

	clearbits(head, segmentamount); 

      //for each starting prime, mark its every multiple as non-prime

	for (prm = 3; prm <= howmany; prm = prm + 2) {

		if (testbit(prm, head) == 0) {

			for (mul = 3*prm; mul <= howmany; mul += prm*2){

				if (testbit(mul, head) == 0) {

					setbit(mul, head);

						count--;

					}

				}

			}

		}

	int jp = howmany-count;

	printf("The number of odd primes less than or equal to N is: %d \n", jp);

	int u;

	while(scanf("%d",&n) != EOF){

		printf("%d",n);

		while(n%2 == 0){

			n = n/2;
			
			printf(" %d", 2);

		}     

		if(testbit(n,head) == 1 && n >=3){

				for(u = 3; u <= n; u=u+2){

					if(testbit(u, head) == 0){

					while(n%u == 0){

							n = n/u;

							printf(" %d", u);

							}

						}			

					}

				}  else printf(" %d", n);

		}

}	

void	clearbits(seg *ptr , int num) { /* clear all bits at once */

	int i,j;

	for (i=0; i< num; i++) {

		for (j=0; j< 255; j++) {

			ptr->bits[j]=0;

		}

		

		ptr=ptr->next;

	}

}







void  setbit (int n, seg* head){

	int q = (n-3)/2;

	seg* thisseg = whichseg(q, head);

	int thisint = whichint(q);

	int thisbit = whichbit(q);

	

	thisseg->bits[thisint] |= 1 << thisbit;

	

	

	} 

		//- this turns on the bit corresponding to the number n



int   testbit (int n, seg* head){ 

	 int q = (n-3)/2;

	 seg* thisseg = whichseg(q, head);

	 int thisint = whichint(q);

	 int thisbit = whichbit(q);

	if(thisseg->bits[thisint] & 1 << thisbit)

		return 1;

	else

		return 0;

		}

        // - this returns the current value (0/1) of the bit corresponding

        //   to the number n



/*and this is all main needs to know to construct and use the bitmap.

setbit and testbit in turn are written in terms of three technical

routines that you need to write:*/

 



seg * whichseg (int n, seg* head){

	

	n = n/32;

	seg* pointer;

	pointer = head;

	while(n >= 256){

		pointer = pointer-> next;

		n = n - 256;

	}

	return pointer;

       //- this returns a pointer to the segment that contains the bit

       //  for the number n.

	}

int   whichint (int n){

	int LeftOverSeg = n % BITSPERSEG;

	int CurrentInt = LeftOverSeg / 32;

	return CurrentInt;

       // - this returns the array index (between 0 and 255) for the integer

       //  that contains the bit for the number n

	}

int   whichbit (int n){

	int LeftOverSeg = n % BITSPERSEG;

	int CurrentBit = LeftOverSeg % 32;

	return CurrentBit;

       //- this returns the bit number (between 0 and 31) for the bit that

       //   corresponds to the integer n

	}
