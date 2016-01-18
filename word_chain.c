#include <stdio.h>

char count;
char words[25][2];
char chaining[4];

char last(char* word) {
  char i = 0;
  for(;word[i] != '\0';++i);
  return word[i - 1];
}

char unique(char index) {
  int i = 0;
  for(;i<3;++i)
    if(index == chaining[i])
      return 0;
  return 1;
}

char next(char letter) {
  char i = 0;
  for(;i<count;++i)
    if((words[i][0] == letter) && unique(i))
      return i;
  return -1;
}

char final(char beggin, char end) {
  char i = 0;
  for(;i<count;++i)
    if(((words[i][0] == beggin) && (words[i][1] == end)) && unique(i))
      return i;
  return -1;
}

char try_chain(char pos) {
  char i = 1;
  char find = words[pos][1];
  chaining[0] = pos;
  for(;i<3;++i) {
    chaining[i] = next(find);
    if(chaining[i] >= 0)
        find = words[chaining[i]][1];
    else return 0;
  }
  chaining[3] = final(find, words[pos][0]);
  return (chaining[3] >= 0);
}

int main(int argc, char** argv) {
  char i = 1;
  char chained = 0;
  count = argc - 1;
  for(;i<argc;++i) {
    words[i - 1][0] = argv[i][0];
    words[i - 1][1] = last(argv[i]);
  }
  for(i=0;i<count;++i) {
    chained = try_chain(i);
    if(chained) break;
  }
  if(chained)
    printf("%s-%s-%s-%s\n", argv[chaining[0] + 1], argv[chaining[1] + 1], argv[chaining[2] + 1], argv[chaining[3] + 1]);
  else printf("no chain posible\n");

  return 0;
}
