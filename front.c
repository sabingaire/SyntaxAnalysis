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
