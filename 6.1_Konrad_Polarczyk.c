#include <stdio.h>

int main()
{
	for (int i=0;i<256;i++)
	{
		char c = i;
		printf("%d - %c\n", i, c);
	}
}
