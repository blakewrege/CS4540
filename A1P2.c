/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 1 - Problem 2
* Name: Blake Wrege
* E-mail: blake.j.wrege@wmich.edu
* Submitted: 01/01/2016
*************************************************/



#include <stdio.h>
#include <stdlib.h>

int main() {
	/* Declare variables */
	int d, n;
	int count = 0;
	time_t t;
	char charArray[26];
	int upperCase[10];
	int lowerCase[10];


	char c;
	for (c = 'A'; c <= 'Z'; ++c) {
		charArray[count] = c;
		count++;
	}

	/* Intializes random number generator */
	srand((unsigned) time(&t));
	count = 0;
	/* Stores numbers representing uppercase array */
	for (d = 1; d <= 10; d++) {
		n = rand() % 26 + 1;
		upperCase[count] = n;
		count++;

	}
	count = 0;
	/* Stores numbers representing lowercase array */
	for (d = 1; d <= 10; d++) {
		do {
			n = rand() % 26 + 1;
			lowerCase[count] = n;
			/* Ensures that lowerCase contains no elements in upperCase */
		} while (n == upperCase[0] || n == upperCase[1] || n == upperCase[2] || n == upperCase[3] || n == upperCase[4] || n == upperCase[5] || n == upperCase[6] || n == upperCase[7] || n == upperCase[8] || n == upperCase[9]);
		count++;
	}
	/* Displays uppercase */
	printf("\nTen random chars from A to Z\n");
	for (d = 1; d <= 10; d++) {

		printf("%c ", charArray[upperCase[d - 1] - 1]);
	}
	/* Displays lowercase */
	printf("\nTen random chars from a to z\n");
	for (d = 1; d <= 10; d++) {

		printf("%c ", tolower(charArray[lowerCase[d - 1] - 1]));

	}

	return 0;
}