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
	size_t i = 0;
	const EC_POINT *p;
	const EC_GROUP *group;
	BN_CTX *ctx;
	char *out;

	if (key == NULL)
		return (NULL);

	p = EC_KEY_get0_public_key(key);
	group = EC_KEY_get0_group(key);
	ctx = BN_CTX_new();

	out = EC_POINT_point2hex(group, p,
		POINT_CONVERSION_UNCOMPRESSED, ctx);

	while (i < EC_PUB_LEN)
	{
		pub[i] = (unsigned char)out[i];
		i++;
	}

	BN_CTX_free(ctx);
	free(out);

	return (pub);
}
