#include "blockchain.h"

/**
* blockchain_difficulty - adjusts difficulty based on time to mine
* @blockchain: chain to adjust
*
* Return: On adjust, return new difficulty, else old difficulty
*/
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *prev, *current;
	int prev_idx;
	uint64_t time, adjustment_time;


	current = llist_get_tail(blockchain->chain);
	if (current->info.index < DIFFICULTY_ADJUSTMENT_INTERVAL)
		return (current->info.difficulty);

	if (current->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL > 0)
		return (current->info.difficulty);

	prev_idx = current->info.index - DIFFICULTY_ADJUSTMENT_INTERVAL + 1;
	prev = llist_get_node_at(blockchain->chain, prev_idx);
	time = current->info.timestamp - prev->info.timestamp;

	adjustment_time = BLOCK_GENERATION_INTERVAL * DIFFICULTY_ADJUSTMENT_INTERVAL;
	if (time <= adjustment_time / 2)
		return (current->info.difficulty + 1);

	if (time > adjustment_time * 2 && current->info.difficulty > 0)
		return (current->info.difficulty - 1);

	return (current->info.difficulty);
}
