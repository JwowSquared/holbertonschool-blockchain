compiler = gcc -Wall -Wextra -Werror -pedantic -I.
flags = -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

files-0 = blockchain_create.c test/blockchain_create-main.c \
provided/_blockchain_print.c provided/_blockchain_destroy.c
task0: $(files-0)
	$(compiler) -o task0 $(files-0) $(flags)

files-1 = blockchain_create.c block_create.c test/block_create-main.c \
provided/_blockchain_print.c provided/_blockchain_destroy.c
task1: $(files-1)
	$(compiler) -o task1 $(files-1) $(flags)

files-2 = blockchain_create.c block_create.c block_destroy.c \
test/block_destroy-main.c provided/_blockchain_destroy.c
task2: $(files-2)
	$(compiler) -o task2 $(files-2) $(flags)

files-3 = blockchain_destroy.c blockchain_create.c block_create.c \
block_destroy.c test/blockchain_destroy-main.c
task3: $(files-3)
	$(compiler) -o task3 $(files-3) $(flags)

files-4 = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c \
block_hash.c test/block_hash-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c
task4: $(files-4)
	$(compiler) -o task4 $(files-4) $(flags)

files-5 = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c \
block_hash.c blockchain_serialize.c provided/_endianness.c test/blockchain_serialize-main.c
task5: $(files-5)
	$(compiler) -o task5 $(files-5) $(flags)

files-6 = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c \
blockchain_deserialize.c provided/_blockchain_print.c provided/_endianness.c test/blockchain_deserialize-main.c
task6: $(files-6)
	$(compiler) -o task6 $(files-6) $(flags)

files-7 = blockchain_create.c block_create.c block_destroy.c \
blockchain_destroy.c block_hash.c block_is_valid.c test/block_is_valid-main.c
task7: $(files-7)
	$(compiler) -o task7 $(files-7) $(flags)

clean:
	rm task0 task1 task2 task3 task4 task5 task6 task7
