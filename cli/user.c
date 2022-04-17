#include "cli.h"

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

user_t *login(llist_t *users, char *name, char *pass)
{
	uint8_t hash[SHA256_DIGEST_LENGTH];
	int i;
	user_t *user;

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

void destroy_user(llist_node_t node)
{
	user_t *user;

	user = (user_t *)node;
	EC_KEY_free(user->key);
	free(user);
}

llist_t *load_users(void)
{
	llist_t *out;
	FILE *file = NULL;
	user_t *user;
	uint32_t i, u_size;
	char *path;

	out = llist_create(MT_SUPPORT_FALSE);

	file = fopen("users/user.dat", "rb");
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

	path = malloc(20);
	for (i = 0; i < u_size; i++)
	{
		user = llist_get_node_at(out, i);
		memset(path, 0, 20);
		sprintf(path, "%s%s", "users/", user->name);
		user->key = ec_load(path);
		ec_to_pub(user->key, user->pub);
	}

	free(path);
	return (out);
}

int save_users(llist_t *users)
{
	struct stat st = {0};
	FILE *file = NULL;
	user_t *user;
	uint32_t i, u_size;
	char *path;

	if (stat("users", &st) == -1)
		mkdir("users", 0700);

	u_size = llist_size(users);

	path = malloc(20);
	for (i = 0; i < u_size; i++)
	{
		user = llist_get_node_at(users, i);
		memset(path, 0, 20);
		sprintf(path, "%s%s", "users/", (char *)user->name);
		ec_save(user->key, path);
	}

	file = fopen("users/user.dat", "wb");
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
