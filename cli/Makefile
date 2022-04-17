compiler = gcc -Wall -Wextra -Werror -pedantic -g3 -I. -I../crypto -I../blockchain/v0.3/blockchain
flags = -L../crypto -L../blockchain/v0.3 -L../blockchain/v0.3/transaction -Wl,--start-group -lhblk_crypto -lhblk_blockchain -lllist -lssl -lcrypto -pthread -Wl,--end-group

files-main = engine.c state_manager.c user.c login.c gumball.c bi.c bi_io.c e_print.c helpers.c provided/*.c
main: $(files-main)
	$(compiler) -o main $(files-main) $(flags)
