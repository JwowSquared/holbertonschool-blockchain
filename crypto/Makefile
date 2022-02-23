all: task0

task0: sha256.c provided/_print_hex_buffer.c test/sha256-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task0 test/sha256-main.c provided/_print_hex_buffer.c sha256.c -lssl -lcrypto

clean:
	rm task0
