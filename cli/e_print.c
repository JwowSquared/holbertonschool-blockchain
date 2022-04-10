#include "cli.h"

/**
* e_print - prints errors
* @prompt: error to print
*
* Return: always 0
*/
int e_print(char *prompt)
{
	printf("%s", prompt);
	return (0);
}
