#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>
#include <string.h>
#include "arg.h"

#define BYTES 0
#define CHARS 1
#define WORDS 2
#define LINES 3
#define BUF_MAX 4

static size_t buf[BUF_MAX]; // buf[0] - bytes, buf[1] - chars,
					  		// buf[2] - words, buf[3] - lines

int main(int argc, char *argv[])
{
	setlocale(LC_CTYPE, "");

	wint_t c;
	FILE *fp = stdin;
	bool isword = false;
	char mbuf[MB_CUR_MAX];

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
				fprintf(stderr, "file errro\n");
				fclose(fp);
				return -1;
			}

			while ((c = fgetwc(fp)) != WEOF)
			{
				if (c == '\n') buf[LINES]++;

				if (iswspace(c) && isword)
				{
					isword = false;
					buf[WORDS]++;
				}
				else
				{
					isword = true;
				}

				buf[CHARS]++;
				buf[BYTES] += wctomb(mbuf, c);
			}

			printf("file\tbytes\tchars\twords\tlines\n");
			printf("%s\t%ld\t%ld\t%ld\t%ld\n", ps, buf[0], buf[1], buf[2], buf[3]);
			memset((void *)buf, 0, sizeof(buf));
		}
	}

	return 0;
}
