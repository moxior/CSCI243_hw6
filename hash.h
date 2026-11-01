/**
 * @file hash.h
 * @brief Interface for an integer-to-integer hash table abstract data type.
 *
 * The HashTable maps int keys to int values. The type is opaque: clients use
 * only the operations declared here and never see the representation (which is
 * separate chaining with linked lists, defined in hash.c). Keys are unique; a
 * second put with an existing key replaces that key's value.
 *
 * @author Dr. Abeer Ahmad <abavcs@rit.edu>
 * @course CSCI-243 Homework 6 (Abstract Data Types)
 */
#ifndef HASH_H
#define HASH_H

#include <stddef.h>

/** Opaque hash-table type; clients never see the fields. */
typedef struct HashTable HashTable;

/**
 * Create a new, empty hash table.
 * @return the table, or NULL on allocation failure.
 */
HashTable *ht_create(void);

/**
 * Destroy a hash table, freeing every key/value entry it owns and the table
 * itself. Safe to call on NULL.
 * @param self the table to destroy (may be NULL)
 */
void ht_destroy(HashTable *self);

/**
 * Insert key with the given value, or replace the value if key is already
 * present.
 * @param self  the table
 * @param key   the key to insert or update
 * @param value the value to associate with key
 */
void ht_put(HashTable *self, int key, int value);

/**
 * Look up key and return its value.
 * @param self  the table
 * @param key   the key to look up
 * @param found out-parameter: set to 1 if key was present, 0 otherwise
 * @return the value associated with key, or 0 if key was not present
 */
int ht_get(const HashTable *self, int key, int *found);

/**
 * Test whether key is present.
 * @param self the table
 * @param key  the key to test
 * @return 1 if key is in the table, 0 otherwise
 */
int ht_contains(const HashTable *self, int key);

/**
 * Remove key (and its value) from the table.
 * @param self the table
 * @param key  the key to remove
 * @return 1 if key was present and removed, 0 if it was absent
 */
int ht_remove(HashTable *self, int key);

/**
 * Report how many key/value pairs the table holds.
 * @param self the table
 * @return the number of entries
 */
size_t ht_size(const HashTable *self);

#endif /* HASH_H */
