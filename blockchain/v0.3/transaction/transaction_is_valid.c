#include "transaction.h"

/**
* transaction_is_valid - determines if a transaction is valid
* @transaction: transaction to check
* @all_unspent: list of all unspent transactions in the blockchain
*
* Return: 1 if transaction is valid, else 0
*/
int transaction_is_valid(
	transaction_t const *transaction,
	llist_t *all_unspent)
{
	tx_in_t *i_token;
	tx_out_t *o_token;
	unspent_tx_out_t *u_token;
	int i, u, u_size;
	uint32_t amount_in = 0, amount_out = 0;
	EC_KEY *u_key;
	uint8_t t_hash[SHA256_DIGEST_LENGTH];

	transaction_hash(transaction, t_hash);
	if (memcmp(transaction->id, t_hash, 32) != 0)
		return (0);

	u_size = llist_size(all_unspent);
	for (i = 0; i < llist_size(transaction->inputs); i++)
	{
		i_token = llist_get_node_at(transaction->inputs, i);
		for (u = 0; u < u_size; u++)
		{
			u_token = llist_get_node_at(all_unspent, u);
			if (memcmp(i_token->tx_out_hash, u_token->out.hash, 32) == 0)
				break;
		}
		if (u == u_size)
			return (0);
		u_key = ec_from_pub(u_token->out.pub);
		u = ec_verify(u_key, transaction->id, SHA256_DIGEST_LENGTH, &i_token->sig);
		EC_KEY_free(u_key);
		if (u == 0)
			return (0);
		amount_in += u_token->out.amount;
	}

	for (i = 0; i < llist_size(transaction->outputs); i++)
	{
		o_token = llist_get_node_at(transaction->outputs, i);
		amount_out += o_token->amount;
	}
	if (amount_in != amount_out)
		return (0);
	return (1);
}
