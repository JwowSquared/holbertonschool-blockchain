#include "cli.h"

/**
* gumball - matches cmd with function to return
* @cmd: command to enter the gumball machine
*
* Return: function pointer to corresponding command
*/
int (*gumball(char *cmd))(state_manager_t *, char *, char *)
{
	int i;
	gumball_t pot[] = {
		{"help", &bi_help},
		{"wallet_load", &bi_wallet_load},
		{"wallet_save", &bi_wallet_save},
		{"send", &bi_send},
		{"mine", &bi_mine},
		{"info", &bi_info},
		{"load", &bi_load},
		{"save", &bi_save}
	};

	if (cmd == NULL)
		return (NULL);

	for (i = 0; i < 8; i++)
	{
		if (!strcmp(pot[i].cmd, cmd))
			return (pot[i].f);
	}
	return (NULL);
}
