#include "crushit.h"
#include "mydefs.h"


bool initialise(state* s, const char* str)
{
  if(!s || !str){
    return false;
  }

  // Check if str is a filename
  FILE *fp;
  fp = fopen(str, "r");
  if(fp){
    for(int i = 0; i < MAXROWS; i++){
      for(int j = 0; j < WIDTH; j++){
        char c = fgetc(fp);
	if(c == '\n'){
	  c = fgetc(fp);
	}
        if(c == EOF){
        fclose(fp);
        return true;
        }
        s->board[i][j] = c;
      }
    }
    fclose(fp);
    return EXIT_SUCCESS;
  }

  // Check if row is complete
  int len = strlen(str);
  if(len % WIDTH != 0){
    return false;
  }

  int rows = len / WIDTH;
  if(rows > MAXROWS){
    return false;
  }

  // Check character is alphabet
  int position = 0;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < WIDTH; j++){
      char c = str[position++];
      if(c < 'A' || c > 'Z'){
        return false;
      }
      s->board[i][j] = c;
    }
  }

  return true;
}

bool tostring(const state* s, char* str){
  if(!s || !str){
    return false;
  }

  int index = 0;
  bool NonEmptyRowFound = false;

  for(int i = 0; i < MAXROWS; i++){
    bool EmptyRow = true;
    for(int j = 0; j < WIDTH; j++){
      if(s->board[i][j] != '.'){
	EmptyRow = false;
      }
      str[index++] = s->board[i][j];
    }
    if(!NonEmptyRowFound){
      if(!EmptyRow){
	NonEmptyRowFound = true;
      }
      else{
	index = 0;
      }
    }
  }
  str[index] = '\0';
  return true;
}

bool matches(state* s)
{
  if(!s){
    return false;
  }

  bool Matched = false;
  int MatchMark[MAXROWS][WIDTH] = {0};

  // Check horizontal match
  for(int i = 0; i < MAXROWS; i++){
    for(int j = 0; j < WIDTH - 2; j++){
      if(s->board[i][j] != '.'){
        if(s->board[i][j] == s->board[i][j + 1]&&
	   s->board[i][j] == s->board[i][j + 2]){
	  MatchMark[i][j] = MatchMark[i][j + 1] = MatchMark[i][j + 2] = 1;
	  Matched = true;
	}
      }
    }
  }

  // Check vertical match
  for(int j = 0; j < WIDTH; j++){
    for(int i = 0; i < MAXROWS - 2; i++){
      if(s->board[i][j] != '.'){
	if(s->board[i][j] == s->board[i + 1][j] &&
	   s->board[i][j] == s->board[i + 2][j]){
	  MatchMark[i][j] = MatchMark[i + 1][j] = MatchMark[i + 2][j] = 1;
	  Matched = true;
	}
      }      
    }
  }

  // Remove matched
  for(int i = 0; i< MAXROWS; i++){
    for(int j = 0; j < WIDTH; j++){
      if(MatchMark[i][j] == 1){
	s->board[i][j] = '.';
      }
    }
  }

  return Matched;
}

bool dropblocks(state* s)
{
  if(!s){
    return false;
  }

  for(int j = 0; j < WIDTH; j++){
  int RowEmpty = MAXROWS - 1;
    for(int i = MAXROWS - 1; i >= 0; i--){
      if(s->board[i][j] != '.'){
	// Move down the character to lowest empty row
	s->board[RowEmpty][j] = s->board[i][j];
	// After the character moving down set the original position as dot
	if(i != RowEmpty){
	  s->board[i][j] = '.';
	}
	// Make the position that point to lowest empty row to above row
	RowEmpty--;
	
	/*
        char temp = s->board[i - 1][j];
        s->board[i][j] = temp;
        s->board[i - 1][j] = '.';
        */
      }
    }
  }

  return true;
}

void test(void)
{
  state s;
  char output[WIDTH * MAXROWS + 1];

  initialise(&s, "BBBDBCDAACDAABDAABCAABCDABCAAA");
  tostring(&s, output);
  printf("Before: %s\n", output);
  matches(&s);
  tostring(&s, output);
  printf("After: %s\n", output);/*
  dropblocks(&s);
  tostring(&s, output);
  printf("Result: %s\n", output);*/
}
