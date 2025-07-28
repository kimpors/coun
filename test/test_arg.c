#include "arg.h"
#include "error.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 3) 
	{
		ERROR_MSG("minimum 2 arguments")
		return -1;
	}

	ERROR_MSG("argc: %d", argc);
	ERROR_MSG("expected: %s", argv[1]);
	ERROR_MSG("arg: %s", argv[2]);

	return argeval((argc - 2), (argv + 2)) & atoi(argv[1]);
}
