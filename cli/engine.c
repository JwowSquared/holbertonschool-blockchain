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

	while (1)
	{
		printf("ENTER USERNAME + PASSWORD\nbc$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
		line = strtok(line, "\n");
		arg1 = strtok(line, " ");
		arg2 = strtok(NULL, " ");
		s->user = login(s->all_users, arg1, arg2);
		if (s->user != NULL)
			break;
		printf("INVALID LOGIN, CREATE NEW USERNAME + PASSWORD:\nbc$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
		line = strtok(line, "\n");
		arg1 = strtok(line, " ");
		arg2 = strtok(NULL, " ");
		s->user = create_user(arg1, arg2);
		llist_add_node(s->all_users, s->user, ADD_NODE_REAR);
		break;
	}

	if (s->user == NULL)
	{
		destroy_state_manager(s);
		if (line)
			free(line);
		return (0);
	}

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
			func(s, arg1, arg2);
		else
			printf("unrecognized command\n");
	}

	save_users(s->all_users);
	destroy_state_manager(s);
	if (line)
		free(line);

	return (0);
}
