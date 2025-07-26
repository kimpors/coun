#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>
#include <string.h>
#include "error.h"
#include "arg.h"

#define BYTES		0
#define CHARS		1
#define WORDS		2
#define LINES 		3
#define BUF_MAX 	4

static struct {
	size_t bytes;
	size_t chars;
	size_t words;
	size_t lines;
} buf;

static wchar_t sbuf[LINE_MAX];

void coun(wchar_t *s);
void cprintf(size_t flags);

int main(int argc, char *argv[])
{
	setlocale(LC_CTYPE, "");

	wint_t c;
	FILE *fp = stdin;
	bool isword = false;
	char mbuf[MB_CUR_MAX];

	size_t flags = argeval(argc, argv);

	if (flags & ARG_ERROR) return -1;
	else if (flags & ARG_HELP)
	{
		help();
		return 0;
	}

	if (flags & ARG_FILE)
	{
		char *ps;
		while ((ps = fpop()))
		{
			if (!(fp = fopen(ps, "r")))
			{
				ERROR_MSG("can't open file: %s", ps);
				return -1;
			}

			while (fgetws(sbuf, LINE_MAX, fp))
			{
			 	coun(sbuf);
			}

			cprintf(flags);
			flags & ARG_FILE
				? printf("\t%s\n", ps)
				: putchar('\n');
			memset(&buf, 0, sizeof(buf));
			fclose(fp);
		}

		return 0;
	}

	while (fgetws(sbuf, LINE_MAX, stdin))
	{
		coun(sbuf);
		cprintf(flags);
		memset(&buf, 0, sizeof(buf));
	}

	return 0;
}

void coun(wchar_t *s)
{
	bool isword = false;
	char mbuf[MB_CUR_MAX];

	while (*s)
	{
		if (*s == '\n') buf.lines++;

		if (iswspace(*s) && isword)
		{
			isword = false;
			buf.words++;
		}
		else
		{
			isword = true;
		}

		buf.chars++;
		buf.bytes += wctomb(mbuf, *s++);
	}
}

void cprintf(size_t flags)
{
	if (flags & ARG_BYTE)
	{
		printf("%7ldb", buf.bytes);
	}

	if (flags & ARG_CHAR)
	{
		printf("%7ldc", buf.chars);
	}

	if (flags & ARG_WORD)
	{
		printf("%7ldw", buf.words);
	}

	if (flags & ARG_LINE)
	{
		printf("%7ldl", buf.lines);
	}
}
