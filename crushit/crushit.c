#include "crushit.h"
#include "mydefs.h"

int heightofrows(const char* str);


bool initialise(state* s, const char* str)
{
  if(!s || !str){
    return false;
  }


  for(int i = 0; i < MAXROWS; i++){
    for(int j = 0; j < WIDTH; j++){
      s->board[i][j] = '.';
    }
  }
  

  FILE *fp;
  fp = fopen(str, "r");
  if(fp){

    s->rowsnumber = heightofrows(str);

    for(int i = MAXROWS - s->rowsnumber; i < MAXROWS; i++){
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
    return true;
  }

  else{
    int len = strlen(str);
    if(len % WIDTH != 0){
      return false;
    }

    int rows = len / WIDTH;
    if(rows > MAXROWS){
      return false;
    }

    s->rowsnumber = rows;

    int position = 0;
    for(int i = MAXROWS - s->rowsnumber; i < MAXROWS; i++){
      for(int j = 0; j < WIDTH; j++){
        char c = str[position++];
        if(c < 'A' || c > 'Z'){
          return false;
        }
        s->board[i][j] = c;
      }
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

  for(int i = MAXROWS - HEIGHT; i < MAXROWS; i++){
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

  for(int j = 0; j < WIDTH; j++){
    for(int i = MAXROWS - HEIGHT; i < MAXROWS - 2; i++){
      if(s->board[i][j] != '.'){
	if(s->board[i][j] == s->board[i + 1][j] &&
	   s->board[i][j] == s->board[i + 2][j]){
	  MatchMark[i][j] = MatchMark[i + 1][j] = MatchMark[i + 2][j] = 1;
	  Matched = true;
	}
      }      
    }
  }

  for(int i = MAXROWS - HEIGHT; i < MAXROWS; i++){
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

	s->board[RowEmpty][j] = s->board[i][j];

	if(i != RowEmpty){
	  s->board[i][j] = '.';
	}

	RowEmpty--;
      }
    }
  }

  return true;
}

int heightofrows(const char* str)
{
  int count = 0;
  
  FILE *fp;
  fp = fopen(str, "r");
  for(int i = 0; i < MAXROWS; i++){
    for(int j = 0; j < WIDTH; j++){
      char c = fgetc(fp);
      if(c == '\n'){
        c = fgetc(fp);
      }
      if(c == EOF){
        fclose(fp);
        int height = count / WIDTH;
        return height;
      }
      count++;
    }
  }

  fclose(fp);
  return true;
}

void test(void)
{
  state s;
  char str[WIDTH * MAXROWS + 1];

  assert(heightofrows("b1.txt") == 6);
  assert(heightofrows("c.txt") == 8);

  assert(initialise(&s, "BBBDBCDAACDAABDAABCAABCDABCAAa") == false);
  assert(initialise(&s, "BBBDBCDAACDAABDAABCAABCDA") == true);
  assert(initialise(&s, "BBBDBCDAACDAABDAABCAABCDABCAA.") == false);

  assert(initialise(&s, "b1.txt") == true);
  assert(tostring(&s, str) == true);
  assert(matches(&s) == true);
  assert(tostring(&s, str) == true);
  assert(dropblocks(&s) == true);
  assert(tostring(&s, str) == true);

  assert(initialise(&s, "BBBDBCDAACDAABDAABCAABCDABCAAA") == true);
  assert(tostring(&s, str) == true);
  assert(matches(&s) == true);
  assert(tostring(&s, str) == true);
  assert(dropblocks(&s) == true);
  assert(tostring(&s, str) == true);

  assert(initialise(&s, "c.txt") == true);
  assert(tostring(&s, str) == true);
  assert(matches(&s) == true);
  assert(tostring(&s, str) == true);
  assert(dropblocks(&s) == true);
  assert(tostring(&s, str) == true);

  assert(initialise(&s, "lft.txt") == true);
  assert(tostring(&s, str) == true);
  assert(matches(&s) == true);
  assert(tostring(&s, str) == true);
  assert(dropblocks(&s) == true);
  assert(tostring(&s, str) == true);
}
