#include "blockchain.h"

void write_transactions(llist_t *transactions, FILE *file);
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
	uint32_t i;
	int t_size;
	block_t *block;
	unspent_tx_out_t *u_token;
	block_header_t header;

	header_setup(&header);
	header.blocks = llist_size(blockchain->chain);
	header.unspent = llist_size(blockchain->unspent);

	file = fopen(path, "wb");
	if (!file)
		return (-1);

	fwrite(&header, 1, sizeof(header), file);
	for (i = 0; i < header.blocks; i++)
	{
		block = llist_get_node_at(blockchain->chain, i);
		fwrite(block, 1, 56, file);
		fwrite(&block->data.len, 1, 4, file);
		fwrite(&block->data.buffer, 1, block->data.len, file);
		fwrite(&block->hash, 1, 32, file);
		if (block->info.index == 0)
			t_size = -1;
		else
			t_size = llist_size(block->transactions);
		fwrite(&t_size, 1, 4, file);
		write_transactions(block->transactions, file);
	}

	for (i = 0; i < header.unspent; i++)
	{
		u_token = llist_get_node_at(blockchain->unspent, i);
		fwrite(u_token, 1, 165, file);
	}

	fclose(file);
	return (0);
}

/**
* write_transactions - writes a list of transactions to file
* @transactions: list of transactions
* @file: open file pointer
*/
void write_transactions(llist_t *transactions, FILE *file)
{
	int i, j, num_in, num_out;
	transaction_t *t_token;
	tx_in_t *i_token;
	tx_out_t *o_token;

	for (i = 0; i < llist_size(transactions); i++)
	{
		t_token = llist_get_node_at(transactions, i);
		num_in = llist_size(t_token->inputs);
		num_out = llist_size(t_token->outputs);
		fwrite(t_token, 1, 32, file);
		fwrite(&num_in, 1, 4, file);
		fwrite(&num_out, 1, 4, file);
		for (j = 0; j < num_in; j++)
		{
			i_token = llist_get_node_at(t_token->inputs, j);
			fwrite(i_token, 1, 169, file);
		}
		for (j = 0; j < num_out; j++)
		{
			o_token = llist_get_node_at(t_token->outputs, j);
			fwrite(o_token, 1, 101, file);
		}
	}
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
	header->version[2] = '3';
	header->endian = 1;
	header->blocks = 0;
	header->unspent = 0;
}
