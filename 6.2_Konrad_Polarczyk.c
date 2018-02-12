#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define HIGHCOL "\x1B[91m"
#define DAYCOL "\x1B[96m"
#define NORMAL "\x1B[97m"

int mod(int a, int b)
{
    int x = a%b;
    return x < 0 ? x+b : x;
}
 
int monthLength(int month, int year)
{
    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return month == 1 ? (year%4 ? months[month]: 29) : months[month];
}
 
int digitsNumb(int number)
{
    int digits = 0;
    while (number > 0)
    {
        number/=10;
        digits++;
    }
    return digits;
}

void prtHead(int month, int year)
{
	char* months[] = {"JANUARY", "FEBRUARY", "MARCH",
				"APRIL", "MAY", "JUNE", "JULY", 
				"AUGUST", "SEPTEMBER", "OCTOBER",
				"NOVEMBER", "DECEMBER"};
	printf("%s", months[month-1]);
	for (int i = 0; i<23-strlen(months[month-1]); i++)
		printf(" ");
	printf("%d", year);
	printf("\n\n");
}

void drawDays()
{
	printf("%s", DAYCOL);
    char days[7][3] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    for (int i = 0; i<7; i++)
    {
        for (int k = 0; k<3; k++)
            printf("%c", days[i][k]);
        printf(" ");
    }
	printf("%s", NORMAL);
    printf("\n");
}
 
void drawMonth(int month, int year, int highlight)
{
  time_t rawtime;
  struct tm * firstDay;
 
  time (&rawtime);
 
  firstDay = localtime (&rawtime);
  firstDay->tm_year = year - 1900;
  firstDay->tm_mon = month-1;
  firstDay->tm_mday = 1;
  mktime(firstDay);
 
  int size = monthLength(firstDay ->tm_mon, 1900+firstDay ->tm_year);
	system("clear");
	prtHead(month, year);

  drawDays();
 
  int weekday = firstDay->tm_wday-1;
	weekday = mod(weekday, 7);
  int space = weekday;
  for (int i = 0; i<space; i++)
    printf("    ");
 
  for (int i = 1; i<size+1; i++)
  {
    if (weekday>6)
    {
        weekday = mod(weekday, 7);
        printf("\n");
    }
	if (i!=highlight)
    	printf("%d  ", i);
	else
	{
		printf("%s%d  ", HIGHCOL, i);
		printf("%s", NORMAL);
	}
    for (int k = digitsNumb(i); k<2; k++)
        printf(" ");
    weekday++;
  }
}
 
int main()
{
	printf("%s", NORMAL);
    int exit = 0;
    while (!exit)
    {
        system("clear");
        printf("Wybierz opcje:\n");
        printf("1. Wyswietl aktualny miesiac\n");
        printf("2. Wybierz miesiac\n");
        printf("0. Zakoncz\n");
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                system("clear");
				time_t now;
		  		struct tm * struc;
				time(&now);
				struc = localtime(&now);

                drawMonth(struc->tm_mon+1, struc->tm_year+1900, struc->tm_mday);
                printf("\n\nWcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
                getchar();
                break;
 
            case 2:
                system("clear");
                printf("Podaj miesiac:\n");
                int month;
                scanf("%d", &month);
                printf("Podaj rok:\n");
                int year;
                scanf("%d", &year);
                drawMonth(month, year, 0);
                printf("\n\nWcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
                getchar();
                break;

            case 0:
                return 0;
 
            default:
                system("clear");
                printf("Podano niewlasciwy znak");
                printf("\n\nWcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
                getchar();
                break;
        }
        printf("\n");
    }
}
