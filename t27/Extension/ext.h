#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ALPHA 27

struct dict {
   struct dict* dwn[ALPHA];
   struct dict* up;
   bool terminal;
   int freq;
};
typedef struct dict dict;


struct HashEntry {
    char* word;
    int freq;
    struct HashEntry* next;
}; 
typedef struct HashEntry HashEntry;


struct HashTable {
    HashEntry** table;
};
typedef struct HashTable HashTable;



dict* dict_init(void);

bool dict_addword(dict* p, const char* wd);

int dict_wordcount(const dict* p);

dict* dict_spell(const dict* p, const char* str);

void dict_free(dict** p);

int dict_mostcommon(const dict* p);

void test(void);
