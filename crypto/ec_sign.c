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
	unsigned int ui;

	if (key == NULL || msg == NULL)
		return (NULL);

	ui = 70;

	sig->len = 70;

	ECDSA_sign(0, msg, msglen, sig->sig, &ui, (EC_KEY *)key);

	return (sig->sig);
}
