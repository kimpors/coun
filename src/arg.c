#include <string.h>
#include <stdbool.h>
#include "arg.h"

bool isempty(void);
char *fpush(char *s);

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

		if (**argv != '-')
		{
			fpush(*argv);
			continue;
		}

		while (*++(*argv))
		{
			switch (**argv)
			{
				case 'b': flags |= ARG_BYTE;	break;
				case 'c': flags |= ARG_CHAR;	break;
				case 'w': flags |= ARG_WORD;	break;
				case 'l': flags |= ARG_LINE;	break;
				case 'h': flags |= ARG_HELP;	return flags;
				default:
						  fprintf(stderr, "wrong argument\n");
						  flags |= ARG_ERROR;
						  return flags;
			}
		}
	}

	if (!isempty()) flags |= ARG_FILE;
	return flags;
}

void help(void)
{
	printf("-h -> show help\n");
	printf("-b -> show bytes\n");
	printf("-c -> show chars\n");
	printf("-w -> show words\n");
	printf("-l -> show lines\n");
}

#define BUF_MAX	12

struct {
	unsigned i; 		// index
	char *d[BUF_MAX];	// data
} buf;

bool isempty(void)
{
	return !buf.i;
}

// push filename
char *fpush(char *s)
{
	if (buf.i > BUF_MAX - 1) return NULL;
	buf.d[buf.i] = s;
	// strcpy(buf.d[buf.i], s);
	return buf.d[buf.i++];
}

// pop filename
char *fpop(void)
{
	if (buf.i < 1) return NULL;
	return buf.d[--buf.i];
}

// peek filename
char *fpeek(void)
{
	if (buf.i < 1 || buf.i > BUF_MAX - 1) return NULL;
	return buf.d[buf.i];
}
