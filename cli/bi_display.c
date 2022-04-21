#include "cli.h"

/**
* bi_print - prints the blockchain
* @s: state manager
* @arg1: left bound index (integer)
* @arg2: right bound index (integer)
*
* Return: 1 on success, else 0
*/
int bi_print(state_manager_t *s, char *arg1, char *arg2)
{
	int i, j, left, right;
	block_t *block;
	transaction_t *t_token;

	if (arg1 != NULL)
		left = atoi(arg1);
	else
		left = 0;

	if (arg2 != NULL)
		right = atoi(arg2);
	else
		right = left;

	if (!arg1 || right >= llist_size(s->bc->chain))
		right = llist_size(s->bc->chain) - 1;

	printf("\n[Blockchain]");
	for (i = left; i <= right; i++)
	{
		block = llist_get_node_at(s->bc->chain, i);
		printf("\n[Block %d] ", block->info.index);
		_print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);
		printf("\n");
		if (i == 0)
			continue;
		for (j = 0; j < llist_size(block->transactions); j++)
		{
			t_token = llist_get_node_at(block->transactions, j);
			print_transaction(s, t_token);
		}
	}
	printf("\n");
	return (1);
}

/**
* bi_pending - displays the pending transactions
* @s: state manager
* @arg1: unused
* @arg2: unused
*
* Return: 0 when program must close, else 1
*/
int bi_pending(state_manager_t *s, char *arg1, char *arg2)
{
	int i;
	transaction_t *t_token;

	(void)arg1;
	(void)arg2;

	printf("[Pending Transactions]\n");
	for (i = 0; i < llist_size(s->pending); i++)
	{
		t_token = llist_get_node_at(s->pending, i);
		print_transaction(s, t_token);
	}

	return (1);
}

/**
* bi_wallet - displays wallet info
* @s: state manager
* @arg1: target
* @arg2: unused
*
* Return: 0 when program must close, else 1
*/
int bi_wallet(state_manager_t *s, char *arg1, char *arg2)
{
	uint32_t balance = 0;
	user_t *user;
	uint8_t *pub, temp[EC_PUB_LEN];
	char *name = "Unknown";

	(void)arg2;

	user = s->user;
	if (arg1)
		user = find_user(s->all_users, arg1);
	if (user != NULL)
	{
		pub = user->pub;
		name = user->name;
	}
	else if (convert_key(arg1, temp))
		pub = temp;
	else
		return (e_print(1, "Invalid Key Format.\n"));

	printf("[%s's Wallet]\n", name);
	printf("Public Key: ");
	_print_hex_buffer(pub, EC_PUB_LEN);
	printf("\n");

	balance = check_balance(s->bc->unspent, pub);
	printf("Verified Balance: [%u]\n", balance);

	balance = check_balance(s->utxo, pub);
	printf("Effective Balance: [%u]\n", balance);

	balance = balance + pending_balance(s->pending, pub);
	printf("Pending Balance: [%u]\n", balance);

	return (1);
}

/**
* pending_balance - calculates reimbursment if block was to be mined
* @pending: list of pending transactions
* @pub: key to match for
*
* Return: amount to be returned
*/
uint32_t pending_balance(llist_t *pending, uint8_t pub[EC_PUB_LEN])
{
	transaction_t *t_token;
	tx_out_t *o_token;
	int i, j;
	uint32_t out = 0;

	for (i = 0; i < llist_size(pending); i++)
	{
		t_token = llist_get_node_at(pending, i);
		for (j = 0; j < llist_size(t_token->outputs); j++)
		{
			o_token = llist_get_node_at(t_token->outputs, j);
			if (memcmp(o_token->pub, pub, EC_PUB_LEN) == 0)
				out += o_token->amount;
		}
	}

	return (out);
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
	(void)arg2;

	printf("Commands:\n");
	printf("\thelp\n");
	printf("\tmine\n");
	printf("\tsend <amount> <user/address>\n");
	printf("\tprint <block index> <range end>\n");
	printf("\tpending\n");
	printf("\twallet <user/address>\n");
	printf("\tlogout\n");
	printf("\texit\n");
	if (arg1 && !strcmp(arg1, "debug"))
	{
		printf("\nDebug Commands:\n");
		printf("\twallet_load <path>\n");
		printf("\twallet_save <path>\n");
		printf("\tinfo\n");
		printf("\tload <path>\n");
		printf("\tsave <path>\n\n");
	}

	return (1);
}
