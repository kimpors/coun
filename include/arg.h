#pragma once
#include <stdio.h>

#define ARG_HELP	(1 << 0)
#define ARG_FILE	(1 << 1)
#define ARG_ERROR	(1 << 8)

void help(void);
char *pop(void);
char *peek(void);
size_t argeval(int argc, char *argv[]);
