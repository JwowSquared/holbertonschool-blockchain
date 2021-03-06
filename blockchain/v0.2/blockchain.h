#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

#include <stdlib.h>
#include <stdint.h>
#include <llist.h>
#include "../../crypto/hblk_crypto.h"
#include "provided/endianness.h"

#define BLOCKCHAIN_DATA_MAX 1024
#define BLOCK_GENERATION_INTERVAL 1
#define DIFFICULTY_ADJUSTMENT_INTERVAL 5

/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain: Linked list of pointers to block_t
 */
typedef struct blockchain_s
{
	llist_t	 *chain;
} blockchain_t;

/**
 * struct block_info_s - Block info structure
 *
 * @index:	  Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp:  Time the Block was created at (UNIX timestamp)
 * @nonce:	  Salt value used to alter the Block hash
 * @prev_hash:  Hash of the previous Block in the Blockchain
 */
typedef struct block_info_s
{
	/*
	 * The order of the elements in this structure should remain the same.
	 * It was designed so every element of this structure is aligned and
	 * doesn't require padding from the compiler.
	 * Therefore, it is possible to use the structure as an array of char,
	 * on any architecture.
	 */
	uint32_t	index;
	uint32_t	difficulty;
	uint64_t	timestamp;
	uint64_t	nonce;
	uint8_t		prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

/**
 * struct block_data_s - Block data
 *
 * @buffer: Data buffer
 * @len:    Data size (in bytes)
 */
typedef struct block_data_s
{
	/*
	 * @buffer must stay first, so we can directly use the structure as
	 * an array of char
	 */
	int8_t      buffer[BLOCKCHAIN_DATA_MAX];
	uint32_t    len;
} block_data_t;

/**
 * struct block_s - Block structure
 *
 * @info: Block info
 * @data: Block data
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s
{
	block_info_t	info; /* This must stay first */
	block_data_t	data; /* This must stay second */
	uint8_t	 hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
* struct block_header_s - used for blockchain I/O
*
* @magic: identifies file as blockchain
* @version: version of blockchain
* @endian: 1 or 2 for little or big endian
* @blocks: number of blocks in block chain
*/
typedef struct block_header_s
{
	unsigned char magic[4];
	unsigned char version[3];
	unsigned char endian;
	uint32_t blocks;
} block_header_t;



blockchain_t *blockchain_create(void);

block_t *block_create(block_t const *, int8_t const *, uint32_t);

void block_destroy(block_t *);

void blockchain_destroy(blockchain_t *);

uint8_t *block_hash(block_t const *, uint8_t hash_buf[SHA256_DIGEST_LENGTH]);

int blockchain_serialize(blockchain_t const *, char const *);

blockchain_t *blockchain_deserialize(char const *);

int block_is_valid(block_t const *, block_t const *);



int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH], uint32_t difficulty);

void block_mine(block_t *block);

uint32_t blockchain_difficulty(blockchain_t const *blockchain);

#endif /* _BLOCKCHAIN_H_ */
