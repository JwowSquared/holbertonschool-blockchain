#include "cli.h"

/**
* main - entry point for CLI
*
* Return: always 0
*/
int main(void)
{
	EC_KEY *wallet;
	blockchain_t *bc;
	block_t *active;
	char *line = NULL, *cmd, *arg1, *arg2;
	size_t len;
	int (*func)(blockchain_t **, block_t **, EC_KEY **, char *, char *);

	wallet = ec_create();
	bc = blockchain_create();
	active = llist_get_head(bc->chain);
	active = block_create(active, (int8_t *)"Minecraft", 9);

	display_welcome();

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
			func(&bc, &active, &wallet, arg1, arg2);
		else
			printf("unrecognized command\n");
	}

	return (0);
}
