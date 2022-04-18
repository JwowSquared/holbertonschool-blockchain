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

	out->bc = blockchain_create();
	out->pending = llist_create(MT_SUPPORT_FALSE);
	out->utxo = llist_create(MT_SUPPORT_FALSE);
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
	unspent_tx_out_t *u_token;

	llist_destroy(s->utxo, 0, NULL);
	s->utxo = llist_create(MT_SUPPORT_FALSE);
	for (i = 0; i < llist_size(s->bc->unspent); i++)
	{
		u_token = llist_get_node_at(s->bc->unspent, i);
		llist_add_node(s->utxo, u_token, ADD_NODE_REAR);
	}
}

/**
* destroy_state_manager - frees data associated with a state manager
* @s: state manager
*/
void destroy_state_manager(state_manager_t *s)
{
	if (s == NULL)
		return;

	blockchain_destroy(s->bc);
	llist_destroy(s->pending, 1, (node_dtor_t)transaction_destroy);
	llist_destroy(s->utxo, 0, NULL);
	llist_destroy(s->all_users, 1, destroy_user);
	free(s);
}
