#include "cli.h"

/**
* bi_mine - mines the pending block and adds it to the blockchain
* @bc: blockchain
* @active: pending block
* @key: current wallet, recieves coinbase transaction for mining
* @arg1: unused
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_mine(blockchain_t **bc, block_t **active,
	EC_KEY **key, char *arg1, char *arg2)
{
	transaction_t *t_token;
	llist_t *temp;

	(void)arg1;
	(void)arg2;

	temp = llist_create(MT_SUPPORT_FALSE);
	t_token = coinbase_create(*key, (*active)->info.index);
	llist_add_node(temp, t_token, ADD_NODE_REAR);
	llist_add_node((*active)->transactions, t_token, ADD_NODE_FRONT);
	(*bc)->unspent = update_unspent(temp,
		(*active)->hash, (*bc)->unspent);
	llist_destroy(temp, 0, NULL);

	(*active)->info.difficulty = blockchain_difficulty(*bc);
	block_mine(*active);
	llist_add_node((*bc)->chain, *active, ADD_NODE_REAR);

	printf("Block mined: [%u] ", (*active)->info.difficulty);
	_print_hex_buffer((*active)->hash, SHA256_DIGEST_LENGTH);
	printf("\n");

	*active = block_create(*active, (int8_t *)"Minecraft", 9);

	return (1);
}

/**
* bi_send - creates transaction where current wallet pays target
* @bc: blockchain
* @active: pending block
* @key: current wallet
* @arg1: amount to send (integer)
* @arg2: target address (valid hex string)
*
* Return: 1 on success, else 0
*/
int bi_send(blockchain_t **bc, block_t **active,
	EC_KEY **key, char *arg1, char *arg2)
{
	uint8_t pub[EC_PUB_LEN];
	llist_t *temp;
	transaction_t *t_token;
	EC_KEY *target;
	uint32_t amount;

	if (arg1 == NULL || arg2 == NULL)
		return (e_print("Usage: send <amount> <address>\n"));
	amount = atoi(arg1);
	if (amount == 0)
		return (e_print("Amount must be a non-zero integer\n"));
	ec_to_pub(*key, pub);
	if (amount > check_balance((*bc)->unspent, pub))
		return (e_print("Insufficient Funds\n"));
	if (!convert_key(arg2, pub))
		return (e_print("Invalid Key Format\n"));
	target = ec_from_pub(pub);
	if (target == NULL)
		return (e_print("Invalid Address\n"));
	t_token = transaction_create(*key, target, (uint32_t)amount, (*bc)->unspent);
	EC_KEY_free(target);
	if (t_token == NULL)
		return (e_print("Error Creating Transaction\n"));

	if (!transaction_is_valid(t_token, (*bc)->unspent))
	{
		free(t_token);
		return (e_print("Invalid Transaction\n"));
	}

	temp = llist_create(MT_SUPPORT_FALSE);
	llist_add_node(temp, t_token, ADD_NODE_REAR);
	llist_add_node((*active)->transactions, t_token, ADD_NODE_REAR);
	(*bc)->unspent = update_unspent(temp,
		(*active)->hash, (*bc)->unspent);
	llist_destroy(temp, 0, NULL);
	printf("Transaction Added to Pending List\n");
	return (1);
}

/**
* bi_info - prints info about the current state of the CLI
* @bc: blockchain
* @active: unused
* @key: current wallet
* @arg1: debug mode
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_info(blockchain_t **bc, block_t **active,
	EC_KEY **key, char *arg1, char *arg2)
{
	uint8_t pub[EC_PUB_LEN];
	uint32_t x;
	int i;
	transaction_t *t_token;

	(void)arg2;

	x = llist_size((*bc)->unspent);
	for (i = 0; i < llist_size((*active)->transactions); i++)
	{
		t_token = llist_get_node_at((*active)->transactions, i);
		x -= llist_size(t_token->outputs);
		x += llist_size(t_token->inputs);
	}

	printf("=====================================\n");
	printf("num Blocks: %d\n", llist_size((*bc)->chain));
	printf("num Unspent: %u\n", x);
	printf("num Pending Transactions: %d\n", llist_size((*active)->transactions));
	printf("Your Address: ");
	_print_hex_buffer(ec_to_pub(*key, pub), EC_PUB_LEN);
	printf("\nBalance: %u\n", check_balance((*bc)->unspent, pub));
	printf("=====================================\n");
	if (arg1 != NULL)
		_blockchain_print(*bc);

	return (1);
}

/**
* bi_help - displays command usage
* @bc: unused
* @active: unused
* @key: unsused
* @arg1: unused
* @arg2: unused
*
* Return: 1 on success, else 0
*/
int bi_help(blockchain_t **bc, block_t **active,
	EC_KEY **key, char *arg1, char *arg2)
{
	(void)bc;
	(void)active;
	(void)key;
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
