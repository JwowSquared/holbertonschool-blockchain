#include "cli.h"

int bi_help(blockchain_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
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

int bi_wallet_load(blockchain_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	EC_KEY *out;

	(void)bc;
	(void)active;
	(void)arg2;

	if (arg1 == NULL)
	{
		printf("Usage: wallet_load <path>\n");
		return (1);
	}

	out = ec_load(arg1);
	if (out == NULL)
	{
		printf("Error loading wallet from %s\n", arg1);
		return (1);
	}

	*key = out;
	printf("Successfully loaded wallet\n");

	return (1);
}

int bi_wallet_save(blockchain_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	(void)bc;
	(void)active;
	(void)arg2;

	if (arg1 == NULL)
	{
		printf("Usage: wallet_save <path>\n");
		return (1);
	}

	if (ec_save(*key, arg1) == -1)
	{
		printf("Error saving key to %s\n", arg1);
		return (1);
	}

	printf("Successfully saved wallet\n");

	return (1);
}

int bi_send(blockchain_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	(void)bc;
	(void)active;
	(void)key;
	printf("REACHED SEND %s %s\n", arg1, arg2);
	return (1);
}

int bi_mine(blockchain_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	int i;
	llist_t *verified;
	transaction_t *t_token;

	(void)arg1;
	(void)arg2;

	verified = llist_create(MT_SUPPORT_FALSE);
	t_token = coinbase_create(*key, (*active)->info.index);
	llist_add_node(verified, t_token, ADD_NODE_REAR);
	for (i = 0; i < llist_size((*active)->transactions); i++)
	{
		t_token = llist_get_node_at((*active)->transactions, i);
		if (transaction_is_valid(t_token, (*bc)->unspent))
			llist_add_node(verified, t_token, ADD_NODE_REAR);
		else
		{
			printf("Transaction %d invalid; skipped\n", i);
		}
	}

	llist_destroy((*active)->transactions, 0, NULL);
	(*active)->transactions = verified;

	llist_add_node((*bc)->chain, *active, ADD_NODE_REAR);
	(*active)->info.difficulty = blockchain_difficulty(*bc);
	block_mine(*active);

	(*bc)->unspent = update_unspent((*active)->transactions, (*active)->hash, (*bc)->unspent);
	*active = block_create(*active, (int8_t *)"Minecraft", 9);

	return (1);
}

int bi_info(blockchain_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	uint8_t pub[EC_PUB_LEN];

	(void)active;
	(void)arg1;
	(void)arg2;

	printf("=====================================\n");
	printf("num Blocks: %d\n", llist_size((*bc)->chain));
	printf("num Unspent: %d\n", llist_size((*bc)->unspent));
	printf("num Pending Transactions: %d\n", llist_size((*active)->transactions));
	printf("Your Address: ");
	_print_hex_buffer(ec_to_pub(*key, pub), EC_PUB_LEN);
	printf("\nBalance: %u\n", check_balance((*bc)->unspent, pub));
	printf("=====================================\n");
	_blockchain_print(*bc);

	return (1);
}

int bi_load(blockchain_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	blockchain_t *out;

	(void)active;
	(void)key;
	(void)arg2;

	if (arg1 == NULL)
	{
		printf("Usage: load <path>\n");
		return (1);
	}

	out = blockchain_deserialize(arg1);
	if (out == NULL)
	{
		printf("Error loading blockchain from %s\n", arg1);
		return (1);
	}

	blockchain_destroy(*bc);
	*bc = out;

	printf("Successfully loaded blockchain\n");

	return (1);
}

int bi_save(blockchain_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	(void)active;
	(void)key;
	(void)arg2;

	if (arg1 == NULL)
	{
		printf("Usage: save <path>\n");
		return (1);
	}

	if (blockchain_serialize(*bc, arg1) == -1)
	{
		printf("Error saving blockchain to %s\n", arg1);
		return (1);
	}

	printf("Successfully saved blockchain\n");

	return (1);
}
