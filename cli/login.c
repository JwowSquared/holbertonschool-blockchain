#include "cli.h"

/**
* prompt_startup - has user create new account or login
* @s: state manager
*/
void prompt_startup(state_manager_t *s)
{
	size_t len;
	char *line = NULL, *cmd;

	printf("[Welcome to blockchain! Please <login> or create <newuser>.]\n");
	while (s->user == NULL)
	{
		printf("bc$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
		cmd = strtok(line, "\n");
		if (cmd == NULL)
			continue;
		if (!strcmp(cmd, "login"))
			prompt_login(s);
		else if (!strcmp(cmd, "newuser"))
			prompt_newuser(s);
		else
			printf("Unknown command. Try 'login' or 'newuser'.");
		printf("\n");
	}
	safe_free(line);
	if (s->user != NULL)
		display_welcome(s->user->name);
}

/**
* prompt_login - opportunity for user to login
* @s: state manager
*/
void prompt_login(state_manager_t *s)
{
	char *line = NULL, *line2 = NULL, *name, *pass;
	size_t len;

	while (1)
	{
		printf("Enter Username: ");
		if (getline(&line, &len, stdin) == -1)
			break;
		name = strtok(line, "\n");
		if (name == NULL)
			continue;
		if (!find_user(s->all_users, name))
		{
			printf("Username Unrecognized.\n");
			continue;
		}
		printf("Enter Password: ");
		if (getline(&line2, &len, stdin) == -1)
			break;
		pass = strtok(line2, "\n");
		s->user = login(s->all_users, name, pass);
		if (s->user != NULL)
			break;
		printf("Password Incorrect.\n");
	}
	safe_free(line);
	safe_free(line2);
}

/**
* prompt_newuser - opportunity for user to create a new user
* @s: state manager
*/
void prompt_newuser(state_manager_t *s)
{
	char *line = NULL, *line2 = NULL, *name, *pass;
	size_t len;

	while (s->user == NULL)
	{
		printf("Enter Username: ");
		if (getline(&line, &len, stdin) == -1)
			break;
		for (name = strtok(line, "\n"); name && *name == ' ';)
			name++;
		if (name == NULL || *name == '\0')
		{
			printf("Username cannot be empty.\n");
			continue;
		}
		if (strlen(name) >= NAME_MAX_LEN)
		{
			printf("Username must be 12 characters or less.\n");
			continue;
		}
		if (find_user(s->all_users, name))
		{
			printf("Account already associated with that username.\n");
			continue;
		}
		printf("Enter Password: ");
		if (getline(&line2, &len, stdin) == -1)
			break;
		for (pass = strtok(line2, "\n"); pass && *pass == ' ';)
			pass++;
		if (pass == NULL || *pass == '\0')
		{
			printf("Password cannot be empty.\n");
			continue;
		}
		s->user = create_user(name, pass);
		llist_add_node(s->all_users, s->user, ADD_NODE_REAR);
	}
	safe_free(line);
	safe_free(line2);
}

/**
* login - hashes password and returns matching user object
* @users: list of all users
* @name: username
* @pass: password
*
* Return: matched user object, else NULL
*/
user_t *login(llist_t *users, char *name, char *pass)
{
	uint8_t hash[SHA256_DIGEST_LENGTH];
	int i;
	user_t *user;

	if (name == NULL || pass == NULL)
		return (NULL);

	sha256((int8_t *)pass, strlen(pass), hash);

	for (i = 0; i < llist_size(users); i++)
	{
		user = llist_get_node_at(users, i);
		if (strcmp(user->name, name))
			continue;
		if (!memcmp(hash, user->pass, SHA256_DIGEST_LENGTH))
			return (user);
	}

	return (NULL);
}

/**
* safe_free - makes sure free doesnt get passed NULL
* @s: string to free
*/
void safe_free(char *s)
{
	if (s)
		free(s);
}
