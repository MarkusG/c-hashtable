#include <stdio.h>
#include <string.h>

#include "hash_table.h"

int main(void)
{
	ht_hash_table* ht = ht_new();
	ht_insert(ht, "mykey", "myvalue");
	if (strcmp(ht_search(ht, "mykey"), "myvalue"))
		return 1;
	ht_del_hash_table(ht);
	return 0;
}
