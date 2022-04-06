#include "transaction.h"

/**
* transaction_destroy - destroys transaction
* @transaction: destroy me
*/
void transaction_destroy(transaction_t *transaction)
{
	if (transaction == NULL)
		return;

	if (transaction->inputs)
		llist_destroy(transaction->inputs, 1, NULL);
	if (transaction->outputs)
		llist_destroy(transaction->outputs, 1, NULL);

	free(transaction);
}
