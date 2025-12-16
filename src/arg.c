#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "dirent.h"
#include "error.h"
#include "arg.h"

bool isempty(void);
void patheval(char *path);

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

		if (**argv != '-' && **argv != '\0')
		{
			patheval(*argv);
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
				case 't': flags |= ARG_TOTAL; 	break;
				case 'h': flags |= ARG_HELP;	return flags;
				default:
						  ERROR_MSG("wrong argument: %s -> %c", *argv, **argv);
						  flags |= ARG_ERROR;
						  return flags;
			}
		}
	}

	if (!flags || flags == ARG_TOTAL)
	{
		flags |= ARG_CHAR;
		flags |= ARG_WORD;
		flags |= ARG_LINE;
	}

	if (!isempty()) flags |= ARG_FILE;
	return flags;
}

void help(void)
{
	printf("Usage:\n\tcoun [args?] [files?]\n\n");

	printf("Options:\n");
	printf("\t-b\t\t\t| Show only bytes\n");
	printf("\t-c\t\t\t| Show only chars\n");
	printf("\t-w\t\t\t| Show only words\n");
	printf("\t-l\t\t\t| Show only lines\n");
	printf("\t-t\t\t\t| Show sum of all files/items\n");
	printf("\t-h\t\t\t| Show help\n");
	printf("\t--help\t\t\t| Show help\n");

	printf("Examples:\n");
	printf("\tcoun --help\t\t| Will show help\n");
	printf("\tcoun\t\t\t| Will read from stdin\n");
	printf("\tcoun file.txt\t\t| Will read from file\n");
	printf("\tcoun -bwl file.txt\t| Will read from file and show bytes, words and lines\n");
}

char *fpush(char *s);
void dirwalk(char *dir, void (*fcn)(char *));

void patheval(char *path)
{
	struct stat stbuf;
	if (stat(path, &stbuf) == -1)
	{
		ERROR_MSG("can't access %s", path);
		return;
	}

	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
	{
		dirwalk(path, patheval);
		return;
	}

	fpush(path);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH] = { 0 };
	struct dirent *dp;
	DIR *dfd;

	if (!(dfd = opendir(dir)))
	{
		ERROR_MSG("can't open %s", dir);
		return;
	}

	while ((dp = readdir(dfd)))
	{
		if (strcmp(dp->d_name, ".") == 0 ||
			strcmp(dp->d_name, "..") == 0)
		{
			continue;
		}

		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
		{
			ERROR_MSG("name %s %s too long", dir, dp->d_name);
		}
		else 
		{
			dir[strlen(dir) - 1] == '/'
				? sprintf(name, "%s%s", dir, dp->d_name)
				: sprintf(name, "%s/%s", dir, dp->d_name);

			(*fcn)(name);
		}
	}

	closedir(dfd);
}


#define BUF_MAX	256

static struct {
	unsigned i; 				// index
	char d[BUF_MAX][LINE_MAX];	// data
} buf;

bool isempty(void)
{
	return !buf.i;
}

// push filename
char *fpush(char *s)
{
	if (buf.i > BUF_MAX - 1) return NULL;
	strcpy(buf.d[buf.i], s);
	return buf.d[buf.i++];
}

// pop filename
char *fpop(void)
{
	if (buf.i < 1) return NULL;
	return buf.d[--buf.i];
}
