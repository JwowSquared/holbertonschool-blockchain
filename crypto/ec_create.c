#include "hblk_crypto.h"

/**
* ec_create - creates a public and private key pair
*
* Return: EC_KEY structure containing both keys, else NULL
*/
EC_KEY *ec_create(void)
{
	EC_KEY *out;

	/* Creates EC_KEY ready for key gen */
	out = EC_KEY_new_by_curve_name(EC_CURVE);

	/* Flag needs to be initialized. This works. */
	/* EC_KEY_set_asn1_flag(out, OPENSSL_EC_NAMED_CURVE); */

	/* Generates keys */
	EC_KEY_generate_key(out);

	return (out);
}
