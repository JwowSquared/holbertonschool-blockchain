#include "transaction.h"

/**
* transaction_create - creates a transaction
* @sender: person sending coin
* @receiver: person recieving coin
* @amount: amount of coin
* @all_unspent: all unspent transactions in the blockchain
*
* Return: pointer to new transaction, else NULL
*/
transaction_t *transaction_create(
	EC_KEY const *sender,
	EC_KEY const *receiver,
	uint32_t amount,
	llist_t *all_unspent)
{
	transaction_t *out = NULL;
	uint8_t key_in[EC_PUB_LEN], key_out[EC_PUB_LEN];
	tx_out_t *o_token;
	tx_in_t *i_token;
	int i;
	uint32_t balance = 0;

	ec_to_pub(sender, key_in);
	ec_to_pub(receiver, key_out);
	out = t_create();
	if (out == NULL)
		return (NULL);

	balance = select_inputs(out->inputs, all_unspent, amount, key_in);
	if (balance < amount)
		return (t_cleanup(out));

	o_token = tx_out_create(amount, key_out);
	llist_add_node(out->outputs, o_token, ADD_NODE_REAR);
	if (balance > amount)
	{
		o_token = tx_out_create(balance - amount, key_in);
		llist_add_node(out->outputs, o_token, ADD_NODE_REAR);
	}
	transaction_hash(out, out->id);

	for (i = 0; i < llist_size(out->inputs); i++)
	{
		i_token = llist_get_node_at(out->inputs, i);
		if (tx_in_sign(i_token, out->id, sender, all_unspent) == 0)
			return (t_cleanup(out));
	}
	return (out);
}

/**
* t_create - creates a blank transaction_t
*
* Return: pointer to new struct, else NULL
*/
transaction_t *t_create(void)
{
	transaction_t *out;

	out = malloc(sizeof(transaction_t));
	if (out == NULL)
		return (NULL);

	out->inputs = NULL;
	out->outputs = NULL;

	out->inputs = llist_create(MT_SUPPORT_FALSE);
	if (out->inputs == NULL)
		return (t_cleanup(out));
	out->outputs = llist_create(MT_SUPPORT_FALSE);
	if (out->outputs == NULL)
		return (t_cleanup(out));

	return (out);
}

/**
* t_cleanup - destroys a transaction_t
* @out: destroy me
*
* Return: always NULL
*/
transaction_t *t_cleanup(transaction_t *out)
{
	if (out->inputs)
		llist_destroy(out->inputs, 0, NULL);
	if (out->outputs)
		llist_destroy(out->outputs, 0, NULL);

	free(out);

	return (NULL);
}

/**
* select_inputs - selects inputs for a transaction
* @inputs: list to add to
* @all_unspent: list to select from
* @amount: amount to reach
* @key_in: public key of sender
*
* Return: balance to be used in transaction
*/
uint32_t select_inputs(
	llist_t *inputs,
	llist_t *all_unspent,
	uint32_t amount,
	uint8_t key_in[EC_PUB_LEN])
{
	unspent_tx_out_t *u_token;
	tx_in_t *i_token;
	int i;
	uint32_t balance = 0;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		u_token = llist_get_node_at(all_unspent, i);
		if (memcmp(u_token->out.pub, key_in, EC_PUB_LEN) == 0)
		{
			i_token = tx_in_create(u_token);
			llist_add_node(inputs, i_token, ADD_NODE_REAR);
			balance += u_token->out.amount;
			if (balance >= amount)
				break;
		}
	}

	return (balance);
}
