#include "transaction.h"

/**
* unspent_tx_out_create - creates an unspent out transaction
* @block_hash: hash of block with transaction in it
* @tx_id: hash of transaction within block
* @t_out: referenced out transaction
*
* Return: pointer to new unspent_tx_out struct, else NULL
*/
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH],
	tx_out_t const *t_out)
{
	unspent_tx_out_t *out;

	out = malloc(sizeof(unspent_tx_out_t));
	if (out == NULL)
		return (NULL);

	memcpy(out->block_hash, block_hash, SHA256_DIGEST_LENGTH);
	memcpy(out->tx_id, tx_id, SHA256_DIGEST_LENGTH);
	memcpy(&out->out, t_out, sizeof(*t_out));

	return (out);
}
