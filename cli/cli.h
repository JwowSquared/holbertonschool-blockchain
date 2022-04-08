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
	int (*f)(blockchain_t *, EC_KEY *, char *, char *);
} gumball_t;

int (*gumball(char *cmd))(blockchain_t *, EC_KEY *, char *, char *);

int bi_wallet_load(blockchain_t *, EC_KEY *, char *, char *);
int bi_wallet_save(blockchain_t *, EC_KEY *, char *, char *);
int bi_send(blockchain_t *, EC_KEY *, char *, char *);
int bi_mine(blockchain_t *, EC_KEY *, char *, char *);
int bi_info(blockchain_t *, EC_KEY *, char *, char *);
int bi_load(blockchain_t *, EC_KEY *, char *, char *);
int bi_save(blockchain_t *, EC_KEY *, char *, char *);

#endif /* _CLI_H_ */
