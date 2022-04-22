#pragma once

#define range(X, LOWER, UPPER) (X >= LOWER && X <= UPPER)
#define is_number(X) range(X, '0', '9')
#define is_letter(X) (range(X, 'a', 'z') || range(X, 'A', 'Z'))
#define is_alphanum(X) (is_letter(X) || is_number(X))
#define is_operator(X) (X == '-' || X == '*' || X == '/' || X == '=' || X == '+' || X == '^')
#define is_bracket(X) (X == '(' || X == ')' || X == '{' || X == '}' || X == '[' || X == ']')
