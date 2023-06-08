/**
 * This the example lexical analyzer code in pages 173 - 177 of the
 * textbook,
 *
 * Sebesta, R. W. (2012). Concepts of Programming Languages. 
 * Pearson, 10th edition.
 *
 */

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "front.h"
#include "parser.h"
#include "parser.c"

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();
static int lookup(char ch);

/******************************************************/
/* main driver */
int main(int args, char **argv) 
{
    //Raider ID as outlined in the rubric
    printf("DCooke Analyzer :: R11678090");
    printf("\n\n");
    /* Open the input data file and process its contents */
    //argv used to open files from DCooke Analyzer correctly
    if ((in_fp = fopen(argv[1], "r")) == NULL) 
    {
        printf("ERROR - cannot open front.in \n");
    } else {
        getChar();
        do {
            lex();
            expr();
        } while (nextToken != EOF);
    }

    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * token */
static int lookup(char ch) {
    switch (ch) {
        //Searches for (, if found print the lexeme name and its symbol 
        case '(':
            //add character to our list
            addChar();
            printf("%s\tLEFT_PAREN\n", lexeme);
            //Assigning the lexeme to our defined token name 
            nextToken = LEFT_PAREN;
            //exit case statement
            break;
        //Searches for ), if found print the lexeme name and its symbol
        case ')':
            //add character to our list
            addChar();
            printf("%s\tRIGHT_PAREN\n", lexeme);
            //Assigning the lexeme to our defined token name
            nextToken = RIGHT_PAREN;
            //exit case statement
            break;
         //Searches for -, if found print the lexeme name and its symbol   
        case '-':
        //add the - character
        addChar();
        //get the next character
        getChar();
        //add the next char found from above to check for -- operator
        addChar();
            //if the char is a - then we continue down this if statement
            if(strcmp(lexeme, "-")==0){
                //A single - means a sub_operation, assign next token and print this out
                nextToken = SUB_OP;
                printf("%s\tSUB_OP\n", lexeme);
                //get the following character
                getChar();
                //if there are two - back to back (--), then we have a decrement operator
            } else if(strcmp(lexeme, "--") == 0){
                //assign decrement operator and print this out
                nextToken = DEC_OP;
                printf("%s\tDEC_OP\n", lexeme);
            } else { 
                    //if none of the above statements are satisifed, then we have a sub operation, assign this and print it
                    nextToken = SUB_OP;
                    printf("%s\tSUB_OP\n", lexeme);
                    addChar();
                
            }
            //exit case statement
            break;
        //searched for +, if found print the lexeme and its symbol
        case '+':
        //add the character
        addChar();
        //get the next character
        getChar();
        //add the next character found, to check for ++ operator
        addChar();
            //if the char is a + then we continue down this if statement
            if(strcmp(lexeme, "+")==0){
                //a single + means an add_operation, assign next token and print this out
                nextToken = ADD_OP;
                printf("%s\tADD_OP\n", lexeme);
                //get the following character
                getChar();
                //if there are two + back to back (++), then we have an increment operator
            } else if(strcmp(lexeme, "++") == 0){
                //assign increment operator and print this out
                nextToken = INC_OP;
                printf("%s\tINC_OP\n", lexeme);
            } else { 
                    //if none of the aboce statements are satisifed, then we have an add operation, assign this and print it
                    nextToken = ADD_OP;
                    printf("%s\tADD_OP\n", lexeme);
                    addChar();
            }
            //exit the case statement
            break;
        //Searches for *, if found print the lexeme name and its symbol
        case '*':
            //add the character to our list
            addChar();
            //Print the lexeme and its identifier, then assign the lexeme to our defined token name 
            printf("%s\tMULT_OP\n", lexeme);
            nextToken = MULT_OP;
            //exit the case statement
            break;
        //Searches for /, if found print the lexeme name and its symbol
        case '/':
            //add the character to our list
            addChar();
            //Print the lexeme and its identifier, then assign the lexeme to our defined token name
            printf("%s\tDIV_OP\n", lexeme);
            nextToken = DIV_OP;
            //exit the case statement
            break;
        //Searches for <, if found print the lexeme name and its symbol   
        case '<':
            //add the character to our list
            addChar();
            //get the next character, to check for <=, LEQUAL operation
            getChar();
            //if statement to check for equal sign
            if(nextChar =="="){
                //if found, add the = to our list
                addChar();
                //Print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tLEQUAL_OP\n", lexeme);
                nextToken = LEQUAL_OP;
                //get the next character
                getChar();
                //if there is no = sign, then we just have > sign, so assign lesser operation and print it out
            } else {
                printf("%s\tLESSER_OP\n", lexeme);
                nextToken = LESSER_OP;
            }
            //exit case statement
            break;
        //Searches for >, if found print the lexeme name and its symbol
        case '>':
            //add the character to our list
            addChar();
            //get the next character, to check for >=, GEQUAL operation
            getChar();
            //if statement to check for equal sign
            if(nextChar == "="){
                //if found, add the = to our list
                addChar();
                //Print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tGEQUAL_OP\n", lexeme);
                nextToken = GEQUAL_OP;
                //get the next character
                getChar();
            } else {
                //if there is no = sign, then we just have > sign, so assign lesser operation and print it out
                printf("%s\tGREATER_OP\n", lexeme);
                nextToken = GREATER_OP;
                }
            //exit case satatement
            break;
        //Searches for =, if found print the lexeme name and its symbol  
        case '=':
            //add the character to our list
            addChar();
            //Print the lexeme and its identifier, then assign the lexeme to our defined token name
            printf("%s\tEQUAL_OP\n", lexeme);
            nextToken = EQUAL_OP;
            //exit case statement
            break;
        //Searches for ;, if found print the lexeme name and its symbol
        case ';':
            //add the character to our list
            addChar();
            //Print the lexeme and its identifier, then assign the lexeme to our defined token name
            printf("%s\tSEMICOLON\n", lexeme);
            nextToken = SEMICOLON;
            //exit case statement
            break;
        //Searches for :, if found print the lexeme name and its symbol
        case ':':
            //add the character to our list
            addChar();
            //get the next character to check for :=, assign operator
            getChar();
            //if statement to check for equal sign 
            if(nextChar == '='){
                //if = is found, add the character to our list
                addChar();
                //Print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tASSIGN_OP\n", lexeme);
                nextToken = ASSIGN_OP;
            } else {
                //if there is no = sign, then we have an unknown symbol, 
                //print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tUNKNOWN\n", lexeme);
                nextToken = UNKNOWN;
            }
            //exit the case statement
            break;
        //Searches for !, if found print the lexeme name and its symbol
        case '!':
        //add the character to our list
        addChar();
        //get the next character, to check for != operation, NEQUAL
        getChar();
            //if statement to check if the nextChar is an = sign
            if(strcmp(&nextChar,"=")==0){
                //add the character to our list
                addChar();
                //Print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tNEQUAL_OP\n", lexeme);
                nextToken = NEQUAL_OP;
                getChar();
            } else { 
                //if there is no = sign, then we have an unknown symbol
                //print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tUNKNOWN\n", lexeme);
                nextToken = UNKNOWN;
            }
            //exit the case statement
            break;
        //Searches for &, if found print the lexeme name and its symbol
        case '&':
            //add the character to our list
            addChar();
            //print the lexeme and its identifier, then assign the lexeme to our defined token name
            printf("%s\tUNKNOWN\n", lexeme);
            nextToken = UNKNOWN;
            break;
            //exit the case statement
        //for if none of the following case statements are true
        default:
            //add the character to our list
            addChar();
            //get the next character
            getChar();
            //if all cases are false that means we are at the end of the file, nextToken = EOF;
            nextToken = EOF;
            //exit case statement
            break;
    }
    //return the nextTokens we found and assigned within the case statements
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {

    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        //if the case is a letter then continue down this path
        case LETTER:
            addChar();
            getChar();
            //while the character class is defined as a letter or a digit then we check for special operators
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();   
            }
            //if we encounter read, then we have a KEY_READ token
            if(strcmp(lexeme, "read") ==0 )
            {
                //print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tKEY_READ\n", lexeme);
                nextToken = KEY_READ;
            } 
            //if we encounter write, then we have a KEY_WRITE token
            else if (strcmp(lexeme, "write") == 0)
            {
                //print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tKEY_WRITE\n", lexeme);
                nextToken = KEY_WRITE;
            }
            //if we encounter while, then we have a KEY_WHILE token
            else if (strcmp(lexeme, "while") == 0)
            {
                //print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tKEY_WHILE\n", lexeme);
                nextToken = KEY_WHILE;
            } 
            //if we encounter do, then we have a KEY_DO token
            else if (strcmp(lexeme, "do") == 0)
            {
                //print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tKEY_DO\n", lexeme);
                nextToken = KEY_DO;
            } 
            //if we encounter od, then we have a KEY_OD token
            else if (strcmp(lexeme, "od") == 0)
            {
                //print the lexeme and its identifier, then assign the lexeme to our defined token name
                printf("%s\tKEY_OD\n", lexeme);
                nextToken = KEY_OD;
            //if none of these cases were encountered then we have an identifier, and no KEY tokens
            } else 
            {
                //print the lexeme and its identifier, then assign the lexeme to our defined token name
                nextToken = IDENT;
                printf("%s\tIDENT\n", lexeme);
            }
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            printf("%s\tINT_LIT\n", lexeme);
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
        //need to change lookup
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
    } /* End of switch */

    //printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
} /* End of function lex */

