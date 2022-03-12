#include "hblk_crypto.h"

/**
* ec_to_pub - extracts public key from EC_KEY
* @key: EC_KEY to extract from
* @pub: buffer to store key in
*
* Return: buffer address, else NULL
*/
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *p;
	const EC_GROUP *group;

	if (key == NULL)
		return (NULL);

	p = EC_KEY_get0_public_key(key);
	group = EC_KEY_get0_group(key);

	EC_POINT_point2oct(group, p,
		POINT_CONVERSION_UNCOMPRESSED,
		pub, EC_PUB_LEN, NULL);

	return (pub);
}
