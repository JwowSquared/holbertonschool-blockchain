#include "cli.h"

int find_origin(llist_node_t node, void *data)
{
	block_t *block = (block_t *)node;
	tx_in_t *i_token = (tx_in_t *)data;

	return (!memcmp(block->hash, i_token->block_hash, 32));
}

int find_tx(llist_node_t node, void *data)
{
	transaction_t *t_token = (transaction_t *)node;
	tx_in_t *i_token = (tx_in_t *)data;

	return (!memcmp(t_token->id, i_token->tx_id, 32));
}

int find_out(llist_node_t node, void *data)
{
	tx_out_t *o_token = (tx_out_t *)node;
	tx_in_t *i_token = (tx_in_t *)data;

	return (!memcmp(o_token->hash, i_token->tx_out_hash, 32));
}

char *find_user_name(llist_t *all_users, uint8_t pub[EC_PUB_LEN])
{
	int i;
	user_t *user;

	for (i = 0; i < EC_PUB_LEN; i++)
	{
		if (pub[i] > 0)
			break;
	}
	if (i == EC_PUB_LEN)
		return ("COINBASE");

	for (i = 0; i < llist_size(all_users); i++)
	{
		user = llist_get_node_at(all_users, i);
		if (!memcmp(user->pub, pub, EC_PUB_LEN))
			return (user->name);
	}

	return ("Unknown");
}

/**
*
*
*/
int bi_bcprint(state_manager_t *s, char *arg1, char *arg2)
{
	int i, j, k;
	block_t *block, *b_home;
	transaction_t *t_token, *t_home;
	tx_in_t *i_token;
	tx_out_t *o_token;

	(void)arg1;
	(void)arg2;

	printf("[Blockchain]\n");
	printf("[Block 0]\n  [GENESIS BLOCK]\n");
	for (i = 1; i < llist_size(s->bc->chain); i++)
	{
		block = llist_get_node_at(s->bc->chain, i);
		printf("[Block %d]\n", block->info.index);
		for (j = 0; j < llist_size(block->transactions); j++)
		{
			t_token = llist_get_node_at(block->transactions, j);
			for (k = 0; k < llist_size(t_token->inputs); k++)
			{
				i_token = llist_get_node_at(t_token->inputs, k);
				b_home = llist_find_node(s->bc->chain, find_origin, i_token);
				if (b_home == NULL)
				{
					printf("  %s [%u]", "COINBASE", COINBASE_AMOUNT);
					continue;
				}
				t_home = llist_find_node(b_home->transactions, find_tx, i_token);
				o_token = llist_find_node(t_home->outputs, find_out, i_token);
				if (k == 0)
					printf("  %s ", find_user_name(s->all_users, o_token->pub));
				printf("[%u]", o_token->amount);
			}
			printf(":\n");
			for (k = 0; k < llist_size(t_token->outputs); k++)
			{
				o_token = llist_get_node_at(t_token->outputs, k);
				printf("    -[%u]-> ", o_token->amount);
				printf("%s\n", find_user_name(s->all_users, o_token->pub));
			}
		}
	}
	return (1);
}
