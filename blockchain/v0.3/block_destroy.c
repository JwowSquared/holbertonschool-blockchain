#include "blockchain.h"

/**
* block_destroy - destroys a block
* @block: block to destroy
*/
void block_destroy(block_t *block)
{
	if (block->transactions)
		llist_destroy(block->transactions, 1, transaction_destroy);
	free(block);
}
