#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

int main(void)
{
	ht_hash_table* ht = ht_new();
	for (int i = 0; i < 200; i++)
	{
		char* key = malloc(8 * sizeof(char));
		sprintf(key, "key %d", i);
		char* value = malloc(10 * sizeof(char));
		sprintf(value, "value %d", i);

		ht_insert(ht, key, value);
	}
	ht_del_hash_table(ht);
	return 0;
}
