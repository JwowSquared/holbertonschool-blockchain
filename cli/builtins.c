#include "cli.h"

int bi_wallet_load(blockchain_t *bc, EC_KEY *key, char *arg1, char *arg2)
{
	(void)bc;
	(void)key;
	printf("REACHED WALLET LOAD %s %s\n", arg1, arg2);
	return (1);
}

int bi_wallet_save(blockchain_t *bc, EC_KEY *key, char *arg1, char *arg2)
{
	(void)bc;
	(void)key;
	printf("REACHED WALLET SAVE %s %s\n", arg1, arg2);
	return (1);
}

int bi_send(blockchain_t *bc, EC_KEY *key, char *arg1, char *arg2)
{
	(void)bc;
	(void)key;
	printf("REACHED SEND %s %s\n", arg1, arg2);
	return (1);
}

int bi_mine(blockchain_t *bc, EC_KEY *key, char *arg1, char *arg2)
{
	(void)bc;
	(void)key;
	printf("REACHED MINE %s %s\n", arg1, arg2);
	return (1);
}

int bi_info(blockchain_t *bc, EC_KEY *key, char *arg1, char *arg2)
{
	(void)bc;
	(void)key;
	printf("REACHED INFO %s %s\n", arg1, arg2);
	return (1);
}

int bi_load(blockchain_t *bc, EC_KEY *key, char *arg1, char *arg2)
{
	(void)bc;
	(void)key;
	printf("REACHED LOAD %s %s\n", arg1, arg2);
	return (1);
}

int bi_save(blockchain_t *bc, EC_KEY *key, char *arg1, char *arg2)
{
	(void)bc;
	(void)key;
	printf("REACHED SAVE %s %s\n", arg1, arg2);
	return (1);
}
