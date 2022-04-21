#include "cli.h"

/**
* create_user - creates a new user
* @name: username
* @pass: password
*
* Return: new user object, else NULL
*/
user_t *create_user(char *name, char *pass)
{
	user_t *out;
	int len;

	out = malloc(sizeof(user_t));

	len = strlen(name);
	if (len >= NAME_MAX_LEN)
		len = NAME_MAX_LEN - 1;

	out->key = ec_create();
	memset(out->name, 0, NAME_MAX_LEN);
	memcpy(out->name, name, len);
	ec_to_pub(out->key, out->pub);
	sha256((int8_t *)pass, strlen(pass), out->pass);

	return (out);
}

/**
* destroy_user - frees memory associated with a user object
* @node: user to free
*/
void destroy_user(llist_node_t node)
{
	user_t *user;

	user = (user_t *)node;
	EC_KEY_free(user->key);
	free(user);
}

/**
* load_users - pre-loads existing users from file
*
* Return: list of all users, can be empty
*/
llist_t *load_users(void)
{
	llist_t *out;
	FILE *file = NULL;
	user_t *user;
	uint32_t i, u_size;
	char *path;

	out = llist_create(MT_SUPPORT_FALSE);

	file = fopen("data/user.dat", "rb");
	if (!file)
		return (out);

	fread(&u_size, 4, 1, file);
	for (i = 0; i < u_size; i++)
	{
		user = malloc(sizeof(user_t));
		memset(user->name, 0, NAME_MAX_LEN);
		fread(user->name, NAME_MAX_LEN, 1, file);
		fread(user->pass, SHA256_DIGEST_LENGTH, 1, file);
		llist_add_node(out, user, ADD_NODE_REAR);
	}

	path = malloc(25);
	for (i = 0; i < u_size; i++)
	{
		user = llist_get_node_at(out, i);
		memset(path, 0, 25);
		sprintf(path, "%s%s", "data/users/", user->name);
		user->key = ec_load(path);
		ec_to_pub(user->key, user->pub);
	}

	free(path);
	return (out);
}

/**
* save_users - saves users to file
* @users: list of all users
*
* Return: 0 on success, else -1
*/
int save_users(llist_t *users)
{
	struct stat st = {0};
	FILE *file = NULL;
	user_t *user;
	uint32_t i, u_size;
	char *path;

	if (stat("data", &st) == -1)
		mkdir("data", 0700);
	if (stat("data/users", &st) == -1)
		mkdir("data/users", 0700);

	u_size = llist_size(users);

	path = malloc(25);
	for (i = 0; i < u_size; i++)
	{
		user = llist_get_node_at(users, i);
		memset(path, 0, 25);
		sprintf(path, "%s%s", "data/users/", (char *)user->name);
		ec_save(user->key, path);
	}

	file = fopen("data/user.dat", "wb");
	if (!file)
		return (-1);

	fwrite(&u_size, 1, 4, file);
	for (i = 0; i < u_size; i++)
	{
		user = llist_get_node_at(users, i);
		fwrite(user->name, 1, NAME_MAX_LEN, file);
		fwrite(user->pass, 1, SHA256_DIGEST_LENGTH, file);
	}

	free(path);
	fclose(file);
	return (0);
}

/**
* find_user - determines if a username exists
* @users: list of all users
* @name: username to check for
*
* Return: user object if match, else NULL
*/
user_t *find_user(llist_t *users, char *name)
{
	int i;
	user_t *user;

	for (i = 0; i < llist_size(users); i++)
	{
		user = llist_get_node_at(users, i);
		if (!strcmp(user->name, name))
			return (user);
	}
	return (NULL);
}
