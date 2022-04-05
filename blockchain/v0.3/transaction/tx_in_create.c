#include "transaction.h"

/**
* tx_in_create - creates an in transaction
* @unspent: unspent out transaction to use for in transaction
*
* Return: pointer to new tx_in struct, else NULL
*/
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *out;

	out = malloc(sizeof(tx_in_t));
	if (out == NULL)
		return (NULL);

	memcpy(out->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
	memcpy(out->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
	memcpy(out->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH);
	memset(&out->sig, 0, sizeof(out->sig));

	return (out);
}
