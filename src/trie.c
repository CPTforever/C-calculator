#include "trie.h"

#define TRIE_NODE_LENGTH 256

typedef struct TrieObj* Trie;

typedef struct TrieObj {
    Trie arr[TRIE_NODE_LENGTH];
    bool end;
} TrieObj;

Trie trie_create() {
    Trie t = malloc(sizeof(TrieObj));

    for (int i = 0; i < TRIE_NODE_LENGTH; i++) {
        t->arr[i] = NULL;
    }

    t->end = false; 
    return t;
}

void trie_delete(Trie *pT) {
    for (int i = 0; i < TRIE_NODE_LENGTH; i++) {
        if (pT != NULL && (*pT) != NULL && (*pT)->arr[i] != NULL) {
            trie_delete(&(*pT)->arr[i]);
        }
    }
    free(*pT);
    
    *pT = NULL;
    return;
}

void trie_add(Trie root, char *str) {
    int index = 0;
    Trie current = root;
    while (str[index] != '\0') {
        if (!current->arr[(uint8_t) str[index]]) {
            current->arr[(uint8_t) str[index]] = trie_create();
        }
        current = current->arr[(uint8_t) str[index]]; 
        index++;
    }

    current->end = true;
}

bool trie_query(Trie root, char *str, size_t n) {
    int index = 0;
    Trie current = root; 
    
    while(str[index] != '\0') {
        if (index == n) {
            break; 
        }
        if (current->arr[(uint8_t) str[index]]) {
            current = current->arr[(uint8_t) str[index]]; 
        }
        else {
            return false;
        }
        index++;
    }

    if (current->end) {
        return true;
    }
    else {
        return false;
    }
}

