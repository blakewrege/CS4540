#include <stdio.h>
#include <stdlib.h>

int sum = 0;
int mean = 0;

void calcEven(int* arrPtr, int arrLength);

void calcOdd(int* arrPtr, int arrLength);

int main() {
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
//		printf("%d | %d\n", count + 1, n );
		count++;

	}
	for (d = 1; d <= 10; d++) {

//		printf("%d ", arrEven[d - 1]);

	}
	for (d = 1; d <= 10; d++) {

//		printf("%d ", arrOdd[d - 1]);

	}
//	printf("\n");


	even = arrEven;
	odd = arrOdd;
	calcEven(even, 10);
	printf("\nEven Sum: %d \n", sum);
	printf("Even Mean: %d \n", mean);
	calcOdd(odd, 10);

}


void calcEven(int *arrPtr, int arrLength) {
	int d;
	for (d = 1; d <= 10; d++) {
		sum = sum + arrPtr[d - 1];
	}
	mean = sum / arrLength;
}

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

