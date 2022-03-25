all: task0 task1 task2 task3 task4 task5 task6 task7

task0: sha256.c provided/_print_hex_buffer.c test/sha256-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task0 test/sha256-main.c provided/_print_hex_buffer.c sha256.c -lssl -lcrypto

task1: ec_create.c test/ec_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task1 test/ec_create-main.c ec_create.c -lssl -lcrypto

task2: ec_to_pub.c ec_create.c provided/_print_hex_buffer.c test/ec_to_pub-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task2 test/ec_to_pub-main.c provided/_print_hex_buffer.c ec_to_pub.c ec_create.c -lssl -lcrypto

task3: ec_from_pub.c ec_to_pub.c ec_create.c provided/_print_hex_buffer.c test/ec_from_pub-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task3 test/ec_from_pub-main.c provided/_print_hex_buffer.c ec_from_pub.c ec_to_pub.c ec_create.c -lssl -lcrypto

task4: ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c test/ec_save-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task4 test/ec_save-main.c ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c -lssl -lcrypto

task5: ec_load.c ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c test/ec_load-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task5 test/ec_load-main.c ec_load.c ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c -lssl -lcrypto

task6: ec_sign.c ec_create.c provided/_print_hex_buffer.c test/ec_sign-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task6 test/ec_sign-main.c provided/_print_hex_buffer.c ec_sign.c ec_create.c -lssl -lcrypto

task7: ec_verify.c ec_sign.c ec_create.c provided/_print_hex_buffer.c test/ec_verify-main.c
	gcc -Wall -Wextra -Werror -pedantic -I. -o task7 test/ec_verify-main.c provided/_print_hex_buffer.c ec_verify.c ec_sign.c ec_create.c -lssl -lcrypto

clean:
	rm task0 task1 task2 task3 task4 task5 task6 task7
