#include "blockchain.h"

/**
* block_hash - hashes a block
* @block: block to hash
* @hash_buf: buffer to store the hash into
*
* Return: hash_buf
*/
uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	return (sha256((int8_t const *)block, sizeof(block), hash_buf));
}
