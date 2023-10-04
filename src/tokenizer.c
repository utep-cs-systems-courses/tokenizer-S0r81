#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

int space_char(char c) {
  return (c == ' ' || c == '\t');
}

int non_space_char(char c) {
  return (c != ' ' && c != '\t' && c != '\0');
}

char *token_start(char *str) {
  while(*str && space_char(*str)) str++;
  return *str ? str : NULL;
}

char *token_terminator(char *token) {
  while(*token && non_space_char(*token)) token++;
  return token;
}

int count_tokens(char *str) {
  int count = 0;
  while((str = token_start(str))) {
    str = token_terminator(str);
    count++;
  }
  return count;
}

char *copy_str(char *inStr, short len) {
  char *outStr = (char*)malloc(len + 1);
  strncpy(outStr, inStr, len);
  outStr[len] = '\0';
  return outStr;
}

char **tokenize(char* str) {
  int token_count = count_tokens(str);
  char **tokens = (char**)malloc((token_count + 1) * sizeof(char*));
  tokens[token_count] = NULL;
  
  for(int i = 0; i < token_count; i++) {
    str = token_start(str);
    char *end = token_terminator(str);
    tokens[i] = copy_str(str, end - str);
    str = end;
  }
  
  return tokens;
}

void print_tokens(char **tokens) {
  while(*tokens) {
    printf("%s\n", *tokens);
    tokens++;
  }
}

void free_tokens(char **tokens) {
  char **temp = tokens;
  while(*temp) {
    free(*temp);
    temp++;
  }
  free(tokens);
}

int main() {
  List *history = init_history();
  char input[100];
  
  while(1) {
    printf("Enter a string to tokenize (or '!' to view history, 'q' to quit): ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character
    
    if(input[0] == 'q') break;
    
    if(input[0] == '!') {
      print_history(history);
      continue;
    }
    
    add_history(history, input);
    char **tokens = tokenize(input);
    print_tokens(tokens);
    free_tokens(tokens);
  }
  
  free_history(history);
  return 0;
}
