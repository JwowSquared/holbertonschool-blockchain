#include "cli.h"

/**
*
*
*
*/
int main(void)
{
	EC_KEY *wallet;
	blockchain_t *bc;
	char *line = NULL, *cmd, *arg1, *arg2;
	size_t len;
	int (*func)(blockchain_t *, EC_KEY *, char *, char *);

	wallet = ec_create();
	bc = blockchain_create();

	while (1)
	{
		printf("bc$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
		line = strtok(line, "\n");
		cmd = strtok(line, " ");
		arg1 = strtok(NULL, " ");
		arg2 = strtok(NULL, " ");
		func = gumball(cmd);
		if (func)
			func(bc, wallet, arg1, arg2);
		else
			printf("unrecognized command\n");
	}

	return (0);
}
