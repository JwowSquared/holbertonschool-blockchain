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
	EVP_PKEY *pkey = NULL;
	BIO *bio = NULL;
	char *path = NULL;

	if (stat(folder, &st) == -1)
		mkdir(folder, 0700);

	bio = BIO_new(BIO_s_file());

	path = malloc(sizeof(char) * (strlen(folder) + 12));

	sprintf(path, "%s%s", folder, "/key.pem");
	BIO_write_filename(bio, path);

	pkey = EVP_PKEY_new();
	EVP_PKEY_assign_EC_KEY(pkey, key);

	PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, 0, NULL);

	sprintf(path, "%s%s", folder, "/key_pub.pem");
	BIO_write_filename(bio, path);

	PEM_write_bio_PUBKEY(bio, pkey);

	BIO_free_all(bio);
	free(path);

	return (1);
}
