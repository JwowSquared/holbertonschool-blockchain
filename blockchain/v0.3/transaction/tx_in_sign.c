#include "transaction.h"

/**
* tx_in_sign - signs a transaction input
* @in: transaction to sign
* @tx_id: hash of transaction which contains @in
* @sender: key pair to use for signing
* @all_unspent: list of unspent transactions in the blockchain
*
* Return: pointer to resulting sig struct, else NULL
*/
sig_t *tx_in_sign(
	tx_in_t *in,
	uint8_t const tx_id[SHA256_DIGEST_LENGTH],
	EC_KEY const *sender,
	llist_t *all_unspent)
{
	int unspent_len, i;
	unspent_tx_out_t *temp;
	uint8_t pubkey[EC_PUB_LEN];

	unspent_len = llist_size(all_unspent);
	for (i = 0; i < unspent_len; i++)
	{
		temp = llist_get_node_at(all_unspent, i);
		if (memcmp(in->tx_out_hash, temp->out.hash, 32) == 0)
			break;
	}

	if (i == unspent_len)
		return (NULL); /* tx out hash not found */

	ec_to_pub(sender, pubkey);

	if (memcmp(pubkey, temp->out.pub, EC_PUB_LEN) != 0)
		return (NULL); /* pubkey doesnt match */

	ec_sign(sender, tx_id, 32, &in->sig);

	return (&in->sig);
}
