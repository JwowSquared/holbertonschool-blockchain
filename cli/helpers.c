#include "cli.h"

void display_welcome(void)
{
	printf("==================================\n\n");
	printf("   Welcome to Blockchain CLI!\n");
	printf("   A new blockchain and wallet\n");
	printf("   have been generated for you.\n\n");
	printf("==================================\n");
	bi_help(NULL, NULL, NULL, NULL, NULL);
}

/**
*
*
*/
uint32_t check_balance(llist_t *all_unspent, uint8_t key_in[EC_PUB_LEN])
{
	unspent_tx_out_t *u_token;
	int i;
	uint32_t balance = 0;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		u_token = llist_get_node_at(all_unspent, i);
		if (memcmp(u_token->out.pub, key_in, EC_PUB_LEN) == 0)
			balance += u_token->out.amount;
	}

	return (balance);
}

void convert_key(char *key, uint8_t pub[EC_PUB_LEN])
{
	uint32_t i = 0, j = 0, left, right;

	while (i < EC_PUB_LEN)
	{
		left = key[j];
		if (left >= 97)
			left -= 87;
		else
			left -= 48;
		right = key[j + 1];
		if (right >= 97)
			right -= 87;
		else
			right -= 48;

		pub[i] = left << 4;
		pub[i] += right;
		j += 2;
		i += 1;
	}
}
