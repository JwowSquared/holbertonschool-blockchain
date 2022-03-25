#include "hblk_crypto.h"

/**
* ec_from_pub - creates an EC_KEY object from oct
* @pub: public key stored in oct
*
* Return: pointer to new EC_KEY, else NULL
*/
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *out = NULL;
	EC_POINT *key = NULL;
	const EC_GROUP *group = NULL;

	out = EC_KEY_new_by_curve_name(EC_CURVE);
	group = EC_KEY_get0_group(out);
	key = EC_POINT_new(group);

	EC_POINT_oct2point(group, key, pub, EC_PUB_LEN, NULL);

	EC_KEY_set_public_key(out, key);

	EC_POINT_free(key);

	return (out);
}
