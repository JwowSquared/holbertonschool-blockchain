#include "cli.h"

/**
* bi_load - loads a blockchain from file, replacing the current one
* @s: state manager
* @arg1: path to load blockchain from
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_load(state_manager_t *s, char *arg1, char *arg2)
{
	blockchain_t *out;

	(void)arg2;

	if (arg1 == NULL)
	{
		printf("Usage: load <path>\n");
		return (0);
	}

	out = blockchain_deserialize(arg1);
	if (out == NULL)
	{
		printf("Error loading blockchain from %s\n", arg1);
		return (0);
	}

	blockchain_destroy(s->bc);
	s->bc = out;
	dupe_unspent(s);

	printf("Successfully loaded blockchain\n");

	return (1);
}

/**
* bi_save - saves current blockchain to file
* @s: state manager
* @arg1: path to save blockchain to
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_save(state_manager_t *s, char *arg1, char *arg2)
{
	(void)arg2;

	if (arg1 == NULL)
	{
		printf("Usage: save <path>\n");
		return (0);
	}

	if (blockchain_serialize(s->bc, arg1) == -1)
	{
		printf("Error saving blockchain to %s\n", arg1);
		return (0);
	}

	printf("Successfully saved blockchain\n");

	return (1);
}

/**
* bi_wallet_load - loads a wallet from file, replacing the current wallet
* @s: state manager
* @arg1: path to load from
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_wallet_load(state_manager_t *s, char *arg1, char *arg2)
{
	EC_KEY *out;

	(void)arg2;

	if (arg1 == NULL)
	{
		printf("Usage: wallet_load <path>\n");
		return (0);
	}

	out = ec_load(arg1);
	if (out == NULL)
	{
		printf("Error loading wallet from %s\n", arg1);
		return (0);
	}

	EC_KEY_free(s->user->key);
	s->user->key = out;
	printf("Successfully loaded wallet\n");

	return (1);
}

/**
* bi_wallet_save - saves the current wallet to file
* @s: state manager
* @arg1: path to save to
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_wallet_save(state_manager_t *s, char *arg1, char *arg2)
{
	(void)arg2;

	if (arg1 == NULL)
	{
		printf("Usage: wallet_save <path>\n");
		return (0);
	}

	if (ec_save(s->user->key, arg1) == -1)
	{
		printf("Error saving key to %s\n", arg1);
		return (0);
	}

	printf("Successfully saved wallet\n");

	return (1);
}
