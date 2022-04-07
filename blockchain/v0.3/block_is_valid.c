#include "blockchain.h"

block_t const valid_genesis = {
	{ /* info */
		0 /* index */,
		0, /* difficulty */
		1537578000, /* timestamp */
		0, /* nonce */
		{0} /* prev_hash */
	},
	{ /* data */
		"Holberton School", /* buffer */
		16 /* len */
	},
	NULL, /* transactions */
	"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d"
	"\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
	/* hash */
	/* c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803 */
};

/**
* block_is_valid - determines whether a block is valid or not
* @block: block to check
* @prev_block: previous block to check against
* @all_unspent: unspent transactions in the blockchain
*
* Return: 0 on success, else -1 (guessing, task doesnt say)
*/
int block_is_valid(
	block_t const *block,
	block_t const *prev_block,
	llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];

	if (block == NULL)
		return (-1);

	if (block->info.index > 0 && prev_block == NULL)
		return (-1);

	if (block->info.index == 0)
	{
		if (prev_block != NULL)
			return (-1);
		if (memcmp(block, &valid_genesis, sizeof(valid_genesis)) != 0)
			return (-1);
	}

	block_hash(block, hash_buf);
	if (memcmp(block->hash, hash_buf, sizeof(hash_buf)) != 0)
		return (-1);

	if (prev_block != NULL)
	{
		if (block->info.index != prev_block->info.index + 1)
			return (-1);
		block_hash(prev_block, hash_buf);
		if (memcmp(block->info.prev_hash, hash_buf, sizeof(hash_buf)) != 0)
			return (-1);
		if (memcmp(prev_block->hash, hash_buf, sizeof(hash_buf)) != 0)
			return (-1);
	}

	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (-1);

	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (-1);

	if (check_transactions(block, all_unspent) == -1)
		return (-1);
	return (0);
}

/**
* check_transactions - checks all transactions in a block
* @block: block to check
* @all_unspent: used for validity checks
*
* Return: 0 if valid, else -1
*/
int check_transactions(block_t const *block, llist_t *all_unspent)
{
	int i;
	transaction_t *t_token;

	for (i = 0; i < llist_size(block->transactions); i++)
	{
		t_token = llist_get_node_at(block->transactions, i);
		if (i == 0 && coinbase_is_valid(t_token, block->info.index) == 0)
			return (-1);
		if (i > 0 && transaction_is_valid(t_token, all_unspent) == 0)
			return (-1);
	}
	if (i == 0)
		return (-1);
	return (0);
}
