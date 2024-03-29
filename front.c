/* Syntax Programming Assignment
 Author: Sabin Gaire*/

/* front.c - a lexical analyzer system for simple
arithmetic expressions */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

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
void stmt();
void factor();
void expr();
void error();
int getErrorCharacter();
int is_empty();

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
bool error_called = false;

/* main driver */
int main(int argc,char* argv[]) {
/* Open the input data file and process its contents */
    if (argc != 2){
        printf("usage:\n./parser filename\n\n");
        exit(0);}
        else {
        /* Open the input data file and process its contents */
            if ((fp = fopen(argv[1], "r")) == NULL)
                printf("ERROR - cannot open %s\n", argv[1]);
            

    
    while ((read = getline(&line, &len, fp)) != -1 ) {
        
        lineNumber += 1;
        currentIndexCount = 0;
        
        getChar();
        do {
           
          lex();
          stmt();
            
        }
            while(nextToken != EOF && error_called==false);
        
         
            
    }
        
    
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

  case '=':
    addChar();
    nextToken = ASSIGN_OP;
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

int is_empty(char *s) {
  while (*s != '\0') {
    if (!isspace((unsigned char)*s))
      return 0;
    s++;
  }
    return 1;
}

/* addChar - a function to add nextChar to lexeme */
void addChar() {
  if (lexLen <= 98) {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  }
  else
    printf("Error - lexeme is too long \n");
}


/*****************************************************/
/* getChar - a function to get the next character of
input and determine its character class */
void getChar() {
  if (line[currentIndexCount] == '\n' || line[currentIndexCount] == '\0' || is_empty(&line[currentIndexCount]) ) {
    charClass = EOF;
  } else {
    nextChar = line[currentIndexCount];
    currentIndexCount += 1;
      if (isalpha(nextChar))
          charClass = LETTER;
  else if (isdigit(nextChar))
      charClass = DIGIT;
  else charClass = UNKNOWN;
  }
  
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank() {
  while (isspace(nextChar))
    getChar();
}

/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex() {
  lexLen = 0;
  getNonBlank();
  switch (charClass) {
  /* Parse identifiers */
    case LETTER:
      addChar();
      getChar();
      while (charClass == LETTER || charClass == DIGIT) {
        addChar();
        getChar();
      }
      nextToken = IDENT;
      break;
  /* Parse integer literals */
    case DIGIT:
      addChar();
      getChar();
      while (charClass == DIGIT) {
        addChar();
        getChar();
      }
      nextToken = INT_LIT;
      break;
          
/* Parentheses and operators */
  case UNKNOWN:
    lookup(nextChar);
    getChar();
    break;
  /* EOF */
  case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = 0;
    break;
  /* NEWLINE */
  case NEWLINE:
    nextToken = NEWLINE;
    lexeme[0] = 'N';
    lexeme[1] = 'E';
    lexeme[2] = 'W';
    lexeme[3] = 'L';
    lexeme[4] = 'I';
    lexeme[5] = 'E';
          break;
}
    /* End of switch */
printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
        return nextToken;
}
/* End of function lex */

/*stmt
Parses strings in the langugae generated by the rule:
 <stmt>->id =<expr>
 */

void stmt(){
    if( nextToken!= -1 ){
    printf("Enter <stmt>\n");


    if (nextToken == IDENT){
        lex();
        if(nextToken == ASSIGN_OP){
            lex();
            expr();
            
        }
        else{
            error();
        }
    }else{
            error();
        }
        if (error_called==false){
    
    printf("Exit <stmt>\n");
        }
    
    
}
}


/* expr
Parses strings in the language generated by the rule:
<expr> -> <term> {(+ | -) <term>}
*/
void expr() {
  printf("Enter <expr>\n");
 /* Parse the first term */
  term();
 /* As long as the next token is + or -, get
    the next token and parse the next term */
  while (nextToken == ADD_OP || nextToken == SUB_OP) {
    lex();
    term();
  }
    if (error_called==false){
  printf("Exit <expr>\n");
    }
}  



/* term
Parses strings in the language generated by the rule:
<term> -> <factor> {(* | /) <factor>)
*/

void term() {
  printf("Enter <term>\n");
/* Parse the first factor */
  factor();
/* As long as the next token is * or /, get the
   next token and parse the next factor */
  while (nextToken == MULT_OP || nextToken == DIV_OP) {
    lex();
    factor();
  }
    if (error_called==false){
        printf("Exit <term>\n");}
}  /* End of function term */


void factor() {
  printf("Enter <factor>\n");

  /* Determine which RHS */
  if (nextToken == IDENT || nextToken == INT_LIT)
  /* Get the next token */
  lex();
 /* If the RHS is ( <expr>), call lex to pass over the
    left parenthesis, call expr, and check for the right
    parenthesis */
  else {
      if (nextToken == LEFT_PAREN) {
        lex();
        expr();
        if (nextToken == RIGHT_PAREN)
          lex();
        else
          error();
        }  /* End of if (nextToken == ... */
   /* It was not an id, an integer literal, or a left
      parenthesis */
    else
      error();
     }  /* End of else */
    if (error_called==false){
    printf("Exit <factor>\n");
    }
  }  /* End of function factor */



void error() {
    printf("Error\n");
    error_called=true;
    ;
}

