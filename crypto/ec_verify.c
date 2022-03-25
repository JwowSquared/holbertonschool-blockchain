#include "hblk_crypto.h"

/**
* ec_verify - verifies a signature
* @key: key used to verify signature
* @msg: message of signature to verify
* @msglen: length of msg
* @sig: signature
*
* Return: 1 on valid signature, else NULL
*/
int ec_verify(EC_KEY const *key, uint8_t const *msg,
	size_t msglen, sig_t const *sig)
{
	if (key == NULL || msg == NULL || sig == NULL || sig->len == 0)
		return (0);

	return (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key));
}
