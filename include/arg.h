#pragma once
#include <stdio.h>

#define ARG_HELP	(1 << 0)
#define ARG_FILE	(1 << 1)
#define ARG_BYTE	(1 << 2)
#define ARG_CHAR	(1 << 3)
#define ARG_WORD	(1 << 4)
#define ARG_LINE	(1 << 5)
#define ARG_TOTAL	(1 << 6)
#define ARG_ERROR	(1 << 7)

#define LINE_MAX	1024

void help(void);
char *fpop(void);
size_t argeval(int argc, char *argv[]);
