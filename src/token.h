#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "trie.h"

typedef enum {T_UNDEF, T_NUM, T_VAR, T_FUNC, T_OP, T_BRACE} token_type;

typedef struct TokenListObj* TokenList;

TokenList create_token_list(Trie keywords);

int token_list_length(TokenList TL);

void append_token(TokenList TL, char *literal, size_t n, token_type type);

void pop_token(TokenList TL);

void parse_token_list(TokenList TL, char *str);

void print_token_list(TokenList TL);
