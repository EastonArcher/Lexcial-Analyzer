#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define KEY_READ 2
#define KEY_WRITE 3
#define KEY_WHILE 4
#define KEY_DO 5
#define KEY_OD 6
#define INT_LIT 7
#define IDENT 8

/* Operator codes*/
#define ASSIGN_OP 9
#define LESSER_OP 10
#define GREATER_OP 11
#define EQUAL_OP 12
#define NEQUAL_OP 13
#define LEQUAL_OP 14
#define GEQUAL_OP 15
#define SEMICOLON 16

/* Operator codes */
#define ADD_OP 17
#define SUB_OP 18
#define MULT_OP 19
#define DIV_OP 20
#define INC_OP 21
#define DEC_OP 22
#define LEFT_PAREN 23
#define RIGHT_PAREN 24

int lex();

#endif
