#include "hblk_crypto.h"

/**
* sha256 - hashes s and stores in digest
* @s: sequence of bytes to hash
* @len: length of s
* @digest: memory location to store hash
*
* Return: address of hash
*/
uint8_t *sha256(int8_t const *s, size_t len,
	uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (digest == NULL)
		return (NULL);

	return (SHA256((unsigned char *)s, len, digest));
}
