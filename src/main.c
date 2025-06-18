#include <locale.h>
#include <stdio.h>
#include <ctype.h>
#include <wchar.h>
#include "arg.h"

#define LINE_MAX 1024

static char sbuf[LINE_MAX];

size_t couword(char *s);
size_t couline(char *s);
size_t couchar(char *s);
size_t coubyte(char *s);

int main(int argc, char *argv[])
{
	setlocale(LC_CTYPE, "");
	FILE *fp = stdin;
	size_t chars = 0;
	size_t words = 0;
	size_t lines = 0;
	size_t bytes = 0;

	size_t flags = argeval(argc, argv);

	if (flags & ARG_HELP)
	{
		help();
	}
	else if (flags & ARG_FILE)
	{
		char *ps;
		while ((ps = pop()))
		{
			if (!(fp = fopen(ps, "r")))
			{
				fprintf(stderr, "file errro");
				fclose(fp);
				return -1;
			}

			while (fgets(sbuf, LINE_MAX, fp))
			{
				bytes += coubyte(sbuf);
				chars += couchar(sbuf);
				words += couword(sbuf);
				lines += 1;
			}

			printf("file: %s\n", ps);
			printf("bytes: %ld\n", bytes);
			printf("chars: %ld\n", chars);
			printf("words: %ld\n", words);
			printf("lines: %ld\n", lines);

			bytes = chars = words = lines = 0;
		}
	}

	return 0;
}

size_t coubyte(char *s)
{
	size_t b = 0;
	while (*s) 
	{
		b += sizeof(*s);
		s++;
	}
	return b;
}

// count chars
size_t couchar(char *s)
{
	char *ps = s;
	while (*ps++);
	return ps - s - 1;
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
