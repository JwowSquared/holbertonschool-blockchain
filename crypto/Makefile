compiler = gcc -Wall -Wextra -Werror -pedantic -I.
flags = -lssl -lcrypto

lib-files = \
sha256.o \
ec_create.o \
ec_to_pub.o \
ec_from_pub.o \
ec_save.o \
ec_load.o \
ec_sign.o \
ec_verify.o

libhblk_crypto.a: $(lib-files)
	ar rcs libhblk_crypto.a $(lib-files)

sha256.o: sha256.c
	$(compiler) -c sha256.c $(flags)
ec_create.o: ec_create.c
	$(compiler) -c ec_create.c $(flags)
ec_to_pub.o: ec_to_pub.c
	$(compiler) -c ec_to_pub.c $(flags)
ec_from_pub.o: ec_from_pub.c
	$(compiler) -c ec_from_pub.c $(flags)
ec_save.o: ec_save.c
	$(compiler) -c ec_save.c $(flags)
ec_load.o: ec_load.c
	$(compiler) -c ec_load.c $(flags)
ec_sign.o: ec_sign.c
	$(compiler) -c ec_sign.c $(flags)
ec_verify.o: ec_verify.c
	$(compiler) -c ec_verify.c $(flags)

files-0 = sha256.c provided/_print_hex_buffer.c test/sha256-main.c
task0: $(files-0)
	$(compiler) -o task0 $(files-0) $(flags)

files-1 = ec_create.c test/ec_create-main.c
task1: $(files-1)
	$(compiler) -o task1 $(files-1) $(flags)

files-2 = ec_to_pub.c ec_create.c provided/_print_hex_buffer.c test/ec_to_pub-main.c
task2: $(files-2)
	$(compiler) -o task2 $(files-2) $(flags)

files-3 = ec_from_pub.c ec_to_pub.c ec_create.c provided/_print_hex_buffer.c test/ec_from_pub-main.c
task3: $(files-3)
	$(compiler) -o task3 $(files-0) $(flags)

files-4 = ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c test/ec_save-main.c
task4: $(files-4)
	$(compiler) -o task4 $(files-4) $(flags)

files-5 = ec_load.c ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c test/ec_load-main.c
task5: $(files-5)
	$(compiler) -o task5 $(files-5) $(flags)

files-6 = ec_sign.c ec_create.c provided/_print_hex_buffer.c test/ec_sign-main.c
task6: $(files-6)
	$(compiler) -o task6 $(files-6) $(flags)

files-7 = ec_verify.c ec_sign.c ec_create.c provided/_print_hex_buffer.c test/ec_verify-main.c
task7: $(files-7)
	$(compiler) -o task7 $(files-7) $(flags)

clean:
	rm task0 task1 task2 task3 task4 task5 task6 task7 $(lib-files) libhblk_crypto.a
