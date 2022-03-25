#include "hblk_crypto.h"

/**
* ec_load - reads key pair from destination folder
* @folder: root folder to read from
*
* Return: 1 on success, else 0
*/
EC_KEY *ec_load(char const *folder)
{
	FILE *fp = NULL;
	char *path = NULL;
	EC_KEY *out = NULL;

	out = EC_KEY_new_by_curve_name(EC_CURVE);

	path = malloc(sizeof(char) * (strlen(folder) + 13));

	sprintf(path, "%s%s%s", folder, "/", PUB_FILENAME);
	fp = fopen(path, "r");
	PEM_read_EC_PUBKEY(fp, &out, NULL, NULL);
	fclose(fp);

	sprintf(path, "%s%s%s", folder, "/", PRI_FILENAME);
	fp = fopen(path, "r");
	PEM_read_ECPrivateKey(fp, &out, NULL, NULL);
	fclose(fp);

	free(path);

	return (out);
}
