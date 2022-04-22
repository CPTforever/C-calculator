#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

static inline void error(bool condition, char* message) {
    if (condition) {
        fprintf(stderr, "%s", message);
        exit(EXIT_FAILURE);
    }
}
