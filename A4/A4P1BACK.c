
/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 3 - Program 2
* Name: Blake Wrege
* E-mail: blake.j.wrege@wmich.edu
* Submitted: 3/14/2016
*************************************************/

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>

int
main(int argc, char **argv)
{
	int x, y, n, i, k, h;
	int xMin, xMax, yMax, nMax;
	time_t t;
		do {
		printf("x min: ");
		scanf("%d", &xMin);
		if (xMin < 0 || xMin > 999)
			printf("Error: x min must be greater than 0 and less than 1000\n");
	} while (xMin < 0 || xMin > 999);
	do {
		printf("x max: ");
		scanf("%d", &xMax);
		if (xMax < xMin || xMax > 999)
			printf("Error: x max must be greater than x min and less than 1000\n");
	} while (xMax < xMin || xMax > 999);
	do {
		printf("y max: ");
		scanf("%d", &yMax);
		if (yMax < 1 || yMax > 999)
			printf("Error: y max must be greater than 0 and less than 1000\n");
	} while (yMax < 1 || yMax > 999);

	do {
		printf("number of nodes: ");
		scanf("%d", &nMax);
		if (nMax < 1 || nMax > 9999)
			printf("Error: number of nodes must be greater than 0 and less than 10000\n");
	} while (nMax < 1 || nMax > 9999);

	int xArray[nMax], yArray[nMax];
	srand((unsigned) time(&t));
//	printf("%d\n", rand());


	for (i = 0; i < nMax; i++) {
		n = (rand() % (xMax+1-xMin))+xMin;
		xArray[i] = n;
	}

	for (k = 0; k < nMax; k++) {
		n = rand() % yMax+1;
		yArray[k] = n;
	}

		for (h = 0; h < nMax; h++) {
		printf("%d,%d\n",xArray[h],yArray[h]);
	}






	return 0;
}

