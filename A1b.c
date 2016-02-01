#include <stdio.h>
#include <stdlib.h>

int main() {
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
	printf("\nTen random numbers in [1,26]\n");
	for (d = 1; d <= 10; d++) {
		n = rand() % 26 + 1;
		upperCase[count] = n;
		count++;

	}
	count = 0;

	for (d = 1; d <= 10; d++) {
		do {
			n = rand() % 26 + 1;
			lowerCase[count] = n;
		} while (n == upperCase[0] || n == upperCase[1] || n == upperCase[2] || n == upperCase[3] || n == upperCase[4] || n == upperCase[5] || n == upperCase[6] || n == upperCase[7] || n == upperCase[8] || n == upperCase[9]);
		count++;
	}

	for (d = 1; d <= 10; d++) {

		printf("%c ", charArray[upperCase[d - 1] - 1]);
	}
	printf("\n\n");
	for (d = 1; d <= 10; d++) {

		printf("%c ", tolower(charArray[lowerCase[d - 1] - 1]));

	}





	return 0;
}