#include "hblk_crypto.h"

/**
* ec_save - saves a key pair to the destination folder
* @key: key pair to save
* @folder: root folder to create files in
*
* Return: 1 on success, else 0
*/
int ec_save(EC_KEY *key, char const *folder)
{
	struct stat st = {0};
	FILE *fp = NULL;
	char *path = NULL;

	if (stat(folder, &st) == -1)
		mkdir(folder, 0700);

	path = malloc(sizeof(char) * (strlen(folder) + 13));

	sprintf(path, "%s%s", folder, "/key.pem");
	fp = fopen(path, "w");
	PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL);
	fclose(fp);

	sprintf(path, "%s%s", folder, "/key_pub.pem");
	fp = fopen(path, "w");
	PEM_write_EC_PUBKEY(fp, key);
	fclose(fp);

	free(path);

	return (1);
}
