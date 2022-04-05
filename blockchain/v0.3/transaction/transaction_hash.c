#include "transaction.h"

/**
* transaction_hash - computes the ID of a transaction
* @transaction: transaction to compute from
* @hash_buf: buffer to store computed hash
*
* Return: hash_buf, or NULL
*/
uint8_t *transaction_hash(
	transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	int8_t *hash_target;
	int in_len, out_len, target_len, offset, i;

	in_len = llist_size(transaction->inputs);
	out_len = llist_size(transaction->outputs);
	target_len = in_len * 96 + out_len * 32;

	hash_target = malloc(target_len);
	if (hash_target == NULL)
		return (NULL);

	offset = 0;
	for (i = 0; i < in_len; i++)
	{
		memcpy(hash_target + offset, llist_get_node_at(transaction->inputs, i), 96);
		offset += 96;
	}

	for (i = 0; i < out_len; i++)
	{
		memcpy(hash_target + offset, llist_get_node_at(transaction->outputs, i), 32);
		offset += 32;
	}

	sha256(hash_target, target_len, hash_buf);
	free(hash_target);

	return (hash_buf);
}
