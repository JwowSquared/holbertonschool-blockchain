#include "cli.h"

/**
*
*
*
*/
int (*gumball(char *cmd))(blockchain_t *, EC_KEY *, char *, char *)
{
	int i;
	gumball_t pot[] = {
		{"wallet_load", &bi_wallet_load},
		{"wallet_save", &bi_wallet_save},
		{"send", &bi_send},
		{"mine", &bi_mine},
		{"info", &bi_info},
		{"load", &bi_load},
		{"save", &bi_save}
	};

	for (i = 0; i < 7; i++)
	{
		if (!strcmp(pot[i].cmd, cmd))
			return (pot[i].f);
	}
	return (NULL);
}
