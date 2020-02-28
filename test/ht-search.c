#include <stdio.h>
#include <string.h>

#include "hash_table.h"

int main(void)
{
	ht_hash_table* ht = ht_new();
	for (int i = 0; i < 200; i++)
	{
		char key[8];
		sprintf(key, "key %d", i);
		char value[10];
		sprintf(value, "value %d", i);
		ht_insert(ht, key, value);
	}

	for (int i = 0; i < 200; i++)
	{
		char key[8];
		sprintf(key, "key %d", i);
		char value[10];
		sprintf(value, "value %d", i);
		
		if (strcmp(value, ht_search(ht, key)) != 0)
			return 1;
	}
	ht_del_hash_table(ht);
	return 0;
}
