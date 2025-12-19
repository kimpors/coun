#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include "error.h"
#include "coun.h"
#include "arg.h"

static wchar_t sbuf[LINE_MAX];

int main(int argc, char *argv[])
{
	setlocale(LC_CTYPE, "");

	FILE *fp = stdin;
	Result temp = { 0 };
	Result total = { 0 }, res = { 0 };
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
			 	temp = coun(sbuf);
				res.bytes += temp.bytes;
				res.chars += temp.chars;
				res.words += temp.words;
				res.lines += temp.lines;
			}

			total.bytes += res.bytes;
			total.chars += res.chars;
			total.words += res.words;
			total.lines += res.lines;

			cprint(res, flags & ARG_TOTAL ? flags ^ ARG_TOTAL : flags);

			flags & ARG_FILE
				? printf("\t%s\n", ps)
				: putchar('\n');
			fclose(fp);
		}

		if (flags & ARG_TOTAL) cprint(total, flags);
		return 0;
	}

	while (fgetws(sbuf, LINE_MAX, stdin))
	{
		res = coun(sbuf);
		total.bytes += res.bytes;
		total.chars += res.chars;
		total.words += res.words;
		total.lines += res.lines;

		wchar_t *ps = sbuf;
		while (*ps != '\n') ps++;
		*ps = '\0';

		cprint(res, flags & ARG_TOTAL ? flags ^ ARG_TOTAL: flags);
		printf("\t%ls\n", sbuf);
	}

	if (flags & ARG_TOTAL) cprint(total, flags);
	return 0;
}
