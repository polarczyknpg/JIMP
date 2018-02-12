#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define MAX_STRING_SIZE 256

enum ArgumentType {CHAR, STRING, INT, DOUBLE};

void clearBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

int intLength(int n)
{
	int length = 0;
	if (n==0)
		return 1;
	while (n>0)
	{
		length++;
		n = n/10;
	}
	return length;
}

void printInt(int n, unsigned width)
{
	int size = intLength(n);
	if (size > width)
	{
		printf("%d\n", n);
		return;
	}
	int middle = width/2;
	int numHalf = size/2;
	int space = middle - numHalf;
	for (int i = 0; i<space; i++)
	{
		printf(" ");
	}
	printf("%d", n);
}

void printString(char* string, unsigned width)
{
	int length = strlen(string);
	if (length > width)
	{
		printf("%s\n", string);
		return;
	}
	int middle = width/2;
	int numHalf = length/2;
	int space = middle - numHalf;
	for (int i = 0; i<space; i++)
	{
		printf(" ");
	}
	printf("%s", string);
}

void printChar(char chr, unsigned width)
{
	int middle = width/2;
	for (int i = 0; i<middle; i++)
	{
		printf(" ");
	}
	printf("%c", chr);
}

void printDouble(double s, unsigned width)
{
	int length;
	int intDouble;
	char *string;
	if ((double)((int)s) == s)
	{
		intDouble = (int)s;
		length = intLength(s);
		string = malloc((length+1)*sizeof(char));
		for (int i = length-1; i>=0; i--)
		{
			string[i] = intDouble%10 + 48;
			intDouble/=10;
		}
	}
	else
	{
		intDouble = (int)(s*100);
		length = intLength(intDouble);
		string = malloc((length+1)*sizeof(char));
		for (int i = length; i>=0; i--)
		{
			if (i == length - 2)
			{
				string[i] = '.';
				continue;
			}
			string[i] = intDouble%10 + 48;
			intDouble/=10;
		}
		if (string[length] == 48)
		{
			if (string[length-1] == 48)
				string[length-2] = '\0';
			else
				string[length] = '\0';
		}
	}
	int space = (width-strlen(string))/2;
	for (int i = 0; i<space; i++)
		printf(" ");
	printf("%s", string);
}

double strToDouble(char *str)
{
	int dotPos = -1;
	double x = 0;
	for (int i = 0; i<strlen(str); i++)
	{
		if (*(str+i) == '.')
			dotPos = i;
	}
	if (dotPos == -1)
		dotPos = strlen(str)-1;
	for (int i = 0; i<strlen(str)-1; i++)
	{
		if (i!=dotPos)
		{
			int power = dotPos - i;
			if (power>0)
				power--;
			double digit = (str[i] - 48) * pow(10, power);
			x += digit;
		}
	}
	return x;
}

int printArgumentInTheMiddle(void* argument, enum ArgumentType type, unsigned width)
{
	if (argument == NULL)
	{
		printf("\n");
		return 0;
	}
	else if (type == STRING)
		printString((char*)argument, width);
	else if (type == INT)
		printInt(*(int*)argument, width);
	else if (type == CHAR)
		printChar(*(char*)argument, width);
	else if (type == DOUBLE)
		printDouble(*(double*)argument, width);
	return;
}


int main()
{
    while (1)
    {
    	struct winsize window;
    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
    	int width = window.ws_col;

        system("clear");
        printf("Wybierz typ argumentu:\n");
        printf("1. Liczba calkowita\n");
        printf("2. Liczba zmiennoprzecinkowa\n");
        printf("3. Znak\n");
        printf("4. Tekst\n");
        printf("0. Zakoncz\n");
        
        enum ArgumentType type;
        
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            	type = INT;
            	system("clear");
            	printf("Wprowadz liczbe calkowita:\n");
            	int num;
            	scanf("%d", &num);
                getchar();
            	printArgumentInTheMiddle(&num, type, width);
                printf("\nWcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
                break;
 
            case 2:
            	type = DOUBLE;
            	system("clear");
            	printf("Wprowadz tekst:\n");
            	char* dbtxt = malloc(MAX_STRING_SIZE);
            	double db;
            	if (dbtxt == NULL)
            	{
            		printf("Za malo pamieci!");
            		return 1;
            	}
            	clearBuffer();
            	fgets(dbtxt, MAX_STRING_SIZE, stdin);
            	db = strToDouble(dbtxt);
            	printArgumentInTheMiddle(&db, type, width);
                printf("\nWcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
                break;

            case 3:
            	type = CHAR;
            	system("clear");
            	printf("Wprowadz znak:\n");
            	char sign;
                getchar();
                sign = fgetc(stdin);
            	if (sign == EOF || sign == '\n')
            	{
            		printf("Blad!");
            	}
            	else
        			printArgumentInTheMiddle(&sign, type, width);
                clearBuffer();
                printf("\nWcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
                break;

            case 4:
            	type = STRING;
            	system("clear");
            	printf("Wprowadz tekst:\n");
            	char* text = malloc(MAX_STRING_SIZE);
            	if (text == NULL)
            	{
            		printf("Za malo pamieci!");
            		return 1;
            	}
                getchar();
            	fgets(text, MAX_STRING_SIZE, stdin);
            	printArgumentInTheMiddle(text, type, width);
                printf("\nWcisnij dowolny przycisk, aby kontynuowac...");
                getchar();
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
