#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_hash.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastName[], entry **e)
{
    // choose which hashtable to find
    unsigned int hashTarget = djb2Hash(lastName);
    entry *probe = NULL;

    if (hashTable[hashTarget] == NULL) {
        return NULL;
    } else {
        probe = hashTable[hashTarget];
    }

    while ( probe != NULL ) {
        if (strcasecmp(lastName, probe->lastName) == 0)
            return probe;
        probe = probe->pNext;
    }

    return NULL;
}

entry *append(char lastName[], entry *e)
{
    // save the new entry first
    entry *newEntry = (entry *) malloc(sizeof(entry));
    strcpy(newEntry->lastName, lastName);

    // calculate the hash value
    unsigned int hashIndex = djb2Hash(lastName);

    // check whether the hashTable is empty, create or lineup
    if(hashTable[hashIndex] == NULL) {
        hashTable[hashIndex] = newEntry;
        hashTable[hashIndex]->pNext = NULL;
    } else {
        // adding newEntry at head has less cache-miss
        newEntry->pNext = hashTable[hashIndex];
        hashTable[hashIndex] = newEntry;
        // adding newEntry at tail has more cache-miss
        /*
        newEntry->pNext = NULL;
        hashTable[hashIndex]->pNext = newEntry;
        */
    }
    return newEntry;
}

unsigned int djb2Hash(char lastName[])
{
    unsigned int hashValue = 0;
    int c;
    while((c = *lastName++))
        hashValue = ((hashValue << 5) + hashValue) + c;
    return hashValue % 42737;
}
