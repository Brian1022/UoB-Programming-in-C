#include "t27.h"

#define MAXSTR 50

void find_most_frequent(const dict* node, char* buf, char* sto, int level, int* max_freq);


dict* dict_init(void)
{
    dict* new_dict = (dict*)malloc(sizeof(dict));
    if (!new_dict) {
        return NULL;
    }
    for (int i = 0; i < ALPHA; i++) {
        new_dict->dwn[i] = NULL;
    }
    new_dict->up = NULL;
    new_dict->terminal = false;
    new_dict->freq = 0;
    return new_dict;
}

bool dict_addword(dict* p, const char* wd)
{
    if (!p || !wd) {
        return false;
    }
    dict* current = p;

    for (const char* c = wd; *c; ++c) {
        int idx = (*c == '\'') ? 26 : tolower(*c) - 'a';
        if (idx < 0 || idx >= ALPHA) {
            return false;
        }
        if (!current->dwn[idx]) {
            current->dwn[idx] = dict_init();
            if (!current->dwn[idx]) {
                return false;
            }
            current->dwn[idx]->up = current;
        }
        current = current->dwn[idx];
    }

    if (current->terminal) {
        current->freq++;
        return false;
    }

    current->terminal = true;
    current->freq = 1;
    return true;
}

void dict_free(dict** p)
{
    if (!p || !*p) {
        return;
    }
    for (int i = 0; i < ALPHA; i++) {
        dict_free(&((*p)->dwn[i]));
    }
    free(*p);
    *p = NULL;
}

int dict_wordcount(const dict* p)
{
    if (!p) {
        return false;
    }
    int count = p->terminal ? p->freq : 0;
    for (int i = 0; i < ALPHA; i++) {
        count += dict_wordcount(p->dwn[i]);
    }
    return count;
}

int dict_nodecount(const dict* p)
{
    if (!p) {
        return false;
    }
    int count = 1;
    for (int i = 0; i < ALPHA; i++) {
        count += dict_nodecount(p->dwn[i]);
    }
    return count;
}

dict* dict_spell(const dict* p, const char* str)
{
    if (!p || !str) {
        return false;
    }
    const dict* current = p;

    for (const char* c = str; *c; ++c) {
        int idx = (*c == '\'') ? 26 : tolower(*c) - 'a';
        if (idx < 0 || idx >= ALPHA) {
            return NULL;
        }
        if (!current->dwn[idx]) {
            return NULL;
        }
        current = current->dwn[idx];
    }

    return current->terminal ? (dict*)current : NULL;
}

int dict_mostcommon(const dict* p)
{
    if (!p) {
        return false;
    }
    int max_freq = p->terminal ? p->freq : 0;
    for (int i = 0; i < ALPHA; i++) {
        int child_max = dict_mostcommon(p->dwn[i]);
        if (child_max > max_freq) {
            max_freq = child_max;
        }
    }
    return max_freq;
}

// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2) 
{
    if (!p1 || !p2) {
        return false;
    }
    unsigned steps = 0;
    dict* temp = p2;

    for (int j = 0; j < MAXSTR; j++) {
        for (int i = 0; i < MAXSTR; i++) {
            while (p1 == p2) {
                steps = i + j;
                return steps;
            }
            if (p2->up) {
                p2 = p2->up;
            }
        }
        p2 = temp;
        if (p1->up) {
            p1 = p1->up;
        }
    }
    return false;
}

void find_most_frequent(const dict* node, char* buf, char* sto, int level, int* max_freq) 
{
    if (!node) {
        return;
    }
    bool firsttime = (level == 0);

    if (!firsttime && node->terminal && node->freq > *max_freq) {
        *max_freq = node->freq;
        strcpy(sto, buf);
    }
    for (int i = 0; i < ALPHA; i++) {
        if (node->dwn[i]) {
            buf[level] = (i == 26) ? '\'' : 'a' + i;
            buf[level + 1] = '\0';
            find_most_frequent(node->dwn[i], buf, sto, level + 1, max_freq);
        }
    }
}

// CHALLENGE2
void dict_autocomplete(const dict* p, const char* wd, char* ret)
{
    if (!p || !wd || !ret) {
        return;
    }
    const dict* current = p;

    for (const char* c = wd; *c; ++c) {
        int idx = (*c == '\'') ? 26 : tolower(*c) - 'a';
        if (!current->dwn[idx]) {
            ret[0] = '\0';
            return;
        }
        current = current->dwn[idx];
    }

    char buffer[MAXSTR] = {0};
    char temp[MAXSTR] = {0};
    int max_freq = 0;

    find_most_frequent(current, buffer, temp, 0, &max_freq);
    strcpy(ret, temp);
}



void test(void)
{
    dict* root = dict_init();
    assert(root != NULL);

    const char* words[] = {"hello", "world", "help", "hell", "hero", "her"};
    for (int i = 0; i < 6; i++) {
        assert(dict_addword(root, words[i]) == true);
    }

    assert(dict_wordcount(root) == 6);
    assert(dict_nodecount(root) > 0);
    assert(dict_mostcommon(root) == 1);

    char result[MAXSTR] = {0};
    dict_autocomplete(root, "he", result);
    assert(strcmp(result, "ll") == 0);

    dict_autocomplete(root, "her", result);
    assert(strcmp(result, "o") == 0);

    char buffer[MAXSTR] = {0};
    char most_frequent[MAXSTR] = {0};
    int max_freq = 0;
    find_most_frequent(root, buffer, most_frequent, 0, &max_freq);
    assert(strcmp(most_frequent, "hell") == 0);

    dict* root2 = dict_init();
    dict_addword(root2, "hello");
    dict* p1 = dict_spell(root, "hello");
    dict* p2 = dict_spell(root2, "hello");
    assert(dict_cmp(p1, p2) == 0);

    dict_free(&root);
    dict_free(&root2);
    assert(root == NULL);
    assert(root2 == NULL);
}
