#include <stdio.h>

void test(int &x, int &y)
{
	int z = x;
	x = y;
	y = z;
}
int main()
{
	int first = 2;
	int second = 4;

	test(first, second);

	printf("first : %d | second : %d\n", first, second);
	return 0;
}
