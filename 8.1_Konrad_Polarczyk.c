#include <stdio.h>
#include <stdlib.h>

void prt(int* beginning, int size)
{
	printf("[");
	for (int i = 0; i<size; i++)
	{
		printf("%d", *(beginning + i));
		if (i < size-1)
			printf(", ");
	}
	printf("]");
}

int sum(int* beginning, int size)
{
	int sum = 0;
	for (int i = 0; i<size; i++)
	{
		sum += *(beginning + i);
	}
	return sum;
}

float average(int* beginning, int size)
{
	int sum = 0;
	for (int i = 0; i<size; i++)
	{
		sum += *(beginning + i);
	}
	double average = (float)sum/size;
	return average;
}


void sort(int* src, int* dest, int size)
{
	int destSize = 0;
	for (int i = 0; i<size; i++)
	{
		int k = 0;
		while (k<destSize && *(dest+k) <= *(src+i))
			k++;
		for (int j = size-1; j>=k; j--)
			*(dest+j) = *(dest+(j-1));
		*(dest+k) = *(src+i);
		destSize++;
	}
}

float median(int* beginning, int size)
{
	int tempTab[size];
	sort(beginning, tempTab, size);

	float med;
	if (size%2==0)
	{
		med = (float)(tempTab[size/2] + tempTab[size/2-1])/2.f;
	}
	else
	{
		med = (float)(tempTab[(size-1)/2]);
	}
	return med;
}

void printHex(int num)
{
	char hex[100];
	int i = 0;
	while (num>=1)
	{
		int digit = num%16;
		if (digit<10)
			hex[i] = digit+48;
		else
			hex[i] = digit+55;
		num = num/16;
		i++;
	}
	for (int j = i-1; j>=0; j--)
		printf("%c", hex[j]);
	printf("\n");
}

void printOct(int num)
{
	char oct[100];
	int i = 0;
	while (num>=1)
	{
		int digit = num%8;
		oct[i] = digit+48;
		num = num/8;
		i++;
	}
	for (int j = i-1; j>=0; j--)
		printf("%c", oct[j]);
	printf(" ");
}

int main()
{
	printf("Wprowadz liczby. Aby zakonczyc wprowadzanie wcisnij Ctrl+D.\n");
	int number;
	int size = 0;
	int* tab = malloc(size);
	while (scanf("%d", &number) != EOF)
	{
		size += 1;
		tab = realloc(tab, size * sizeof(int));
		if (tab == NULL)
		{
			printf("Niewystarczajaca ilosc pamieci!");
			return 0;
		}
		tab[size-1] = number;
	}
	if (!size)
	{
		printf("Nie podano zadnej liczby!\n");
		return 0;
	}
	int sumary = sum(tab, size);
	float med = median(tab, size);
	float avg = average(tab, size);
	printf("Suma: %d ", sumary);
	printOct(sumary);
	printHex(sumary);
	printf("\n");
	printf("Srednia: %f ", avg);
	if (avg == (int)avg)
	{
		printOct(avg);
		printHex(avg);
	}
	printf("\n");
	printf("Mediana: %f ", med);
	if (med == (int)med)
	{
		printOct(med);
		printHex(med);
	}
	printf("\n");
}
