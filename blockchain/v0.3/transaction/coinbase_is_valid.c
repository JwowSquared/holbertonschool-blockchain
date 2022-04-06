#include "transaction.h"

/**
* coinbase_is_valid - determines if a coinbase transaction is valid
* @coinbase: transaction to validate
* @block_index: supposed block index of transaction
*
* Return: 1 if transaction is valid, else 0
*/
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	tx_in_t *i_token, zero_token;
	tx_out_t *o_token;
	uint8_t t_hash[SHA256_DIGEST_LENGTH];

	transaction_hash(coinbase, t_hash);
	if (memcmp(coinbase->id, t_hash, 32) != 0)
		return (0);

	if (llist_size(coinbase->inputs) != 1)
		return (0);

	if (llist_size(coinbase->outputs) != 1)
		return (0);

	i_token = llist_get_node_at(coinbase->inputs, 0);
	if (memcmp(i_token->tx_out_hash, &block_index, 4) != 0)
		return (0);

	memset(&zero_token, 0, sizeof(zero_token));
	if (memcmp(i_token->block_hash, zero_token.block_hash, 32) != 0)
		return (0);
	if (memcmp(i_token->tx_id, zero_token.tx_id, 32) != 0)
		return (0);
	if (memcmp(&i_token->sig, &zero_token.sig, sizeof(i_token->sig)) != 0)
		return (0);

	o_token = llist_get_node_at(coinbase->outputs, 0);
	if (o_token->amount != COINBASE_AMOUNT)
		return (0);

	return (1);
}
