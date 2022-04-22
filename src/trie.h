#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct TrieObj* Trie;   

Trie trie_create(); 

void trie_delete(Trie* pT); 

void trie_add(Trie root, char *str);

bool trie_query(Trie root, char *str, size_t n);
