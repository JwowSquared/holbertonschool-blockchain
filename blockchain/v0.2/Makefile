compiler = gcc -Wall -Wextra -Werror -pedantic -I.
flags = -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

files-0 = hash_matches_difficulty.c test/hash_matches_difficulty-main.c
task0: $(files-0)
	$(compiler) -o task0 $(files-0) $(flags)

files-1 = blockchain_create.c block_create.c block_destroy.c \
blockchain_destroy.c block_hash.c block_is_valid.c test/block_is_valid-main.c
task1: $(files-1)
	$(compiler) -o task1 $(files-1) $(flags)

files-2 = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c \
block_hash.c block_is_valid.c hash_matches_difficulty.c block_mine.c \
provided/_genesis.c provided/_blockchain_print.c test/block_mine-main.c
task2: $(files-2)
	$(compiler) -o task2 $(files-2) $(flags)

files-3 = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c \
block_hash.c blockchain_difficulty.c provided/_genesis.c \
provided/_blockchain_print.c test/blockchain_difficulty-main.c
task3: $(files-3)
	$(compiler) -o task3 $(files-3) $(flags)

clean:
	rm task0 task1 task2 task3
