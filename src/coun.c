#include <stdbool.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include "coun.h"
#include "arg.h"

static wchar_t sbuf[LINE_MAX];

Result coun(wchar_t *s)
{
	bool isword = false;
	char mbuf[MB_CUR_MAX];
	Result res = { 0 };

	while (*s)
	{
		if (*s == '\n') res.lines++;

		if (iswspace(*s) && isword)
		{
			isword = false;
			res.words++;
		}
		else
		{
			isword = true;
		}

		res.chars++;
		res.bytes += wctomb(mbuf, *s++);
	}

	if (isword) res.words++;
	return res;
}

void cprintf(Result res, size_t flags)
{
	if (flags & ARG_TOTAL)
	{
		printf("Total:");
		if (flags & ARG_BYTE) printf("%7ldb", res.bytes);
		if (flags & ARG_CHAR) printf("%7ldc", res.chars);
		if (flags & ARG_WORD) printf("%7ldw", res.words);
		if (flags & ARG_LINE) printf("%7ldl", res.lines);		
		return;
	}

	if (flags & ARG_BYTE)
	{
		printf("%7ldb", res.bytes);
	}

	if (flags & ARG_CHAR)
	{
		printf("%7ldc", res.chars);
	}

	if (flags & ARG_WORD)
	{
		printf("%7ldw", res.words);
	}

	if (flags & ARG_LINE)
	{
		printf("%7ldl", res.lines);
	}
}
