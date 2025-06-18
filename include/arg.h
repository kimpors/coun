#pragma once
#include <stdio.h>

#define ARG_HELP	(1 << 0)

extern size_t flags;

void help(void);
char *argeval(int argc, char *argv[]);
