#include "blockchain.h"
#ifndef _genesis
#include "provided/_genesis.c"
#endif

/**
* blockchain_create - creates a blockchain using the given genesis block
*
* Return: pointer to new blockchain, else NULL
*/
blockchain_t *blockchain_create(void)
{
	blockchain_t *out;
	block_t *g;

	out = malloc(sizeof(blockchain_t));
	if (out == NULL)
		return (NULL);

	g = malloc(sizeof(block_t));
	if (g == NULL)
		return (NULL);

	out->chain = llist_create(MT_SUPPORT_FALSE);
	if (out->chain == NULL)
		return (NULL);

	memcpy(g, &_genesis, sizeof(block_t));

	llist_add_node(out->chain, g, ADD_NODE_FRONT);

	return (out);
}
