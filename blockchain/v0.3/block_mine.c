#include "blockchain.h"

/**
* block_mine - mines a block so hash matches difficulty
* @block: block to mine
*/
void block_mine(block_t *block)
{
	if (block == NULL)
		return;

	if (block->info.difficulty == 0)
		return;

	block_hash(block, block->hash);

	/* This may take a while... */
	while (!hash_matches_difficulty(block->hash, block->info.difficulty))
	{
		block->info.nonce++;
		block_hash(block, block->hash);
	}
}
