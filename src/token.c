#include "error.h"
#include "token.h"
#include "helper.h"

// This encapsulates the Token tree that will be the public struct for this file
typedef struct TokenObj* Token;

typedef struct TokenObj {
    char *literal; 
    token_type type;
    Token *children;
    int children_len;
    Token parent;
} TokenObj;

typedef struct TokenTreeObj* TokenTree;

typedef struct TokenTreeObj {
    Token root;
} TokenTreeObj;

Token create_token(char *literal, token_type type, size_t n) {
    Token T = malloc(sizeof(TokenObj));

    T->literal = strndup(literal, n);
    T->children = NULL;
    T->parent = NULL;
    T->children_len = 0;
    return T; 
}

// Recursively frees a token and it's children
void delete_token(Token *pT) {
    if (pT != NULL && *pT != NULL) {
        free((*pT)->literal);
        if (T->children != NULL) {
            for (int i = 0; i < T->children_len; i++) {
                delete_token(&(T->children[i]));
            }
        }
        free(*pT);
        *pT = NULL;
    }

    return;
}

TokenList create_token_list(char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    int stackSize = 100;
    Token *stack = calloc(sizeof(Token), stackSize);
    int top = 0;

    bool is_var = false;
    bool is_num = false;
    uint32_t index = 0;
    uint32_t start = 0;
    
    while (str[index] != '\0') {
        if (!(is_var || is_num) && is_number(str[index])) {
            is_num = true;
            start = index;
        }
        if (!(is_var || is_num) && is_letter(str[index])) {
            is_var = true;
            start = index; 
        }

        if (is_num && !is_number(str[index + 1])) {
            append_token(TL, str + start, index - start + 1, T_NUM);
            is_num = false;
        }
        if (is_var && !is_alphanum(str[index + 1])) {
            if (TL->keywords != NULL && trie_query(TL->keywords, str + start, index - start)) {
                append_token(TL, str + start, index - start + 1, T_FUNC);
            }
            else {
                append_token(TL, str + start, index - start + 1, T_VAR);
            }

            is_var = false;
        }
        if ((!is_var || !is_num) && is_operator(str[index])) {
            append_token(TL, str + index, 1, T_OP);
        }
        if ((!is_var || !is_num) && is_bracket(str[index])) {
            append_token(TL, str + index, 1, T_BRACE);
        }

        index++;
    }
}

void print_token_list(TokenList TL) {
    Token T = TL->first;
    while (T != NULL) {
        printf("%s\n", T->literal);
        T = T->next;
    }
}

int main(void) {
    TokenList TL = create_token_list(NULL);

    parse_token_list(TL, "4sin(x) + 4");

    print_token_list(TL);

    return 0;
}
