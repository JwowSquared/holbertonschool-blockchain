#include "blockchain.h"

/**
* blockchain_destroy - frees all memory associated with a blockchain
* @blockchain: data structure to destroy
*/
void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy(blockchain->chain, 1, (node_dtor_t)block_destroy);
	llist_destroy(blockchain->unspent, 1, NULL);
	free(blockchain);
}
