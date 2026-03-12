#include "mydefs.h"


bool is_complete(board* b, state* s) {
  for (int col = 0; col < s->cols; col++) {
    if (b->complete[col] == false) {
      return false;
    }
  }
  return true;
}

bool file2str(const char* fname, char* str)
{

  if (!fname || !str) {
    return false;
  }

  FILE *fp = fopen(fname, "r");
  if (!fp) {
    return false;
  }


  char* temp = (char*) calloc(1, MAXSTR);
  char line[BRDSZ + 2];

  if (fscanf(fp, "%c", &temp[0]) != 1) {
    fclose(fp);
    return false;
  }

  while (fscanf(fp, "%s", line) == 1) {
    strcat(temp, "-");
    strcat(temp, line);
  }

  strcpy(str, temp);
  free(temp);
  fclose(fp);
  return true;

}

state* str2state(const char* str)
{

  if (!str) {
    return NULL;
  }

  state* s = (state*) calloc(1,sizeof(state));
  if (!s) {
    return NULL;
  }

  s->num_boards = 1;

  board* first_board = &s->boards[0];
  first_board->hawk = str[0];
  first_board->moves = 0;
  first_board->parent_idx = -1;


  int row = 0, col = 0;
  int max_row = 0, max_col = 0;

  for (const char* p = str + 2; *p; p++) {
    if (*p == '-') {
      max_row = row + 1;
      row++;
      col = 0;
    } else if (row < BRDSZ && col < BRDSZ) {
      first_board->tiles[row][col] = *p;
      col++;
      if (col > max_col) {
        max_col = col;
      }
    }
  }

  s->rows = max_row + 1;
  s->cols = max_col;

  for (int i = 0; i < max_col; i++) {
    first_board->complete[i] = false;
  }

  return s;

}

int solve(state* s, bool verbose)
{

  int f = 0;
  int r = 0;
  bool matched = false;

  while (f < s->num_boards) {
    board* current = &s->boards[f];

    for (int col = 0; col < s->cols; col++) {
      bool identical = true;
      int stop_1 = 0;
      for (int row = 1; row < s->rows && stop_1 == 0; row++) {
        if (current->tiles[row][col] != current->tiles[0][col]) {
          identical = false;
          stop_1 = 1;
        }
      }
      current->complete[col] = identical;
    }

    if (s->rows == 1) {
      matched = true;
    }

    if (matched) {
      board* sol = &s->boards[r];
      if (verbose) {
        int idx = r;
        int m = sol->moves;
        int i = m;
        int a[MAXBRDS];

        while (idx >= 0) {
          board* b = &s->boards[idx];
          
          a[i] = idx;
          i--;
          idx = b->parent_idx;
        }

        for (int i = 0; i <= m; i++) {
          board* b = &s->boards[a[i]]; 
          for (int k = 0; k < s->rows; k++) {
            for (int j = 0; j < s->cols; j++) {
              printf("%c", b->tiles[k][j]);
            }
            printf("\n");
          }
          printf("\n");
        }
      }

      return sol->moves;
    }

    int stop_4 = 0;
    for (int col = 0; col < s->cols && stop_4 == 0; col++) {
      if (current->complete[col]) {
        col++;
      }

      board new_board = *current;
      new_board.hawk = current->tiles[s->rows - 1][col];
      new_board.parent_idx = f;
      new_board.moves = current->moves + 1;
      new_board.complete[col] = current->complete[col];

      for (int row = s->rows - 1; row > 0; row--) {
        new_board.tiles[row][col] = new_board.tiles[row - 1][col];
      }
      new_board.tiles[0][col] = current->hawk;

      int stop_2 = 0;
      bool identical = true;
      for (int row = 1; row < s->rows && stop_2 == 0; row++) {
        if (new_board.tiles[row][col] != new_board.tiles[0][col]) {
          identical = false;
          stop_2 = 1;
        }
      }
      new_board.complete[col] = identical;

      bool duplicate = false;
      int stop_3 = 0;
      for (int i = 0; i < s->num_boards && stop_3 == 0; i++) {
        if (memcmp(&s->boards[i], &new_board, sizeof(board)) == 0) {
          duplicate = true;
          stop_3 = 1;
        }
      }

      if (!duplicate && s->num_boards < MAXBRDS) {
        r = s->num_boards;
        s->boards[s->num_boards++] = new_board;
      }

      if (is_complete(&new_board, s)) {
        matched = true;
        stop_4 = 1;
      }

    }

    f++;
  }

  return -1;

}

void test(void)
{
   char str[MAXSTR];
   state* s;

   strcpy(str, "A-ABC-ABC-ABC-CBA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false)==2);
   free(s);

   assert(file2str("0moves.brd", str));
   assert(strcmp("A-B", str)==0);
   s = str2state(str);
   assert(s);
   assert(solve(s, false)==0);
   free(s);

   assert(file2str("4moves.txt", str));
   assert(strcmp("O-COMS-COMS-COMS-CMMS-CSSO", str)==0);
   s = str2state(str);
   assert(s);
   assert(solve(s, false)==4);
   free(s);

}


