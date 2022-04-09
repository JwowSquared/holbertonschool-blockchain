#ifndef _CLI_H_
#define _CLI_H_

#include <stdio.h>
#include <stdint.h>
#include <llist.h>
#include "../crypto/hblk_crypto.h"
#include "../blockchain/v0.3/blockchain.h"

typedef struct gball_s
{
	char *cmd;
	int (*f)(blockchain_t **, block_t **, EC_KEY **, char *, char *);
} gumball_t;

/* Gumball */
int (*gumball(char *cmd))(blockchain_t **, block_t **, EC_KEY **, char *, char *);

/* Builtin Functions */
int bi_help(blockchain_t **, block_t **, EC_KEY **, char *, char *);
int bi_wallet_load(blockchain_t **, block_t **, EC_KEY **, char *, char *);
int bi_wallet_save(blockchain_t **, block_t **, EC_KEY **, char *, char *);
int bi_send(blockchain_t **, block_t **, EC_KEY **, char *, char *);
int bi_mine(blockchain_t **, block_t **, EC_KEY **, char *, char *);
int bi_info(blockchain_t **, block_t **, EC_KEY **, char *, char *);
int bi_load(blockchain_t **, block_t **, EC_KEY **, char *, char *);
int bi_save(blockchain_t **, block_t **, EC_KEY **, char *, char *);

/* Helper Functions */
void display_welcome(void);
uint32_t check_balance(llist_t *all_unspent, uint8_t key_in[EC_PUB_LEN]);

/* Provided Functions */
void _blockchain_print(blockchain_t const *blockchain);
void _print_hex_buffer(uint8_t const *buf, size_t len);

#endif /* _CLI_H_ */