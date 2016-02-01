#include<stdio.h>
#include<math.h>

main()
{
	float a, x, y, ans;
	int b, c, d, r;
	do {
		printf("a: ");
		scanf("%f", &a);
		if (a <= 1.1 || a >= 1.9)
			printf("Error: a must be 1.1 to 1.9\n");
	} while (a <= 1.1 || a >= 1.9);

	do {
		printf("b: ");
		scanf("%d", &b);
		if (b < 1 || b > 10)
			printf("Error: b must be 1 to 10\n");
	} while (b < 1 || b > 10);

	do {
		printf("c: ");
		scanf("%d", &c);
		if (c < 101 || c > 999)
			printf("Error: c must be greater than 100 and less than 1000\n");
	} while (c < 101 || c > 999);

	do {
		printf("d: ");
		scanf("%d", &d);
		if (d < 1 || d > 10)
			printf("Error: d must be 1 to 10\n");
	} while (d < 1 || d > 10);

	do {
		printf("r: ");
		scanf("%d", &r);
		if (r < (-100) || r > 100)
			printf("Error: r must be -100 to 100\n");
	} while (r < (-100) || r > 100);

	printf("\na=%f b=%d c=%d d=%d r=%d\n", a, b, c, d, r);
	x = (3.14 * r * r + (10.7 * a)) / (4.11 * c);
	y = (b * c * d) / (5.11 * a);
	ans = (x + y) * (x + y);
	printf("\nf(a,b,c,d,r) = %f\n", ans);
  return 0;
}