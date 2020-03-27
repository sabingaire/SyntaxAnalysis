/* Syntax Programming Assignment
 Author: Sabin Gaire*/

/* front.c - a lexical analyzer system for simple
arithmetic expressions */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* Global declarations */ /* Variables */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
int lineNumber = 0;
int currentIndexCount;
FILE *fp, *fopen();

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void term();
void factor();
void expr();
void error();
int getErrorCharacter();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define NEWLINE 101

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/* Global variables */
size_t len = 0;
ssize_t read;
char * line = NULL;

/* main driver */
int main(int argc, char *argv[]) {
/* Open the input data file and process its contents */
  fp = fopen("front.in", "r");
  if (fp == NULL) {
    fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__);
    exit(EXIT_FAILURE);
  }
    
while ((read = getline(&line, &len, fp)) != -1) {
    lineNumber += 1;
    currentIndexCount = 0;
    getChar();
    do {
      lex();
      expr();
    } while (nextToken != EOF);
    printf("\n\n");
  }
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch) {
  switch (ch) {
    case '(':
      addChar();
      nextToken = LEFT_PAREN;
      break;
          
          
  case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    break;

  case '+':
    addChar();
    nextToken = ADD_OP;
    break;

  case '-':
    addChar();
    nextToken = SUB_OP;
    break;

  case '*':
    addChar();
    nextToken = MULT_OP;
    break;
          
  case '/':
    addChar();
    nextToken = DIV_OP;
    break;

  case '\n':
    addChar();
    nextToken = NEWLINE;
    break;

  default:
    addChar();
    nextToken = EOF;
    break;
}
return nextToken;
}
