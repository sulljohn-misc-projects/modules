/*
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>
#include "hash.h"

struct hashtable {
    queue_t **table;
    uint32_t size;
};

/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */
#define get16bits(d) (*((const uint16_t *) (d)))

static uint32_t SuperFastHash(const char *data, int len, uint32_t tablesize) {
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || data == NULL)
        return 0;
    rem = len & 3;
    len >>= 2;
    /* Main loop */
    for (; len > 0; len--) {
        hash += get16bits (data);
        tmp = (get16bits (data + 2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        data += 2 * sizeof(uint16_t);
        hash += hash >> 11;
    }
    /* Handle end cases */
    switch (rem) {
        case 3:
            hash += get16bits (data);
            hash ^= hash << 16;
            hash ^= data[sizeof(uint16_t)] << 18;
            hash += hash >> 11;
            break;
        case 2:
            hash += get16bits (data);
            hash ^= hash << 11;
            hash += hash >> 17;
            break;
        case 1:
            hash += *data;
            hash ^= hash << 10;
            hash += hash >> 1;
    }
    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;
    return hash % tablesize;
}

/* hopen -- opens a hash table with initial size hsize */
hashtable_t *hopen(uint32_t hsize) {
    struct hashtable *ht;

    // Allocating memory for the size that was given
    if (!(ht = (struct hashtable*)malloc(sizeof(struct hashtable)))) {
        printf("[Error: malloc failed allocating car]\n");
        return NULL;
    }

    // Allocating memory for the size that was given
    if (!(ht->table = malloc(sizeof(void*)*hsize))) {
        printf("[Error: malloc failed allocating car]\n");
        return NULL;
    }

    ht->size = hsize;

    queue_t **curr = ht->table;

    for (int i = 0; i < hsize; i++) {
        curr[i] = qopen();
    }

    return ht;
}

/* hclose -- closes a hash table */
void hclose(hashtable_t *htp) {
    struct hashtable *ht = (struct hashtable*)htp;

    queue_t **curr = ht->table;

    // Close up all the queues
    for (int i = 0; i < ht->size; i++) {
        qclose(*curr);
        curr++; // Incrementing the pointer
    }

    // Close up internal table
    free(ht->table);

    // Close up hashtable
    free(ht);
}

/* hput -- puts an entry into a hash table under designated key
 * returns 0 for success; non-zero otherwise
 *
 * ep seems to be elementp
 */
int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen) {
    struct hashtable *ht = (struct hashtable*)htp;

    queue_t** table = ht->table;

    // Getting what index of the table to put it in
    uint32_t ind = SuperFastHash(key, keylen, ht->size);

    // Adding it to the corresponding queue
    qput(table[ind], ep);

    return 0; // TODO: How to make this return something else?
}

/* happly -- applies a function to every entry in hash table */
void happly(hashtable_t *htp, void (*fn)(void *ep)) {
    struct hashtable *ht = (struct hashtable*)htp;

    queue_t **curr = ht->table;

    for (int i = 0; i < ht->size; i++) {
        queue_t *q = curr[i];

        qapply(q, fn);
    }
}

/* hsearch -- searches for an entry under a designated key using a
 * designated search fn -- returns a pointer to the entry or NULL if
 * not found
 */
void *hsearch(hashtable_t *htp,
              bool (*searchfn)(void *elementp, const void *searchkeyp),
              const char *key,
              int32_t keylen) {

    struct hashtable *ht = (struct hashtable*)htp;

    queue_t** table = ht->table;

    // Getting what index of the table to put it in
    uint32_t ind = SuperFastHash(key, keylen, ht->size);

    // Using qsearch to search in the appropriate queue
    return qsearch(table[ind], searchfn, key);
}

/* hremove -- removes and returns an entry under a designated key
 * using a designated search fn -- returns a pointer to the entry or
 * NULL if not found
 */
void *hremove(hashtable_t *htp,
              bool (*searchfn)(void *elementp, const void *searchkeyp),
              const char *key,
              int32_t keylen) {

    struct hashtable *ht = (struct hashtable*)htp;

    queue_t** table = ht->table;

    // Getting what index of the table to put it in
    uint32_t ind = SuperFastHash(key, keylen, ht->size);

    // Using qsearch to search in the appropriate queue
    return qremove(table[ind], searchfn, key);
}
