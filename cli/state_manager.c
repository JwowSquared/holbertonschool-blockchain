#include "cli.h"

/**
* create_state_manager - initializes the state of the program
*
* Return: pointer to state manager object, else NULL
*/
state_manager_t *create_state_manager(void)
{
	state_manager_t *out;

	out = malloc(sizeof(state_manager_t));
	if (out == NULL)
		return (NULL);

	out->bc = blockchain_deserialize("data/chain.dat");
	if (out->bc == NULL)
		out->bc = blockchain_create();
	out->pending = llist_create(MT_SUPPORT_FALSE);
	out->utxo = NULL;
	dupe_unspent(out);
	out->user = NULL;
	out->all_users = load_users();

	return (out);
}

/**
* dupe_unspent - makes a local copy of unspent
* @s: state manager
*/
void dupe_unspent(state_manager_t *s)
{
	int i;
	unspent_tx_out_t *u_token, *temp;

	if (s->utxo != NULL)
		llist_destroy(s->utxo, 1, NULL);
	s->utxo = llist_create(MT_SUPPORT_FALSE);
	for (i = 0; i < llist_size(s->bc->unspent); i++)
	{
		u_token = llist_get_node_at(s->bc->unspent, i);
		temp = malloc(sizeof(unspent_tx_out_t));
		memcpy(temp, u_token, 165);
		llist_add_node(s->utxo, temp, ADD_NODE_REAR);
	}
}

/**
* destroy_state_manager - frees data associated with a state manager
* @s: state manager
*
* Return: always 0
*/
int destroy_state_manager(state_manager_t *s)
{
	if (s == NULL)
		return (0);

	blockchain_destroy(s->bc);
	llist_destroy(s->pending, 1, (node_dtor_t)transaction_destroy);
	llist_destroy(s->utxo, 1, NULL);
	llist_destroy(s->all_users, 1, destroy_user);
	free(s);

	return (0);
}
