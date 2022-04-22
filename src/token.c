#include "error.h"
#include "token.h"
#include "helper.h"

typedef struct TokenObj* Token;

typedef struct TokenObj {
    char *literal; 
    token_type type;
    Token prev;
    Token next;
} TokenObj;

typedef struct TokenListObj* TokenList;

typedef struct TokenListObj {
    Trie keywords;
    uint32_t length;
    uint32_t index;
    Token first;
    Token last;
    Token cursor;

} TokenListObj;

Token create_token(char *literal, token_type type, size_t n) {
    Token T = malloc(sizeof(TokenObj));

    T->literal = strndup(literal, n);
    T->type = type;

    T->prev = NULL;
    T->next = NULL;
    T->cursor = NULL;
    return T; 
}

void delete_token(Token *pT) {
    if (pT != NULL && *pT != NULL) {
        free((*pT)->literal);
        free(*pT);
        *pT = NULL;
    }

    return;
}

TokenList create_token_list(Trie keywords) {
    TokenList TL = malloc(sizeof(TokenListObj));
    
    TL->length = 0;
    TL->keywords = keywords;
    
    TL->first = NULL;
    TL->last = NULL;

    return TL;
}

void delete_token_list(TokenList *pTL) {
    if (pTL != NULL && *pTL != NULL) {
        while ((*pTL)->length > 0) {
            pop_token(*pTL);
        }

        free(*pTL);
        *pTL = NULL;
    }
    return;
}

int token_list_length(TokenList TL) {
    error(TL == NULL, "Error: token_list_length() access NULL TL pointer");

    return TL->length;
}

void append_token(TokenList TL, char *literal, size_t n, token_type type) {
    if (n == 0) {
        return;
    }
    
    Token T = create_token(literal, type, n);
    
    if (TL->length == 0) {
        TL->first = T;
        TL->last = T;
    } 
    else {
        // new last prev is old last
        T1->prev = TL->last;
        // old last next is new last
        TL->last->next = T;
        // last pointer is new last
        TL->last = T;
    }

    TL->length++;
}

void pop_token(TokenList TL) {
    error(TL == NULL, "Error: pop_token() access NULL TL pointer");
    error(token_list_length(TL) == 0, "Error: pop_token() token list is empty\n");
    
    if (token_list_length(TL) > 1) {
        Token T = TL->last;
        TL->last = TL->last->prev;
        TL->last->next = NULL;
        delete_token(&T);
    }
    else {
        delete_token(&(TL->first));
        TL->last = NULL;
    }
    TL->length--;
    return;
}

void parse_token_list(TokenList TL, char *str) {
    if (str == NULL) {
        return;
    }

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
            append_token(TL, str + start, index - start + 1, TYPE_NUMBER);
            is_num = false;
        }
        if (is_var && !is_alphanum(str[index + 1])) {
            if (TL->keywords != NULL && trie_query(TL->keywords, str + start, index - start)) {
                append_token(TL, str + start, index - start + 1, TYPE_FUNCTION);
            }
            else {
                append_token(TL, str + start, index - start + 1, TYPE_VARIABLE);
            }

            is_var = false;
        }
        if ((!is_var || !is_num) && is_operator(str[index])) {
            append_token(TL, str + index, 1, TYPE_OPERATOR);
        }
        if ((!is_var || !is_num) && is_bracket(str[index])) {
            append_token(TL, str + index, 1, TYPE_BRACKET);
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


}
