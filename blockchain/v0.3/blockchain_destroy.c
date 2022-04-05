#include "blockchain.h"

/**
* blockchain_destroy - frees all memory associated with a blockchain
* @blockchain: data structure to destroy
*/
void blockchain_destroy(blockchain_t *blockchain)
{
	/* blockchain_t is just a llist from the given library */
	llist_destroy(blockchain->chain, 1, NULL);
	free(blockchain);
}
