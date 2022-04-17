#include "cli.h"

/**
* bi_mine - mines the pending block and adds it to the blockchain
* @s: state manager
* @arg1: unused
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_mine(state_manager_t *s, char *arg1, char *arg2)
{
	transaction_t *t_token;

	(void)arg1;
	(void)arg2;

	t_token = coinbase_create(s->user->key, s->block->info.index);
	llist_add_node(s->block->transactions, t_token, ADD_NODE_FRONT);

	s->block->info.difficulty = blockchain_difficulty(s->bc);
	block_mine(s->block);
	llist_add_node(s->bc->chain, s->block, ADD_NODE_REAR);

	s->bc->unspent = update_unspent(s->block->transactions,
		s->block->hash, s->bc->unspent);
	dupe_unspent(s);

	printf("Block mined: [%u] ", s->block->info.difficulty);
	_print_hex_buffer(s->block->hash, SHA256_DIGEST_LENGTH);
	printf("\n");

	s->block = block_create(s->block, (int8_t *)"Minecraft", 9);

	return (1);
}

/**
* bi_send - creates transaction where current wallet pays target
* @s: state manager
* @arg1: amount to send (integer)
* @arg2: target address (valid hex string)
*
* Return: 1 on success, else 0
*/
int bi_send(state_manager_t *s, char *arg1, char *arg2)
{
	uint8_t pub[EC_PUB_LEN];
	int i;
	transaction_t *t_token;
	EC_KEY *target;
	uint32_t amount;

	if (arg1 == NULL || arg2 == NULL)
		return (e_print("Usage: send <amount> <address>\n"));
	amount = atoi(arg1);
	if (amount == 0)
		return (e_print("Amount must be a non-zero integer\n"));
	if (amount > check_balance(s->utxo, s->user->pub))
		return (e_print("Insufficient Funds\n"));
	if (!convert_key(arg2, pub))
		return (e_print("Invalid Key Format\n"));
	target = ec_from_pub(pub);
	if (target == NULL)
		return (e_print("Invalid Address\n"));
	t_token = transaction_create(s->user->key, target, (uint32_t)amount, s->utxo);
	EC_KEY_free(target);
	if (t_token == NULL)
		return (e_print("Error Creating Transaction\n"));

	if (!transaction_is_valid(t_token, s->bc->unspent))
	{
		free(t_token);
		return (e_print("Invalid Transaction\n"));
	}

	for (i = 0; i < llist_size(t_token->inputs); i++)
		llist_remove_node(s->utxo, remove_spent, t_token->inputs, 0, NULL);

	llist_add_node(s->block->transactions, t_token, ADD_NODE_REAR);
	printf("Transaction Added to Pending List\n");

	return (1);
}

/**
* bi_info - prints info about the current state of the CLI
* @s: state manager
* @arg1: debug mode
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_info(state_manager_t *s, char *arg1, char *arg2)
{
	uint8_t pub[EC_PUB_LEN];

	(void)arg2;

	printf("=====================================\n");
	printf("num Blocks: %d\n", llist_size(s->bc->chain));
	printf("num Unspent: %d\n", llist_size(s->utxo));
	printf("num Pending Transactions: %d\n", llist_size(s->block->transactions));
	printf("Your Address: ");
	_print_hex_buffer(s->user->pub, EC_PUB_LEN);
	printf("\nBalance: %u\n", check_balance(s->utxo, pub));
	printf("=====================================\n");
	if (arg1 != NULL)
		_blockchain_print(s->bc);

	return (1);
}

/**
* bi_help - displays command usage
* @s: unused
* @arg1: unused
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_help(state_manager_t *s, char *arg1, char *arg2)
{
	(void)s;
	(void)arg1;
	(void)arg2;

	printf("Commands:\n");
	printf("\thelp (displays this message)\n");
	printf("\twallet_load <path>\n");
	printf("\twallet_save <path>\n");
	printf("\tsend <amount> <address>\n");
	printf("\tmine\n");
	printf("\tinfo\n");
	printf("\tload <path>\n");
	printf("\tsave <path>\n\n");

	return (1);
}
