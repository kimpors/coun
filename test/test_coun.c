#include "coun.h"
#include "error.h"
#include <locale.h>

static wchar_t sbuf[LINE_MAX];

int main(int argc, char *argv[])
{
	setlocale(LC_CTYPE, "");

	if (argc < 5) 
	{
		ERROR_MSG("minimum 4 arguments");
		return -1;
	}

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
		ERROR_MSG("bytes %ld:%ld", a.bytes, b.bytes);
		ERROR_MSG("chars %ld:%ld", a.chars, b.chars);
		ERROR_MSG("words %ld:%ld", a.words, b.words);
		ERROR_MSG("lines %ld:%ld", a.lines, b.lines);

		return -1;
	}

	return 0;
}
