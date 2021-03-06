#include "cli.h"

/**
* main - entry point for CLI
*
* Return: always 0
*/
int main(void)
{
	state_manager_t *s;
	char *line = NULL, *cmd, *arg1, *arg2;
	size_t len;
	int (*func)(state_manager_t *, char *, char *);

	s = create_state_manager();
	prompt_startup(s);
	if (s->user == NULL)
		return (destroy_state_manager(s));

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
		{
			if (!func(s, arg1, arg2))
				break;
		}
		else
			printf("unrecognized command\n");
	}

	save_users(s->all_users);
	blockchain_serialize(s->bc, "data/chain.dat");
	destroy_state_manager(s);
	if (line)
		free(line);

	return (0);
}
