#include "blockchain.h"

int check_header(block_header_t *);
void read_transactions(block_t *block, FILE *file);

/**
* blockchain_deserialize - loads a blockchain to file
* @path: file target
*
* Return: pointer to new blockchain, else NULL
*/
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *file = NULL;
	uint32_t i;
	block_t *block;
	block_header_t header;
	blockchain_t *out;
	unspent_tx_out_t *u_token;

	file = fopen(path, "rb");
	if (!file)
		return (NULL);

	fread(&header, sizeof(header), 1, file);
	if (!check_header(&header))
		return (NULL);

	if (header.blocks == 0)
	{
		fclose(file);
		return (NULL);
	}

	out = malloc(sizeof(blockchain_t));
	out->chain = llist_create(MT_SUPPORT_FALSE);
	out->unspent = llist_create(MT_SUPPORT_FALSE);
	for (i = 0; i < header.blocks; i++)
	{
		block = malloc(sizeof(block_t));
		fread(block, 56, 1, file);
		fread(&block->data.len, 4, 1, file);
		memset(block->data.buffer, 0, sizeof(block->data.buffer));
		fread(&block->data.buffer, block->data.len, 1, file);
		fread(&block->hash, 32, 1, file);
		read_transactions(block, file);
		llist_add_node(out->chain, block, ADD_NODE_REAR);
	}
	for (i = 0; i < header.unspent; i++)
	{
		u_token = malloc(sizeof(unspent_tx_out_t));
		fread(u_token, 165, 1, file);
		llist_add_node(out->unspent, u_token, ADD_NODE_REAR);
	}
	fclose(file);
	return (out);
}

/**
* read_transactions - reads transactions from file
* @block: block for transactions to be read into
* @file: open file pointer
*/
void read_transactions(block_t *block, FILE *file)
{
	int i, j, num_in, num_out, t_size;
	transaction_t *t_token;
	tx_in_t *i_token;
	tx_out_t *o_token;

	fread(&t_size, 4, 1, file);
	if (t_size == -1)
	{
		block->transactions = NULL;
		return;
	}
	block->transactions = llist_create(MT_SUPPORT_FALSE);
	for (i = 0; i < t_size; i++)
	{
		t_token = malloc(sizeof(transaction_t));
		fread(t_token, 32, 1, file);
		fread(&num_in, 4, 1, file);
		fread(&num_out, 4, 1, file);
		t_token->inputs = llist_create(MT_SUPPORT_FALSE);
		for (j = 0; j < num_in; j++)
		{
			i_token = malloc(sizeof(tx_in_t));
			fread(i_token, 169, 1, file);
			llist_add_node(t_token->inputs, i_token, ADD_NODE_REAR);
		}
		t_token->outputs = llist_create(MT_SUPPORT_FALSE);
		for (j = 0; j < num_out; j++)
		{
			o_token = malloc(sizeof(tx_out_t));
			fread(o_token, 101, 1, file);
			llist_add_node(t_token->outputs, o_token, ADD_NODE_REAR);
		}
		llist_add_node(block->transactions, t_token, ADD_NODE_REAR);
	}
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
	if (header->version[2] != '3')
		return (0);

	return (1);
}
