#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <ncurses.h>

#include "integrate.h"
#include "trie.h"
#include "helper.h"

#define set(X) attron(COLOR_PAIR(X))
#define reset(X) attroff(COLOR_PAIR(X))

#define SELECTED    1
#define BACKGROUND  2

#define GREENT      3
#define REDT        4
#define YELLOWT     5
#define MAGENTAT    6

#define INPUT_LEN   1000

inline char lower(char s) {
    return range(s, 'A', 'Z') ? s + 20 : s;
}

void print_header(int tab) {
    char tabs[10][1024] = {"[ CALCULATOR ]", "[ SAVED FUNCTIONS ]", "[ CONSTANTS ]"};
    for (int i = 0; i < 3; i++) {
        if (i == tab) {
            set(SELECTED);
        }
        printw("%s", tabs[i]);
        if (i == tab) {
            reset(SELECTED);
        }
        printw(" ");
    }
    printw("\n");
}

void print_str(char *str, Trie keywords) {
    bool is_var = false;
    bool is_num = false;
    
    int y, x;
    getyx(stdscr, y, x);

    uint32_t start = 0, index = 0;
    
    while (str[index] != '\0') {
        addch(str[index]);
        if (!(is_var || is_num) && is_number(str[index])) {
            is_num = true;
            start = index;
        }
        if (!(is_var || is_num) && is_letter(str[index])) {
            is_var = true;
            start = index;
        }

        if (is_num && !is_number(str[index + 1])) {
            is_num = false;
        }

        if (is_var && !is_alphanum(str[index + 1])) {
            if (keywords != NULL && trie_query(keywords, str + start, index - start + 1)) {
                set(REDT);
            } 
            else {
                set(GREENT);
            }
            int tx;
            getyx(stdscr, y, tx);

            move(y, start);
            for (int i = start; i <= index; i++) {
                addch(str[i]);
            }
            move(y, tx);

            is_var = false;
            reset(REDT);
            reset(GREENT);
        }
        if ((!is_var || !is_num) && is_operator(str[index])) {
            int tx;
            getyx(stdscr, y, tx);
            move(y, index);
            set(YELLOWT);
            addch(str[index]);
            reset(YELLOWT);
            move(y, tx);
        }
        if ((!is_var || !is_num) && is_bracket(str[index])) {
            int tx;
            getyx(stdscr, y, tx);
            move(y, index);
            set(MAGENTAT);
            addch(str[index]);
            reset(MAGENTAT);
            move(y, tx);
       
        }

        index++;
    }
}

void get_input(Trie keywords) {
    int ch; 
    
    char output[INPUT_LEN] = {0};
    int index = 0;
    int cursor = 0;
    int line = 1;
    while ((ch = getch()) != EOF) {
        if (ch == KEY_BACKSPACE) {
            if (index == 0) {
                continue;
            }
            output[index--] = '\0';
            cursor--;
        }
        else if (ch == '\n') {
            line++;
            index = 0;
            cursor = 0;
            for (int i = 0; i < INPUT_LEN; i++) {
                output[i] = 0;
            }
        }
        else {
            output[index++] = ch;
        }
        output[index] = '\0';
        move(line, 0);
        clrtoeol();
        print_str(output, keywords);
    }

    return;
}

Trie init_keywords(void) {
    Trie keywords = trie_create();
    trie_add(keywords, "cos"); 
    trie_add(keywords, "abs");
    trie_add(keywords, "sin");
    trie_add(keywords, "sqrt");
    trie_add(keywords, "cbrt");
    trie_add(keywords, "exp");
    trie_add(keywords, "tan");
    trie_add(keywords, "floor");

    return keywords;
}

int main(void) {
    initscr(); 
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    keypad(stdscr, TRUE);
    
    start_color();
    
    init_pair(SELECTED, COLOR_RED, COLOR_BLACK);
    init_pair(REDT, COLOR_RED, COLOR_BLACK);
    init_pair(GREENT, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOWT, COLOR_YELLOW, COLOR_BLACK);
    init_pair(MAGENTAT, COLOR_MAGENTA, COLOR_BLACK);
    
    Trie keywords = init_keywords();
    
    noecho();
    
    print_header(0);
    
    get_input(keywords);
    
    endwin();
}
