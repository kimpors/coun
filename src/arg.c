#include <string.h>
#include "arg.h"

size_t flags;

// evaluate arguments and returns flags
char *argeval(int argc, char *argv[])
{
	while (--argc > 0 && ++argv)
	{
		if (strcmp(*argv, "--help") == 0)
		{
			flags |= ARG_HELP;
			return NULL;
		}
	}

	return NULL;
}

void help(void)
{
	printf("hello from help\n");
}
