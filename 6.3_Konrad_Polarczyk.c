#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
 

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

void draw(int* beginning, int size)
{
    system("clear");
	for (int i = 0; i<size; i++)
	{
		*(beginning + i) = rand()%101-50;
	}
    printf("Pomyslnie wylosowano tablice!\n\n");
	prt(beginning, size);
    printf("\n\nWcisnij dowolny przycisk, aby kontynuowac...");
    getchar();
    getchar();
}

void average(int* beginning, int size)
{
    system("clear");
	printf("Podgląd:\n");
	prt(beginning, size);
	printf("\n\n");

	int sum = 0;
	for (int i = 0; i<size; i++)
	{
		sum += *(beginning + i);
	}
	double average = (float)sum/size;
	printf("Srednia wynosi: %f", average);
    printf("\n\nWcisnij dowolny przycisk, aby kontynuowac...");
    getchar();
    getchar();
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

void median(int* beginning, int size)
{
    system("clear");
	int tempTab[size];
	sort(beginning, tempTab, size);
	printf("Posortowana tablica:\n\n");
	prt(tempTab, size);

	float med;
	if (size%2==0)
	{
		med = (float)(tempTab[size/2] + tempTab[size/2-1])/2.f;
	}
	else
	{
		med = (float)(tempTab[(size-1)/2]);
	}
	printf("\n\nMediana wynosi: %f", med);
    printf("\n\nWcisnij dowolny przycisk, aby kontynuowac...");
    getchar();
    getchar();
}

int min(int* beginning, int size)
{
	int tempTab[size];
	sort(beginning, tempTab, size);
	return tempTab[0];
}

int max(int* beginning, int size)
{
	int tempTab[size];
	sort(beginning, tempTab, size);
	return tempTab[size-1];
}

void minMax(int* beginning, int size)
{
	system("clear");
	printf("Podgląd:\n");
	prt(beginning, size);
	printf("\n\n");
	printf("Najmniejszy element: %d\n\n", min(beginning, size));
	printf("Najwiekszy element: %d\n\n", max(beginning, size));
	printf("Wcisnij dowolny przycisk, aby kontynuowac...");
	getchar();
	getchar();
}
 
int main()
{
	srand(time(NULL));
	int tabSize = 10;
	int tab[tabSize];
	for (int i = 0; i<10; i++)
	{
		tab[i] = 0;
	}

    while (1)
    {
        system("clear");
        printf("Wybierz opcje:\n");
        printf("1. Losuj nowa tablice\n");
        printf("2. Wyswietl tablice\n");
        printf("3. Oblicz srednia\n");
        printf("4. Oblicz mediane\n");
        printf("5. Oblicz maks. i min. element\n");
        printf("0. Zakoncz\n");
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
				draw(tab, tabSize);
                break;
 
            case 2:
   				system("clear");
				printf("Podgląd:\n");
				prt(tab, tabSize);
				printf("\n\nWcisnij dowolny przycisk, aby kontynuowac...");
				getchar();
				getchar();
                break;

            case 3:
				average(tab, tabSize);
                break;

            case 4:
				median(tab, tabSize);
                break;

            case 5:
				minMax(tab, tabSize);
                break;

            case 0:
                return 0;
 
            default:
                system("clear");
                printf("Podano niewlasciwy znak");
                printf("\n Wcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
                getchar();
                break;
        }
        printf("\n");
    }
}
