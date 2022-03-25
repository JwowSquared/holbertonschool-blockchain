#include "hblk_crypto.h"

/**
* ec_sign - signs a key
* @key: key struct
* @msg: msg to sign
* @msglen: length of msg
* @sig: signal struct for use in signing
*
* Return: pointer to sig->sig, else NULL
*/
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
	size_t msglen, sig_t *sig)
{
	if (key == NULL || msg == NULL)
		return (NULL);

	ECDSA_sign(0, msg, msglen, sig->sig,
		(unsigned int *)&sig->len, (EC_KEY *)key);

	return (sig->sig);
}
