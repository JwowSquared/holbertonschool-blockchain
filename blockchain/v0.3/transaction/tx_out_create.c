#include "transaction.h"

/**
* tx_out_create - creates an out transaction
* @amount: amount of the transaction
* @pub: public key of transaction reciever
*
* Return: pointer to new tx_out struct, else NULL
*/
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *out;

	out = malloc(sizeof(tx_out_t));
	if (out == NULL)
		return (NULL);

	out->amount = amount;
	memcpy(out->pub, pub, EC_PUB_LEN);
	sha256((const int8_t *)out, EC_PUB_LEN + 4, out->hash);

	return (out);
}
