#include "blockchain.h"

/**
* block_hash - hashes a block
* @block: block to hash
* @hash_buf: buffer to store the hash into
*
* Return: hash_buf
*/
uint8_t *block_hash(block_t const *block,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	int tx_len = 0, target_len, i, offset;
	transaction_t *t_token;
	int8_t *hash_target;

	offset = sizeof(block->info) + block->data.len;
	if (block->transactions)
		tx_len = llist_size(block->transactions);
	target_len = offset + 32 * tx_len;
	hash_target = malloc(target_len);
	memcpy(hash_target, block, offset);
	for (i = 0; i < tx_len; i++)
	{
		t_token = llist_get_node_at(block->transactions, i);
		memcpy(hash_target + offset, t_token->id, 32);
		offset += 32;
	}

	sha256(hash_target, target_len, hash_buf);
	free(hash_target);
	return (hash_buf);
}
