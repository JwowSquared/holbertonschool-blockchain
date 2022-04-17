#include "transaction.h"

/**
* update_unspent - returns a new list of all unspent transactions
* @transactions: all validated transactions in the block
* @block_hash: hash of block which contains transactions
* @all_unspent: current list
*
* Return: new list, else NULL (..?)
*/
llist_t *update_unspent(
	llist_t *transactions,
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	llist_t *all_unspent)
{
	int i, j, k, t_size;
	tx_in_t *i_token;
	tx_out_t *o_token;
	unspent_tx_out_t *u_token;
	transaction_t *t_token;
	llist_t *out = llist_create(MT_SUPPORT_FALSE);

	t_size = llist_size(transactions);
	for (i = 0; i < llist_size(all_unspent); i++)
	{
		u_token = llist_get_node_at(all_unspent, i);
		for (j = 0; j < t_size; j++)
		{
			t_token = llist_get_node_at(transactions, j);
			for (k = 0; k < llist_size(t_token->inputs); k++)
			{
				i_token = llist_get_node_at(t_token->inputs, k);
				if (unspent_match(u_token, i_token))
					break;
			}
			if (k < llist_size(t_token->inputs))
				break;
		}
		if (j == t_size)
			llist_add_node(out, u_token, ADD_NODE_REAR);
		else
			free(u_token);
	}
	for (i = 0; i < llist_size(transactions); i++)
	{
		t_token = llist_get_node_at(transactions, i);
		for (j = 0; j < llist_size(t_token->outputs); j++)
		{
			o_token = llist_get_node_at(t_token->outputs, j);
			u_token = unspent_tx_out_create(block_hash, t_token->id, o_token);
			llist_add_node(out, u_token, ADD_NODE_REAR);
		}
	}
	llist_destroy(all_unspent, 0, NULL);
	return (out);
}

/**
* unspent_match - determines if an unspent token matches an input token
* @u_token: unspent out transaction
* @i_token: transaction input
*
* Return: 1 on match, else 0
*/
int unspent_match(unspent_tx_out_t *u_token, tx_in_t *i_token)
{
	if (memcmp(u_token->out.hash, i_token->tx_out_hash, 32))
		return (0);
	if (memcmp(u_token->tx_id, i_token->tx_id, 32))
		return (0);
	return (1);
}

/**
* remove_spent - removes spent transactions from unspent list
* @node: unspent token to potentially be removed
* @data: linked list of transaction inputs
*
* Return: 1 if any input matches node, else 0
*/
int remove_spent(llist_node_t node, void *data)
{
	llist_t *inputs;
	unspent_tx_out_t *u_token;
	tx_in_t *i_token;
	int i;

	u_token = (unspent_tx_out_t *)node;
	inputs = (llist_t *)data;

	for (i = 0; i < llist_size(inputs); i++)
	{
		i_token = llist_get_node_at(inputs, i);
		if (unspent_match(u_token, i_token))
			return (1);
	}

	return (0);
}
