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

static wchar_t sbuf[LINE_MAX];
static size_t buf[BUF_MAX]; // buf[0] - bytes, buf[1] - chars,
					  		// buf[2] - words, buf[3] - lines
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
			memset(buf, 0, sizeof(buf));
			fclose(fp);
		}

		return 0;
	}

	while (fgetws(sbuf, LINE_MAX, stdin))
	{
		coun(sbuf);
		cprintf(flags);
		memset(buf, 0, sizeof(buf));
	}

	return 0;
}

void coun(wchar_t *s)
{
	bool isword = false;
	char mbuf[MB_CUR_MAX];

	while (*s)
	{
		if (*s == '\n') buf[LINES]++;

		if (iswspace(*s) && isword)
		{
			isword = false;
			buf[WORDS]++;
		}
		else
		{
			isword = true;
		}

		buf[CHARS]++;
		buf[BYTES] += wctomb(mbuf, *s++);
	}
}

void cprintf(size_t flags)
{
	if (flags & ARG_BYTE)
	{
		printf("%7ldb", buf[BYTES]);
	}

	if (flags & ARG_CHAR)
	{
		printf("%7ldc", buf[CHARS]);
	}

	if (flags & ARG_WORD)
	{
		printf("%7ldw", buf[WORDS]);
	}

	if (flags & ARG_LINE)
	{
		printf("%7ldl", buf[LINES]);
	}
}
