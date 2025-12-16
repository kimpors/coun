#include <stdlib.h>
#define LINE_MAX	1024

typedef struct {
	size_t bytes;
	size_t chars;
	size_t words;
	size_t lines;
} Result;

Result coun(wchar_t *s);
void cprint(Result res, size_t flags);
