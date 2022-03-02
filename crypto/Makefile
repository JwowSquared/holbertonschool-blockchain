all: task0 task1 task2 task3

task0: sha256.c provided/_print_hex_buffer.c test/sha256-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task0 test/sha256-main.c provided/_print_hex_buffer.c sha256.c -lssl -lcrypto

task1: ec_create.c test/ec_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task1 test/ec_create-main.c ec_create.c -lssl -lcrypto

task2: ec_to_pub.c ec_create.c provided/_print_hex_buffer.c test/ec_to_pub-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task2 test/ec_to_pub-main.c provided/_print_hex_buffer.c ec_to_pub.c ec_create.c -lssl -lcrypto

task3: ec_from_pub.c ec_to_pub.c ec_create.c provided/_print_hex_buffer.c test/ec_from_pub-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task3 test/ec_from_pub-main.c provided/_print_hex_buffer.c ec_from_pub.c ec_to_pub.c ec_create.c -lssl -lcrypto

clean:
	rm task0 task1 task2 task3
