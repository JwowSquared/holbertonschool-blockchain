#include "blockchain.h"

void header_setup(block_header_t *);

/**
* blockchain_serialize - saves a blockchain to file
* @blockchain: structure to save
* @path: file target
*
* Return: 0 on success, else -1
*/
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *file = NULL;
	uint32_t i = 0;
	block_t *block;
	block_header_t header;

	header_setup(&header);
	header.blocks = llist_size(blockchain->chain);

	file = fopen(path, "wb");
	if (!file)
		return (-1);

	fwrite(&header, 1, sizeof(header), file);
	while (i < header.blocks)
	{
		block = llist_get_node_at(blockchain->chain, i);
		fwrite(block, 1, 56, file);
		fwrite(&block->data.len, 1, 4, file);
		fwrite(&block->data.buffer, 1, block->data.len, file);
		fwrite(&block->hash, 1, 32, file);
		i++;
	}
	fclose(file);
	return (0);
}

/**
* header_setup - sets up the header for blockchain serializing
* @header: header to setup
*/
void header_setup(block_header_t *header)
{
	header->magic[0] = 'H';
	header->magic[1] = 'B';
	header->magic[2] = 'L';
	header->magic[3] = 'K';
	header->version[0] = '0';
	header->version[1] = '.';
	header->version[2] = '1';
	header->endian = 1;
	header->blocks = 0;
}
