#include <stdio.h>     // for printf()
#include <unistd.h>    // for fork(), pid_t
#include <stdlib.h>    // for exit()
#include <sys/types.h>
#include <sys/wait.h> 


#define NUNMBER 10

const static char PARITY[8] = {'E','V','E','N','O','D','D','\0'};

int countbits(int val, int ov){
	int status;
	pid_t pidVal;
	int value;

	if(val == 0){ 
		exit(val);
	}

	if((pidVal = fork()) == 0){
			countbits(val/2, ov);
	}

	if(val % 2 == 0){
		while (waitpid(pidVal, &status, 0) > 0) {
    		if (WIFEXITED(status))   
      			value = WEXITSTATUS(status);   
		}
	}
	else{
		while (waitpid(pidVal, &status, 0) > 0) { 
    		if (WIFEXITED(status))   
      			value = WEXITSTATUS(status) + 1;   
  		}

	}


	if (ov == val)
	{
		return value;
	}
	else{
		exit(value);
	}
}

int main(int argc, char const *argv[])
{
	int bits;
	int num;

	if(argc > 2 || argc < 2){
		if (argc<2)
		{
			printf("Too few command line arguments\n");
		return 0;
		}
		else{
			printf("Too many command line arguments\n");
			return 0;
		}
	}

	num = atoi(argv[1]);


	if(num < 0){
		printf("DONT USE NEGATIVE NUMBERS!\n");
		return 0;
	}


	bits  = countbits(num, num);
	if (bits % 2 == 0)
	{
		printf("The number %d has an %.*s parity.\n",num, 4, PARITY);
	}
	else{
		printf("The number %d has an %.*s parity.\n",num, 8, 4+PARITY);
	}
	return 0;
}

/*MAIN:
int n
 
n = countbit(val);
	if (n%2 == 0){
		printf(EVEN);
	}
	else{
		pringf(ODD);
	}
	*/
