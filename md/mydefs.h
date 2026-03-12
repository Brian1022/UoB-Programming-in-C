#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdbool.h>

#define BRDSZ 6
#define MAXBRDS 200000
#define MAXSTR (BRDSZ*BRDSZ+BRDSZ+2)


struct board {
    char tiles[BRDSZ][BRDSZ];
    char hawk;
    int parent_idx;
    int moves;
    bool complete[BRDSZ];
};
typedef struct board board;

struct state {
    board boards[MAXBRDS];
    int num_boards;
    int rows;
    int cols;
};
typedef struct state state;

#include "md.h"

