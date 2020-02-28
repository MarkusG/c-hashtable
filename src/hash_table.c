#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/hash_table.h"
#include "prime.h"

static ht_item HT_DELETED_ITEM = { NULL, NULL };

static ht_item* ht_new_item(const char* k, const char* v)
{
	ht_item* i = malloc(sizeof(ht_item));
	i->key = strdup(k);
	i->value = strdup(v);
	return i;
}

static ht_hash_table* ht_new_sized(const int base_size)
{
	ht_hash_table* ht = malloc(sizeof(ht_hash_table));
	ht->base_size = base_size;

	ht->size = next_prime(ht->base_size); // set size to next prime > base_size
	ht->count = 0;
	ht->items = calloc((size_t)ht->size, sizeof(ht_item*)); // zero items
	return ht;
}

static const int HT_INITIAL_BASE_SIZE = 53;

ht_hash_table* ht_new()
{
	return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

static void ht_del_item(ht_item* i)
{
	free(i->key);
	free(i->value);
	free(i);
}

void ht_del_hash_table(ht_hash_table* ht)
{
	for (int i = 0; i < ht->count; i++)
	{
		if(ht->items[i] && ht->items[i] != &HT_DELETED_ITEM)
			ht_del_item(ht->items[i]);
	}
	free(ht->items);
	free(ht);
}

static int ht_hash(const char* s, const int a, const int m)
{
	long long hash = 0;
	const int len_s = strlen(s);
	for (int i = 0; i < len_s; i++)
	{
		hash += (long long)pow(a, len_s - (i + 1)) * s[i];
		hash = hash % m;
	}
	return (int)hash;
}

static const int HT_PRIME_1 = 151;
static const int HT_PRIME_2 = 193;

static int ht_get_hash(const char* s, const int num_buckets, const int attempt)
{
	const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
	const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
	return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

static void ht_resize(ht_hash_table* ht, const int base_size)
{
	if (base_size < HT_INITIAL_BASE_SIZE) // don't resize smaller than minimum
		return;
	ht_hash_table* new_ht = ht_new_sized(base_size); // generate new hash table
	for (int i = 0; i < ht->size; i++) // insert items (omit deleted items to make the hash chain faster)
	{
		ht_item* item = ht->items[i];
		if (item && item != &HT_DELETED_ITEM)
			ht_insert(new_ht, item->key, item->value);
	}

	ht->base_size = new_ht->base_size;
	ht->count = new_ht->count;
	
	// swap attributes instead of copying so we don't delete our new hash table
	// swap sizes
	const int tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;

	// swap item pointer arrays
	ht_item** tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;

	ht_del_hash_table(new_ht);
}

static void ht_resize_up(ht_hash_table* ht)
{
	const int new_size = ht->base_size * 2;
	ht_resize(ht, new_size);
}

static void ht_resize_down(ht_hash_table* ht)
{
	const int new_size = ht->base_size / 2;
	ht_resize(ht, new_size);
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value)
{
	const int load = ht->count * 100 / ht->size;
	if (load > 70)
		ht_resize_up(ht);
	ht_item* item = ht_new_item(key, value); // initialize k/v pair
	int index = ht_get_hash(item->key, ht->size, 0); // hash the key to get our first index to try
	ht_item* cur_item = ht->items[index]; // NULL if no collisison
	int i = 1;
	while (cur_item) // collision
	{
		if (cur_item != &HT_DELETED_ITEM) // item exists at index
		{
			if (strcmp(cur_item->key, key) == 0) // key matches; perform update
			{
				ht_del_item(cur_item); // delete old item
				ht->items[index] = item; // insert new item
				return;
			}
		}
		index = ht_get_hash(item->key, ht->size, i++); // double hash and try again
		cur_item = ht->items[index];
	}
	ht->items[index] = item; // insert
	ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key)
{
	int index = ht_get_hash(key, ht->size, 0); // get index
	ht_item* item = ht->items[index]; // get item
	int i = 1;
	while (item) // found
	{
		if (item != &HT_DELETED_ITEM) // not deleted
		{
			if (strcmp(item->key, key) == 0)
				return item->value;
		}
		index = ht_get_hash(key, ht->size, i++); // double hash and try again
		item = ht->items[index];
	}
	return NULL; // not found
}


void ht_delete(ht_hash_table* ht, const char* key)
{
	const int load = ht->count * 100 / ht->size;
	if (load < 10)
		ht_resize_down(ht);
	int index = ht_get_hash(key, ht->size, 0); // get index
	ht_item* item = ht->items[index]; // get item
	int i = 1;
	while (item) // found
	{
		if (item != &HT_DELETED_ITEM) // really found
		{
			if (strcmp(item->key, key) == 0) // key matches
			{
				ht_del_item(item); // delete item
				ht->items[index] = &HT_DELETED_ITEM; // mark index as deleted to preserve chain
			}
		}
		index = ht_get_hash(key, ht->size, i++); // not really found; double hash and try again
		item = ht->items[index];
	}
	ht->count--;
}
