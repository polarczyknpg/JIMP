#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

float average(int* start, int* end)
{
	float sum = 0;
	float divider = 0;
	for (int i=0; i<=(int)(end - start);i++)
	{
		float var = *(start+i);
		sum+=var*i;
		divider += i;
	}
	float result = sum/divider;
	return (result);
}

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

void prtAvg(int* beginning, int size)
{
	float avg;
	avg = average(beginning, beginning+size-1);
	system("clear");
	printf("Podgląd:\n");
	prt(beginning, size);
	printf("\n\nSrednia wazona wynosi: %f", avg);
	printf("\n\nWcisnij dowolny przycisk, aby kontynuowac...");
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
        printf("3. Oblicz srednia wazona\n");
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
				prtAvg(tab, tabSize);
                break;

            case 0:
                return 0;
 
            default:
                system("clear");
                printf("Podano niewlasciwy znak");
                printf("\nWcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
                getchar();
                break;
        }
        printf("\n");
    }
}
