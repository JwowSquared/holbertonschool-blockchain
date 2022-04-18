#ifndef _CLI_H_
#define _CLI_H_

#include <stdio.h>
#include <stdint.h>
#include <llist.h>
#include "../crypto/hblk_crypto.h"
#include "../blockchain/v0.3/blockchain.h"

#define NAME_MAX_LEN 13

/**
* struct user_s - blockchain user
* @key: key object used for transactions
* @name: user's login name
* @pass: user's hashed password
* @pub: user's public key
*/
typedef struct user_s
{
	EC_KEY *key;
	char name[NAME_MAX_LEN];
	uint8_t pass[SHA256_DIGEST_LENGTH];
	uint8_t pub[EC_PUB_LEN];
} user_t;

/**
* struct state_manager_s - manages the state of the program
* @bc: reference to blockchain
* @pending: transaction list of active block being built
* @user: current user
* @utxo: copy of blockchain's unspent list to remove from on SEND
* @all_users: list of all users
*/
typedef struct state_manager_s
{
	blockchain_t *bc;
	llist_t *pending;
	user_t *user;
	llist_t *utxo;
	llist_t *all_users;
} state_manager_t;

/**
* struct gball_s - pairs string with corresponing function
* @cmd: string
* @f: function
*/
typedef struct gball_s
{
	char *cmd;
	int (*f)(state_manager_t *, char *, char *);
} gumball_t;

/* Gumball */
int (*gumball(char *cmd))(state_manager_t *, char *, char *);

/* User */
user_t *create_user(char *, char *);
void destroy_user(llist_node_t);
llist_t *load_users(void);
int save_users(llist_t *);

/* State Manager */
state_manager_t *create_state_manager(void);
void destroy_state_manager(state_manager_t *);
void dupe_unspent(state_manager_t *s);

/* Login */
void prompt_startup(state_manager_t *s);
void prompt_login(state_manager_t *s);
void prompt_newuser(state_manager_t *s);
user_t *login(llist_t *, char *, char *);
int user_name_exists(llist_t *users, char *name);

/* Builtin Functions */
int bi_help(state_manager_t *, char *, char *);
int bi_send(state_manager_t *, char *, char *);
int bi_mine(state_manager_t *, char *, char *);
int bi_print(state_manager_t *, char *, char *);

/* Print Helper Functions */
void print_transaction(state_manager_t *s, transaction_t *t_token);
char *find_user_name(llist_t *all_users, uint8_t pub[EC_PUB_LEN]);
int find_origin(llist_node_t node, void *data);
int find_tx(llist_node_t node, void *data);
int find_out(llist_node_t node, void *data);

/* Debug Functions */
int bi_wallet_load(state_manager_t *, char *, char *);
int bi_wallet_save(state_manager_t *, char *, char *);
int bi_info(state_manager_t *, char *, char *);
int bi_load(state_manager_t *, char *, char *);
int bi_save(state_manager_t *, char *, char *);

/* Helper Functions */
void display_welcome(char *);
uint32_t check_balance(llist_t *all_unspent, uint8_t key_in[EC_PUB_LEN]);
int convert_key(char *key, uint8_t pub[EC_PUB_LEN]);
void safe_free(char *s);

/* Provided Functions */
void _blockchain_print(blockchain_t const *blockchain);
void _print_hex_buffer(uint8_t const *buf, size_t len);

/* Error Functions */
int e_print(char *prompt);

#endif /* _CLI_H_ */
