#include "hblk_crypto.h"

/**
* ec_from_pub - creates an EC_KEY object from oct
* @pub: public key stored in oct
*
* Return: pointer to new EC_KEY, else NULL
*/
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	(void)pub;

	return (NULL);
}
