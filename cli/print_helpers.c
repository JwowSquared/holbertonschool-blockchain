#include "cli.h"

/**
* print_transaction - prints a transaction, for use with bi_print
* @s: state manager
* @t_token: transaction to print
*/
void print_transaction(state_manager_t *s, transaction_t *t_token)
{
	int i;
	block_t *block;
	tx_in_t *i_token;
	tx_out_t *o_token;
	transaction_t *t_from;

	for (i = 0; i < llist_size(t_token->inputs); i++)
	{
		i_token = llist_get_node_at(t_token->inputs, i);
		block = llist_find_node(s->bc->chain, find_origin, i_token);
		if (block == NULL)
		{
			printf("  %s", "COINBASE");
			break;
		}
		t_from = llist_find_node(block->transactions, find_tx, i_token);
		o_token = llist_find_node(t_from->outputs, find_out, i_token);
		if (i == 0)
			printf("  %s ", find_user_name(s->all_users, o_token->pub));
		printf("[-%u]", o_token->amount);
	}
	printf(":\n");
	for (i = 0; i < llist_size(t_token->outputs); i++)
	{
		o_token = llist_get_node_at(t_token->outputs, i);
		printf("    [+%u] -> ", o_token->amount);
		printf("%s\n", find_user_name(s->all_users, o_token->pub));
	}
}

/**
* find_user_name - matches public key with username
* @all_users: list of all users
* @pub: public key to match with
*
* Return: Name, else Unknown
*/
char *find_user_name(llist_t *all_users, uint8_t pub[EC_PUB_LEN])
{
	int i;
	user_t *user;

	for (i = 0; i < llist_size(all_users); i++)
	{
		user = llist_get_node_at(all_users, i);
		if (!memcmp(user->pub, pub, EC_PUB_LEN))
			return (user->name);
	}

	return ("Unknown");
}

/**
* find_origin - matches true when i_token->block_hash matches
* @node: block in blockchain list
* @data: i_token to match with
*
* Return: 1 if hashes match, else 0
*/
int find_origin(llist_node_t node, void *data)
{
	block_t *block = (block_t *)node;
	tx_in_t *i_token = (tx_in_t *)data;

	return (!memcmp(block->hash, i_token->block_hash, 32));
}

/**
* find_tx - matches true when i_token->block_hash matches
* @node: transaction token in block->transactions list
* @data: i_token to match with
*
* Return: 1 if hashes match, else 0
*/
int find_tx(llist_node_t node, void *data)
{
	transaction_t *t_token = (transaction_t *)node;
	tx_in_t *i_token = (tx_in_t *)data;

	return (!memcmp(t_token->id, i_token->tx_id, 32));
}

/**
* find_out - matches true when i_token->tx_out_hash matches
* @node: tx_out_t token in transaction->outputs list
* @data: i_token to match with
*
* Return: 1 if hashes match, else 0
*/
int find_out(llist_node_t node, void *data)
{
	tx_out_t *o_token = (tx_out_t *)node;
	tx_in_t *i_token = (tx_in_t *)data;

	return (!memcmp(o_token->hash, i_token->tx_out_hash, 32));
}
