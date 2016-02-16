
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
		printf("\nEnter a DNA subsequence: ");
		scanf("%s", &myStr);
		len = strlen(myStr);
		if (len < 4 || len > 100) {
			printf("Error: a must be 4 to 100");
			strcpy(myStr, "");
		}else{
	/* Sets up for creating child process */
	int     fd[2], nbytes, d;
	pid_t   childpid;
	int count = 0;
	/* Prepares the tempStr and the buffer that is read back into parent */
	char tempStr[strlen(myStr) + 1];
	char readbuffer[101] = "";

	pipe(fd);
	if ((childpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if (childpid == 0)
	{

		/* Preforms the filtering in the child process */

		for (d = 0; d <= strlen(myStr); d++) {
			if (myStr[d] == 'A' || myStr[d] == 'C' || myStr[d] == 'G' || myStr[d] == 'T') {
				tempStr[count] = myStr[d];
				count++;
			}

		}
		/* Null terminates the new string */
		char cleanStr[count + 1];
		strncpy(cleanStr, tempStr, count);
		cleanStr[count] = '\0';


		/* Child process closes up input side of pipe */
		close(fd[0]);

		/* Send "string" through the output side of pipe */
		write(fd[1], cleanStr, (strlen(cleanStr)));
		exit(0);

	}
	else
	{
		/* Parent process closes up output side of pipe */
		close(fd[1]);

		/* Read in a string from the pipe */
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Received string: %s", readbuffer);
	}
}
	return 0;
}
