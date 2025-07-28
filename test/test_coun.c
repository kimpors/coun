#include "coun.h"
#include <stdio.h>

static wchar_t sbuf[LINE_MAX];

int main(int argc, char *argv[])
{
	if (argc < 5) return -1;

	Result a = { 
		atoi(argv[1]),
		atoi(argv[2]),
		atoi(argv[3]),
		atoi(argv[4])
	};

	mbstowcs(sbuf, argv[5], LINE_MAX);
	Result b = coun(sbuf);

	if (a.bytes != b.bytes ||
		a.chars != b.chars ||
		a.words != b.words ||
		a.lines != b.lines) 
	{
		printf("bytes %ld:%ld\n", a.bytes, b.bytes);
		printf("chars %ld:%ld\n", a.chars, b.chars);
		printf("words %ld:%ld\n", a.words, b.words);
		printf("lines %ld:%ld\n", a.lines, b.lines);

		return -1;
	}

	return 0;
}
