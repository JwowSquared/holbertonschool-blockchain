# blockchain CLI Extension #

# Dependencies #
OpenSSL v1.0.1f

# Install #
1. in `llist/`, run `install.so`
2. in `crypto/`, make `libhblk_crypto.a`
3. in `blockchain/v0.3/`, make `libhblk_blockchain.a`
4. in `cli/`, make `main`

# What is Blockchain CLI? #
The Blockchain CLI is a project for the Low Level specialization at Holberton School. Over 2 months, I built my own interactive tech demo of a blockchain. You can `save` and `load` serialized blockchains to/from file. You can `send` to create a pending transaction, and `mine` the block to add it to the blockchain. You can also `wallet_save` and `wallet_load` key pairs to/from file, to change who is performing transactions. And finally you can display `info` about your current balance, and the raw blockchain data structure!

# What is the Blockchain CLI Extension? #
The base CLI was functional, however I felt it was too clunky for the average user. To solve this, I added and revamped many features! Firstly, blockchain and key pair data are saved and loaded automatically now. Key pairs are generated when you create a `newuser`, and are attached to the username and password you choose. Then in the future, you can `login` to access that wallet. You can now show your `wallet`, which gives you advanced information on your avaliable, effective, and pending balance. You can also use `wallet` to view this information of other users/addresses in the blockchain! `print` now exists to display the blockchain in a human readable format. `print` can be given a `target index` to print only that specific block from the chain, or even print a range of blocks. You can also `logout` to switch users while maintaining the pending transaction list. `pending` will also show you the list of pending transactions!

# Thanks #
Thanks.
