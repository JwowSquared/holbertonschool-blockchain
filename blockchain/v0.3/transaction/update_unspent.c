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
	llist_t *out;

	out = llist_create(MT_SUPPORT_FALSE);
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
				if (!memcmp(u_token->out.hash, i_token->tx_out_hash, 32))
					break;
			}
			if (k < llist_size(t_token->inputs))
				break;
		}
		if (j == t_size)
			llist_add_node(out, u_token, ADD_NODE_REAR);
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
