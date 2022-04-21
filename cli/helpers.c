#include "cli.h"

/**
* display_welcome - prints a welcome message
* @name: name of user
*/
void display_welcome(char *name)
{
	int padlen;

	padlen = (34 - strlen(name)) / 2;

	printf("==================================\n");
	printf("          Logged in as:\n");
	printf("%*s%s\n", padlen, "", name);
	printf("    Welcome to Blockchain CLI!\n");
	printf("==================================\n");
	bi_help(NULL, NULL, NULL);
}

/**
* check_balance - determines the wallet balance of a key
* @all_unspent: linked list of all unspent transactions
* @key_in: key to determine balance of
*
* Return: balance of wallet
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

/**
* convert_key - converts a string into a public key
* @key: string to convert
* @pub: buffer to write to
*
* Return: 1 on success, else 0
*/
int convert_key(char *key, uint8_t pub[EC_PUB_LEN])
{
	uint32_t i = 0, j = 0, left, right;

	if (strlen(key) != EC_PUB_LEN * 2)
		return (0);

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

		if (left > 15 || right > 15)
			return (0);

		pub[i] = left << 4;
		pub[i] += right;
		j += 2;
		i += 1;
	}

	return (1);
}

/**
* safe_free - makes sure free doesnt get passed NULL
* @s: string to free
*/
void safe_free(char *s)
{
	if (s)
		free(s);
}

/**
* e_print - prints errors
* @code: return value
* @prompt: error to print
*
* Return: code
*/
int e_print(int code, char *prompt)
{
	printf("%s", prompt);
	return (code);
}
