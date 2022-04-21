#include "cli.h"

/**
* bi_mine - mines the pending block and adds it to the blockchain
* @s: state manager
* @arg1: unused
* @arg2: unused
*
* Return: 0 when program should close, else 1
*/
int bi_mine(state_manager_t *s, char *arg1, char *arg2)
{
	transaction_t *t_token;
	block_t *block;

	(void)arg1;
	(void)arg2;

	block = llist_get_tail(s->bc->chain);
	block = block_create(block, (int8_t *)"Minecraft", 9);
	llist_append(block->transactions, s->pending);

	t_token = coinbase_create(s->user->key, block->info.index);
	llist_add_node(block->transactions, t_token, ADD_NODE_FRONT);

	block->info.difficulty = blockchain_difficulty(s->bc);
	block_mine(block);
	llist_add_node(s->bc->chain, block, ADD_NODE_REAR);

	s->bc->unspent = update_unspent(block->transactions,
		block->hash, s->bc->unspent);
	dupe_unspent(s);

	printf("Block mined: [%u] ", block->info.difficulty);
	_print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);
	printf("\n");

	return (1);
}

/**
* bi_send - creates transaction where current wallet pays target
* @s: state manager
* @arg1: amount to send (integer)
* @arg2: target address (valid hex string), or username
*
* Return: 0 when program should close, else 1
*/
int bi_send(state_manager_t *s, char *arg1, char *arg2)
{
	uint8_t pub[EC_PUB_LEN];
	int i, flag = 0;
	transaction_t *t_token;
	EC_KEY *target;
	user_t *user;
	uint32_t amount;

	if (arg1 == NULL || arg2 == NULL)
		return (e_print(1, "Usage: send <amount> <address>\n"));
	amount = atoi(arg1);
	if (amount == 0)
		return (e_print(1, "Amount must be a non-zero integer\n"));
	if (amount > check_balance(s->utxo, s->user->pub))
		return (e_print(1, "Insufficient Funds\n"));
	user = find_user(s->all_users, arg2);
	if (user == NULL)
	{
		flag = 1;
		if (!convert_key(arg2, pub))
			return (e_print(1, "Invalid Key Format\n"));
		target = ec_from_pub(pub);
		if (target == NULL)
			return (e_print(1, "Invalid Address\n"));
	}
	else
		target = user->key;
	t_token = transaction_create(s->user->key, target, (uint32_t)amount, s->utxo);
	if (flag)
		EC_KEY_free(target);

	for (i = 0; i < llist_size(t_token->inputs); i++)
		llist_remove_node(s->utxo, remove_spent, t_token->inputs, 1, NULL);

	llist_add_node(s->pending, t_token, ADD_NODE_REAR);
	printf("Transaction Added to Pending List\n");
	bi_pending(s, NULL, NULL);

	return (1);
}

/**
* bi_logout - logs user out, prompts login
* @s: state manager
* @arg1: unused
* @arg2: unused
*
* Return: 0 when program should close, else 1
*/
int bi_logout(state_manager_t *s, char *arg1, char *arg2)
{
	(void)arg1;
	(void)arg2;

	s->user = NULL;

	prompt_startup(s);
	if (s->user == NULL)
		return (0);

	return (1);
}

/**
* bi_exit - exits
* @s: state manager
* @arg1: unused
* @arg2: unused
*
* Return: 0 when program should close, else 1
*/
int bi_exit(state_manager_t *s, char *arg1, char *arg2)
{
	(void)s;
	(void)arg1;
	(void)arg2;

	return (0);
}
