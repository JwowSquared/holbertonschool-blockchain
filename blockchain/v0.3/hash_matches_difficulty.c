#include "blockchain.h"

/**
* hash_matches_difficulty - see function title
* @hash: hash to check
* @difficulty: difficulty to check
*
* Return: 1 if match, else 0
*/
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
uint32_t difficulty)
{
	uint32_t i, mask, count = 0;

	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		for (mask = 128; mask > 0; mask = mask >> 1)
		{
			if (mask & hash[i])
				break;
			count++;
		}
		if (mask & hash[i])
			break;
	}

	if (count >= difficulty)
		return (1);

	return (0);
}
