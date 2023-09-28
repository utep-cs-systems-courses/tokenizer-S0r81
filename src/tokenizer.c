#include<stdio.h>
#include<stdlib.h>
#include"tokenizer.h"


/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c){
    return (c == ' ' || c == '\t');
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c){
    return (c != ' ' && c != '\t');
}

/* Returns a pointer to the first character of the next 
   space-separated token in zero-terminated str.  Return a zero pointer if 
   str does not contain any tokens. */
char *token_start(char *str){
    while(space_char(*str)){
        str++;
    }
    if(*str == '\0'){
        return NULL;
    }
    return str;
}

/* Returns a pointer terminator char following *token */
char *token_terminator(char *token){
    while(non_space_char(*token)){
        token++;
    }
    return token;
}

/* Counts the number of tokens in the string argument. */
int count_tokens(char *str){
    int count = 0;
    char *token = token_start(str);
    while(token != NULL){
        count++;
        token = token_start(token_terminator(token));
    }
    return count;
}

/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len){
    char *outStr = malloc(len + 1);
    for(int i = 0; i < len; i++){
        outStr[i] = inStr[i];
    }
    outStr[len] = '\0';
    return outStr;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char* str){
    int numTokens = count_tokens(str);
    char **tokens = malloc((numTokens + 1) * sizeof(char *));
    char *token = token_start(str);
    for(int i = 0; i < numTokens; i++){
        char *term = token_terminator(token);
        int len = term - token;
        tokens[i] = copy_str(token, len);
        token = token_start(term);
    }
    tokens[numTokens] = 0;
    return tokens;
}

/* Prints all tokens. */
void print_tokens(char **tokens){
    int i = 0;
    while(tokens[i] != 0){
        printf("%s\n", tokens[i]);
        i++;
    }
}

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens){
    int i = 0;
    while(tokens[i] != 0){
        free(tokens[i]);
        i++;
    }
    free(tokens);
}



                
