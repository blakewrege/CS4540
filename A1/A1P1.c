
/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 1 - Problem 1
* Name: Blake Wrege
* E-mail: blake.j.wrege@wmich.edu
* Submitted: 01/01/2016
*************************************************/

#include<stdio.h>
#include<math.h>

main()
{
	/* Declare variables */
	float a, x, y, ans;
	int b, c, d, r;
	/* Prompt user for "a" until variable is within parameters */
	do {
		printf("a: ");
		scanf("%f", &a);
		if (a <= 1.1 || a >= 1.9)
			printf("Error: a must be 1.1 to 1.9\n");
	} while (a <= 1.1 || a >= 1.9);
	/* Prompt user for "b" until variable is within parameters */
	do {
		printf("b: ");
		scanf("%d", &b);
		if (b < 1 || b > 10)
			printf("Error: b must be 1 to 10\n");
	} while (b < 1 || b > 10);
	/* Prompt user for "c" until variable is within parameters */

	do {
		printf("c: ");
		scanf("%d", &c);
		if (c < 101 || c > 999)
			printf("Error: c must be greater than 100 and less than 1000\n");
	} while (c < 101 || c > 999);
	/* Prompt user for "d" until variable is within parameters */

	do {
		printf("d: ");
		scanf("%d", &d);
		if (d < 1 || d > 10)
			printf("Error: d must be 1 to 10\n");
	} while (d < 1 || d > 10);
	/* Prompt user for "r" until variable is within parameters */

	do {
		printf("r: ");
		scanf("%d", &r);
		if (r < (-100) || r > 100)
			printf("Error: r must be -100 to 100\n");
	} while (r < (-100) || r > 100);
	/* Prints variable results */

	printf("\na=%f b=%d c=%d d=%d r=%d\n", a, b, c, d, r);
	/* Calculates the function results */
	x = (3.14 * r * r + (10.7 * a)) / (4.11 * c);
	y = (b * c * d) / (5.11 * a);
	ans = (x + y) * (x + y);
	/* Displays the function results */
	printf("\nf(a,b,c,d,r) = %f\n", ans);
	return 0;
}