
/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 2 - Problem 1
* Name: Blake Wrege
* E-mail: blake.j.wrege@wmich.edu
* Submitted: 2/15/2016
*************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>



main()
{
	/* Declare variables */
	int len = 0;
	char myStr[1000];

	/* Prompt user for myStr until variable is within parameters */
	do {
		printf("Enter a DNA subsequence: ");
		scanf("%s", &myStr);
		len = strlen(myStr);
		if (len < 4 || len > 100) {
			printf("Error: a must be 4 to 100\n");
			strcpy(myStr, "");
		}
	} while (len < 4 || len > 100);

	int     fd[2], nbytes, d;
	pid_t   childpid;
	int count = 0;
	char tempStr[strlen(myStr)+1];
	char readbuffer[80]= "";

	pipe(fd);
	if ((childpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if (childpid == 0)
	{

	//	printf("I am the child process. My PID is %d\n", getpid());

		for (d = 0; d <= strlen(myStr); d++) {
			if (myStr[d] == 'A' || myStr[d] == 'C' || myStr[d] == 'G' || myStr[d] == 'T') {
				tempStr[count] = myStr[d];
				count++;
			}

		}
		char cleanStr[count+1];
		strncpy(cleanStr, tempStr, count);
		cleanStr[count]='\0';


		/* Child process closes up input side of pipe */
		close(fd[0]);

		/* Send "string" through the output side of pipe */
		write(fd[1], cleanStr, (strlen(cleanStr)));
		readbuffer[(strlen(cleanStr))] = '\0';
		exit(0);
	
	}
	else
	{
		/* Parent process closes up output side of pipe */
		close(fd[1]);

		/* Read in a string from the pipe */
	nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
	printf("Received string: %s", readbuffer);
	//	printf("\nI am the parent process. My PID is %d\n", getpid());
	}

	return 0;
}