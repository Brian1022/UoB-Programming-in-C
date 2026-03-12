#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ext.h"

#define MAXSTR 50
#define TABLE_SIZE 10007


char* wordToLower(const char* str);

unsigned hash_function(const char* word) {
    unsigned hash = 0;
    for (const char* c = word; *c; ++c) {
        hash = (hash * 31 + tolower(*c)) % TABLE_SIZE;
    }
    return hash;
}

dict* dict_init(void) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->table = (HashEntry**)calloc(TABLE_SIZE, sizeof(HashEntry*));
    if (!ht->table) {
        free(ht);
        return NULL;
    }
    return (dict*)ht;
}

bool dict_addword(dict* p, const char* wd) {
    if (!p || !wd) return false;
    HashTable* ht = (HashTable*)p;
    unsigned hash = hash_function(wd);

    HashEntry* current = ht->table[hash];
    char* lowerWord = wordToLower(wd);
    while (current) {
        if (strcmp(current->word, lowerWord) == 0) {
            current->freq++;
            return false;
        }
        current = current->next;
    }

    HashEntry* new_entry = (HashEntry*)malloc(sizeof(HashEntry));
    if (!new_entry) return false;

    new_entry->word = lowerWord;
    new_entry->freq = 1;
    new_entry->next = ht->table[hash];
    ht->table[hash] = new_entry;

    return true;

}

char* wordToLower(const char* str)
{
    char* tempWord = calloc(1 , strlen(str)+1);
    int i = 0;
    while(str[i] != '\0')
    {
       tempWord[i] = tolower(str[i]);
    }

    return tempWord;
}

void dict_free(dict** p) {
    if (!p || !*p) return;
    HashTable* ht = (HashTable*)(*p);

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashEntry* current = ht->table[i];
        while (current) {
            HashEntry* to_free = current;
            current = current->next;
            free(to_free->word);
            free(to_free);
        }
    }

    free(ht->table);
    free(ht);
    *p = NULL;
}

int dict_wordcount(const dict* p) {
    if (!p) return 0;
    const HashTable* ht = (const HashTable*)p;
    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        for (HashEntry* current = ht->table[i]; current; current = current->next) {
            count += current->freq;
        }
    }

    return count;
}

dict* dict_spell(const dict* p, const char* str) {
    if (!p || !str) return NULL;
    const HashTable* ht = (const HashTable*)p;
    unsigned hash = hash_function(str);

    for (HashEntry* current = ht->table[hash]; current; current = current->next) {
        if (strcmp(current->word, str) == 0) {
            return (dict*)current;
        }
    }

    return NULL;
}

int dict_mostcommon(const dict* p) {
    if (!p) return 0;
    const HashTable* ht = (const HashTable*)p;
    int max_freq = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        for (HashEntry* current = ht->table[i]; current; current = current->next) {
            if (current->freq > max_freq) {
                max_freq = current->freq;
            }
        }
    }

    return max_freq;
}

void test(void)
{
}
