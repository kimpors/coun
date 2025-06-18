#include <string.h>
#include "arg.h"

char *pop(void);
char *peek(void);
char *push(char *s);

// evaluate arguments and returns flags
size_t argeval(int argc, char *argv[])
{
	size_t flags = 0;

	while (--argc > 0 && ++argv)
	{
		if (strcmp(*argv, "--help") == 0)
		{
			flags |= ARG_HELP;
			return flags;
		}

		if ((!flags || flags & ARG_FILE) && **argv != '-')
		{
			flags |= ARG_FILE;
			push(*argv);
			continue;
		}
	}

	return flags;
}

void help(void)
{
	printf("hello from help\n");
}

#define BUF_MAX	12

struct {
	unsigned i; 		// index
	char *d[BUF_MAX];	// data
} buf;

char *push(char *s)
{
	if (buf.i > BUF_MAX - 1) return NULL;
	buf.d[buf.i] = s;
	// strcpy(buf.d[buf.i], s);
	return buf.d[buf.i++];
}

char *pop(void)
{
	if (buf.i < 1) return NULL;
	return buf.d[--buf.i];
}

char *peek(void)
{
	if (buf.i < 1 || buf.i > BUF_MAX - 1) return NULL;
	return buf.d[buf.i];
}
