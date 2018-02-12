#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/*
Przy kompilacji pojawia się warning, który przeanalizowałem i pojawia się tylko dlatego,
że ilości argumentów nie podaję z góry, tylko ją liczę, co jest pożądane dla większej
estetyki. Nie znalazłem konkretnej flagi, by usunąć ten warning, ale jest nieszkodliwy.
*/ 

void input(const char* string, ...)
{
	int argc = 0;
	const char* ind;
	ind = string;
	int string_size = strlen(string);
	while (*ind != '\0')
	{
		if (*ind == '%')
			argc++;
		ind++;
	}
	va_list args;
	va_start(args, argc);
	ind = string;
	for (int i = 0; i<argc+1; i++)
	{
		char text[string_size];
		int size = 0;
		char sign = *ind;
		while(sign != '%' && sign != '\0')
		{
			text[size] = sign;
			size++;
			ind++;
			sign = *ind;
		}
		text[size] = '\0';
		printf("%s", text);
		if (i<argc)
		{
			int* var = va_arg(args, int*);
			scanf("%d", var);
		}
		ind+=2;
	}
	va_end(args);
}

int main()
{
	printf("Przykladowy program liczacy pole prostokata przy uzyciu funkcji input\n");
	int a, b;
	input("Podaj bok a:\n%dPodaj bok b:\n%d", &a, &b);
	printf("a = %d\nb = %d\n", a, b);
	printf("Pole = %d\n", a*b);
}
