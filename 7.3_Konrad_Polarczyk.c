#include <stdio.h>

void sort(int** b, int size)
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i=0; i<size-1; i++)
		{
			if(**(b+i) > **(b+i+1))
			{
				int* temp = *(b+i+1);
				*(b+i+1) = *(b+i);
				*(b+i) = temp;
				flag = 1;
			}
		}
	}
}

void prt_b(int** beginning, int size)
{
	printf("[");
	for (int i = 0; i<size; i++)
	{
		printf("%d", **(beginning + i));
		if (i < size-1)
			printf(", ");
	}
	printf("]\n");
}

void prt_a(int* beginning, int size)
{
	printf("[");
	for (int i = 0; i<size; i++)
	{
		printf("%d", *(beginning + i));
		if (i < size-1)
			printf(", ");
	}
	printf("]\n");
}

int main()
{
	int a[] = {4, -2, 6, -7, 0, 2, 9, 5, -3, -5};
	int* b[10];
	for (int i=0; i<10; i++)
	{
		b[i] = a + i;
	}
	printf("Poczatkowa tablica A:\n");
	prt_a(a, 10);
	sort(b, 10);
	printf("Posortowana tablica A:\n");
	prt_b(b, 10);
	printf("Sprawdzenie ukladu tablicy A:\n");
	prt_a(a, 10);
}
