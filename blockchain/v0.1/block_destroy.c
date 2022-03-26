#include "blockchain.h"

/**
* block_destroy - destroys a block
* @block: block to destroy
*/
void block_destroy(block_t *block)
{
	free(block);
}
