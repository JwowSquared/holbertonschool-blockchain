#include "blockchain.h"

block_t const GENESIS_BLOCK = {
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

	memcpy(g, &GENESIS_BLOCK, sizeof(block_t));

	llist_add_node(out->chain, g, ADD_NODE_FRONT);

	return (out);
}
