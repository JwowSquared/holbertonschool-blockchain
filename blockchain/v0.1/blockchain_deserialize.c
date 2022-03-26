#include "blockchain.h"

int check_header(block_header_t *);
void swap_block(block_t *);

/**
* blockchain_deserialize - loads a blockchain to file
* @path: file target
*
* Return: pointer to new blockchain, else NULL
*/
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *file = NULL;
	uint32_t i = 0;
	block_t *block;
	block_header_t header;
	blockchain_t *out;

	file = fopen(path, "rb");
	if (!file)
		return (NULL);

	fread(&header, sizeof(header), 1, file);
	if (!check_header(&header))
		return (NULL);
	if (header.endian == 2)
		_swap_endian(&header.blocks, sizeof(header.blocks));

	if (header.blocks == 0)
	{
		fclose(file);
		return (NULL);
	}

	out = malloc(sizeof(blockchain_t));
	if (out == NULL)
		return (NULL);
	out->chain = llist_create(MT_SUPPORT_FALSE);

	while (i < header.blocks)
	{
		block = malloc(sizeof(block_t));
		if (block == NULL)
			return (NULL); /* This would be bad */
		fread(block, 56, 1, file);
		fread(&block->data.len, 4, 1, file);
		if (header.endian == 2)
			swap_block(block);
		fread(&block->data.buffer, block->data.len, 1, file);
		fread(&block->hash, 32, 1, file);

		llist_add_node(out->chain, block, ADD_NODE_REAR);
		i++;
	}
	fclose(file);
	return (out);
}

/**
* check_header - determines if a header is valid
* @header: header to check
*
* Return: 1 on success, else 0
*/
int check_header(block_header_t *header)
{
	if (header->magic[0] != 'H')
		return (0);
	if (header->magic[1] != 'B')
		return (0);
	if (header->magic[2] != 'L')
		return (0);
	if (header->magic[3] != 'K')
		return (0);
	if (header->version[0] != '0')
		return (0);
	if (header->version[1] != '.')
		return (0);
	if (header->version[2] != '1')
		return (0);

	return (1);
}

/**
* swap_block - swaps the endianness of a block
* @block: block to swap
*/
void swap_block(block_t *block)
{
	printf("swappies\n");
	_swap_endian(&block->info.index, 4);
	_swap_endian(&block->info.difficulty, 4);
	_swap_endian(&block->info.timestamp, 8);
	_swap_endian(&block->info.nonce, 8);
	_swap_endian(&block->data.len, 4);
}
