#include "arg.h"

int main(int argc, char *argv[])
{
	return argeval(argc, argv) & ARG_ERROR;
}
