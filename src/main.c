#include <stdio.h>
#include <ctype.h>
#include "arg.h"

size_t couword(char *s);
size_t couline(char *s);
size_t couchar(char *s);

int main(int argc, char *argv[])
{
	char *s = "\nhello there\n";

	printf("len: %ld\n", couchar(s));
	printf("words: %ld\n", couword(s));
	printf("lines: %ld\n", couline(s));

	argeval(argc, argv);

	if (flags & ARG_HELP)
	{
		help();
	}


	return 0;
}

// count chars
size_t couchar(char *s)
{
	char *ps = s;
	while (*ps++);
	return ps - s;
}

// count words
size_t couword(char *s)
{
	size_t w = 0;

	while (*s && !isalpha(*s)) s++;

	while (*s)
	{
		while (*s && isalpha(*s)) s++;
		if (*s) w++;
		while (*s && !isalpha(*s)) s++;
	}

	return w;
}

// count lines
size_t couline(char *s)
{
	size_t l = 0;

	while (*s)
	{
		if (*s++ == '\n') l++;
	}

	return l;
}
