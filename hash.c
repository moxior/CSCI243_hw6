/**
 * @file hash.c
 * @brief Integer-to-integer hash table using separate chaining.
 *
 * @author Andrew Herrera <ah2356@rit.edu>
 * @course CSCI-243 Homework 6
 */

#include "hash.h"

#include <stdlib.h>

#define NUM_BUCKETS 16

/**
 * A single key value entry stored in one linked list.
 * 
 */
typedef struct Entry {
    int key;
    int value;
    struct Entry *next;
} Entry;

/**
 * The private representation of  hash table.
 */
struct HashTable {
    Entry *buckets[NUM_BUCKETS];
    size_t size;
};

/**
 * Calculates the bucket index for an integer key.
 *
 *
 * @param key The integer key to hash.
 * @return The bucket index for the key.
 */
static size_t bucket_index(int key)
{
    return ((unsigned int) key) % NUM_BUCKETS;
}

/**
 * Creates a new empty hash table.
 *
 * @return A pointer to the new table, or null if it fails.
 */
HashTable *ht_create(void)
{
    HashTable *table;

    table = calloc(1, sizeof(HashTable));

    return table;
}

/**
 * Frees every entry in a hash table and then frees the table itself.
 *
 * 
 *
 * @param self The hash table to destroy.
 */
void ht_destroy(HashTable *self)
{
    size_t i;

    if (self == NULL) {
        return;
    }

    for (i = 0; i < NUM_BUCKETS; i++) {
        Entry *current = self->buckets[i];

        while (current != NULL) {
            Entry *next = current->next;

            free(current);
            current = next;
        }
    }

    free(self);
}

/**
 * Inserts or replaces a key value pair in the hash table.
 *
 * If the key already exists, its value is replaced without changing
 * the armt of entries.
 *
 * @param self The hash table.
 * @param key The key to insert or replace.
 * @param value The value associated with the key.
 */
void ht_put(HashTable *self, int key, int value)
{
    size_t index = bucket_index(key);
    Entry *current = self->buckets[index];
    Entry *entry;

    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }

        current = current->next;
    }

    entry = malloc(sizeof(Entry));

    if (entry == NULL) {
        return;
    }

    entry->key = key;
    entry->value = value;
    entry->next = self->buckets[index];

    self->buckets[index] = entry;
    self->size++;
}

/**
 * Looks up the value w key
 *
 * @param self The hash table.
 * @param key The key to look up.
 * @param found Pointer used to report whether the key was found.
 * @return The stored value when found, otherwise 0.
 */
int ht_get(const HashTable *self, int key, int *found)
{
    size_t index = bucket_index(key);
    const Entry *current = self->buckets[index];

    while (current != NULL) {
        if (current->key == key) {
            if (found != NULL) {
                *found = 1;
            }

            return current->value;
        }

        current = current->next;
    }

    if (found != NULL) {
        *found = 0;
    }

    return 0;
}

/**
 * Checks whether a key is present in the hash table.
 *
 * @param self The hash table.
 * @param key The key to search for.
 * @return 1 if  key exists, otherwise 0.
 */
int ht_contains(const HashTable *self, int key)
{
    size_t index = bucket_index(key);
    const Entry *current = self->buckets[index];

    while (current != NULL) {
        if (current->key == key) {
            return 1;
        }

        current = current->next;
    }

    return 0;
}

/**
 * Removes a key value pair from the hash table.
 *
 * @param self The hash table.
 * @param key The key to remove.
 * @return 1 if  key was removed, otherwise 0.
 */
int ht_remove(HashTable *self, int key)
{
    size_t index = bucket_index(key);
    Entry *current = self->buckets[index];
    Entry *previous = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (previous == NULL) {
                self->buckets[index] = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            self->size--;

            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

/**
 * Returns the number of key value pairs 
 *
 * @param self The hash table.
 * @return The number of pairs currently stored.
 */
size_t ht_size(const HashTable *self)
{
    return self->size;
}
