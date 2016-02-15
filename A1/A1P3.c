/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 1 - Problem 3
* Name: Blake Wrege
* E-mail: blake.j.wrege@wmich.edu
* Submitted: 01/01/2016
*************************************************/


#include <stdio.h>
#include <stdlib.h>
/* Declare global variables */
int sum = 0;
int mean = 0;

void calcEven(int* arrPtr, int arrLength);

void calcOdd(int* arrPtr, int arrLength);

int main() {
	/* Declare local variables */
	int d, n;
	int count, countEven, countOdd;
	time_t t;
	int arrALL[20];
	int arrEven[10];
	int arrOdd[10];
	int *even;
	int *odd;
	count = 0; countEven = 0; countOdd = 0;

	/* Intializes random number generator */
	srand((unsigned) time(&t));
	/* Stores random numbers from 500 to 599 into designated arrays */
	for (d = 1; d <= 20; d++) {
		n = rand() % 100 + 500;
		arrALL[count] = n;

		if ((count + 1) % 2 == 0) {
			arrEven[countEven] = n;
			countEven++;
		}
		else {
			arrOdd[countOdd] = n;
			countOdd++;
		}
		count++;

	}
	for (d = 1; d <= 10; d++) {

		printf("%d ", arrEven[d - 1]);

	}
	/* Stores arrays into pointers */
	even = arrEven;
	odd = arrOdd;
	calcEven(even, 10);
	/* Displays sum and mean for arrEven */
	printf("\nEven Sum: %d \n", sum);
	printf("Even Mean: %d \n", mean);


	for (d = 1; d <= 10; d++) {
		printf("%d ", arrOdd[d - 1]);
	}

	calcOdd(odd, 10);

	return 0;

}

/* Calculates the sum and mean for arrEven */
void calcEven(int *arrPtr, int arrLength) {
	int d;
	for (d = 1; d <= 10; d++) {
		sum = sum + arrPtr[d - 1];
	}
	mean = sum / arrLength;
}
/* Calculates the sum and mean for arrOdd and displays results */
void calcOdd(int *arrPtr, int arrLength) {
	int d;
	sum = 0;
	for (d = 1; d <= 10; d++) {
		sum = sum + arrPtr[d - 1];
	}
	mean = sum / arrLength;
	printf("\nOdd Sum: %d \n", sum);
	printf("Odd Mean: %d \n", mean);
}

