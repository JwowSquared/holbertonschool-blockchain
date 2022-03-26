#include "blockchain.h"

/**
* block_create - creates a new block on the chain
* @prev: previous block
* @data: data to duplicate and store in the block
* @data_len: length of data
*
* Return: pointer to new block, else NULL
*/
block_t *block_create(block_t const *prev,
	int8_t const *data, uint32_t data_len)
{
	block_t *out;
	uint32_t copy = BLOCKCHAIN_DATA_MAX;

	out = malloc(sizeof(block_t));
	if (out == NULL)
		return (NULL);

	if (copy > data_len)
		copy = data_len;

	memcpy(out->data.buffer, data, copy);
	out->data.len = copy;

	out->info.index = prev->info.index + 1;
	out->info.difficulty = 0;
	out->info.nonce = 0;
	time((time_t *)&out->info.timestamp);
	memcpy(out->info.prev_hash, prev->hash, sizeof(prev->hash));
	memset(out->hash, 0, sizeof(out->hash));

	return (out);
}
