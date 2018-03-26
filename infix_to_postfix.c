#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>

// Display driver
// ==============

static long hasErrors = 0; // Error marker

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_FONT_BOLD     "\x1b[1m"

static void perr(const char* msg, ...){
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_RED "\n[Error] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg,args);
    hasErrors++;
}

static void pdbg(const char* msg, ...){
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_GREEN "\n[Debug] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg,args);
}

static void pinput(const char* msg, ...){
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_BLUE "\n[Input] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg,args);
}

static void poutput(const char* msg, ...){
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_YELLOW "\n[Output] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg,args);
}

// The Tokenizer
// =============

typedef enum{
    // Operands
    TOKEN_IDENTIFIER,
    TOKEN_CONSTANT,
    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_CAP,
    TOKEN_PERCEN,
    // Braces
    TOKEN_BRACE_OPEN,
    TOKEN_BRACE_CLOSE,
    // EOF marker
    TOKEN_END,
    TOKEN_UNKNOWN
} TokenType;

typedef struct{
    TokenType type;
    const char* strStart;
    size_t length;
} Token;

typedef struct{
    Token *tokens;
    char *source;
    int count;
} TokenList;

static char *source = NULL;
static size_t length = 0, pointer = 0, start = 0;

static Token makeToken(TokenType type){
#ifdef DEBUG
    pdbg("Making token : %d", type);
#endif
    return (Token){type, &source[start], pointer-start};
}

static Token identifer(){
    while(isalnum(source[pointer]))
        pointer++;
    return makeToken(TOKEN_IDENTIFIER);
}

#ifdef DEBUG

static const char* typeStrings[] = {
    "TOKEN_IDENTIFIER",
    "TOKEN_CONSTANT",
    "TOKEN_PLUS",
    "TOKEN_MINUS",
    "TOKEN_STAR",
    "TOKEN_SLASH",
    "TOKEN_CAP",
    "TOKEN_PERCEN",
    "TOKEN_BRACE_OPEN",
    "TOKEN_BRACE_CLOSE",
    "TOKEN_END",
    "TOKEN_UNKNOWN"
};

#endif

static void printToken(Token t){
    for(size_t i = 0;i < t.length;i++)
        printf("%c", t.strStart[i]);
#ifdef DEBUG
    printf("(%s)", typeStrings[t.type]);
#endif
    printf(" ");
}

static Token constant(){
    int decimal = 0;
    if(source[pointer] == '.' && !isdigit(source[pointer+1])){
            perr("Wrong usage of '.'!");
            pointer++;
            return makeToken(TOKEN_UNKNOWN); 
    }
    while((isdigit(source[pointer]) || source[pointer] == '.')){
        pointer++;
        if(source[pointer] == '.')
            decimal++;
    }
    if(decimal > 1 || (decimal==1 && source[pointer-1]=='.')){
        Token t = makeToken(TOKEN_UNKNOWN);
        perr("Bad constant : ");
        printToken(t);
        return t;
    }
    return makeToken(TOKEN_CONSTANT);
}

static Token nextToken(){
    start = pointer;
    if(pointer >= length)
        return makeToken(TOKEN_END);
    if(isalpha(source[pointer]))
        return identifer();
    if(isdigit(source[pointer]) || source[pointer] == '.')
        return constant();
    pointer++;
    switch(source[start]){
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            return nextToken();
        case '+':
            return makeToken(TOKEN_PLUS);
        case '-':
            return makeToken(TOKEN_MINUS);
        case '*':
            return makeToken(TOKEN_STAR);
        case '/':
            return makeToken(TOKEN_SLASH);
        case '^':
            return makeToken(TOKEN_CAP);
        case '%':
            return makeToken(TOKEN_PERCEN);
        case '{':
        case '(':
        case '[':
            return makeToken(TOKEN_BRACE_OPEN);
        case '}':
        case ')':
        case ']':
            return makeToken(TOKEN_BRACE_CLOSE);
        default:
            perr("Unrecognized character : '%c'!", source[start]);
            return makeToken(TOKEN_UNKNOWN);
    }
}

static void addToList(TokenList *list, Token t){
    list->count++;
    list->tokens = (Token *)realloc(list->tokens, sizeof(Token) * list->count);
    list->tokens[list->count - 1] = t;
}

static TokenList scanTokens(const char *s){
    source = strdup(s);
    length = strlen(s);
    pointer = 0;
    start = 0;

    TokenList list = {NULL, NULL, 0};
    list.source = source;
    while(1){
        Token t = nextToken();
        addToList(&list, t);
        if(t.type == TOKEN_END)
            break;
    }
    length = pointer = start = 0;
    return list;
}

static void printList(TokenList t){
    for(int i = 0;i < t.count;i++){
        printToken(t.tokens[i]);
    }
}

static void freeList(TokenList t){
    free(t.tokens);
    if(t.source != NULL)
        free(t.source);
}

// Parser (for validating the expression)
// ======================================

static TokenList list;
static int listPointer = 0;

static bool match(TokenType type){
    if(listPointer >= list.count ||  list.tokens[listPointer].type != type)
        return false;
    return true;
}

static Token advance(){
    if(list.tokens[listPointer].type == TOKEN_END)
        return list.tokens[listPointer];
    if(listPointer < list.count)
        listPointer++;
    if(listPointer < list.count)
        return list.tokens[listPointer];
    return list.tokens[listPointer - 1];
}

static void punexpected(){
    if(list.tokens[listPointer].type == TOKEN_END){
        perr("Unexpected end of input!");
    }
    else{
        perr("Unexpected token : ");
        printToken(list.tokens[listPointer]); 
    }
}

static Token consume(TokenType type){
    if(match(type))
        return advance();
    else{
        punexpected();
        return advance();
    }
}

static void prec0();

static void primary(){
    if(match(TOKEN_IDENTIFIER) || match(TOKEN_CONSTANT))
        advance();
    else if(match(TOKEN_BRACE_OPEN)){
        advance();
        prec0();
        consume(TOKEN_BRACE_CLOSE);
    }
    else{
        punexpected();
        advance();
    }
}

static void unary(){
    if(match(TOKEN_MINUS))
        advance();
    primary();
}

static void prec3(){
    unary();
    while(match(TOKEN_CAP)){
        advance();
        unary();
    }
}

static void prec2(){
    prec3();
    while(match(TOKEN_SLASH) || match(TOKEN_STAR)){
        advance();
        prec3();
    }
}

static void prec1(){
    prec2();
    while(match(TOKEN_PLUS) || match(TOKEN_MINUS)){
        advance();
        prec2();
    }
}

static void prec0(){
    prec1();
    while(match(TOKEN_PERCEN)){
        advance();
        prec1();
    }
}

static void parse(TokenList l){
    list = l;
    listPointer = 0;
    hasErrors = 0;

    while(!match(TOKEN_END))
        prec0();
}

// Postfix converter
// ================

typedef struct Stack{
    Token token;
    struct Stack* next;
} Stack;

static Stack* top = NULL;
static TokenList orig;

static void push(Token t){
    Stack *n = (Stack *)malloc(sizeof(Stack));
    n->token = t;
    n->next = top;
    top = n;
}

static Token pop(){
    Token t = top->token;
    Stack *temp = top;
    top = top->next;
    free(temp);
    return t;
}

static bool isoperator(Token t){
    return t.type == TOKEN_PLUS || t.type == TOKEN_MINUS || t.type == TOKEN_STAR
        || t.type == TOKEN_SLASH || t.type == TOKEN_CAP || t.type == TOKEN_PERCEN;
}

static int priority(Token t){
    switch(t.type){
        case TOKEN_BRACE_OPEN:
            return 4;
        case TOKEN_CAP:
            return 3;
        case TOKEN_STAR:
        case TOKEN_SLASH:
            return 2;
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            return 1;
        default:
            return 0;
    }
}

static TokenList toPostfix(TokenList orig){
    TokenList ret = {NULL, NULL, 0};
    push((Token){TOKEN_BRACE_OPEN, "(", 1});
    orig.tokens[orig.count - 1] = (Token){TOKEN_BRACE_CLOSE, ")", 1};
    int pointer = 0;

    while(top != NULL){
#ifdef DEBUG
        pdbg("Pointer at %d; Count %d", pointer, orig.count);
#endif
        Token item = orig.tokens[pointer];
#ifdef DEBUG
        pdbg("Present token : ");
        printToken(item);
#endif
        if(item.type == TOKEN_IDENTIFIER || item.type == TOKEN_CONSTANT){
            addToList(&ret, item);
        }
        else if(isoperator(item) || item.type == TOKEN_BRACE_OPEN){
            Token x = pop();
            if(isoperator(x)){
                if(priority(x) >= priority(item)){
                    addToList(&ret, x);
                    push(item);
                }
                else{
                    push(x);
                    push(item);
                }
            }
            else if(x.type == TOKEN_BRACE_OPEN){
                push(x);
                push(item);
            }
        }
        else if(item.type == TOKEN_BRACE_CLOSE){
            while((item = pop()).type != TOKEN_BRACE_OPEN){
                addToList(&ret, item);
            }
        }
        pointer++;
    }
#ifdef DEBUG
    pdbg("Conversion completed!\n");
#endif
    return ret;
}

int main(){
    char *line = NULL;
    size_t size = 0;
    pinput("Enter an expression : ");
    if(getline(&line, &size, stdin) == 1){
        perr("Empty input!\n");
        return 1;
    }
#ifdef DEBUG
    pdbg("Scanning..");
#endif
    TokenList t = scanTokens(line), c;
    if(hasErrors){
        perr("Scanning completed with %d errors!", hasErrors);
        perr("Unable to convert to postfix!");
        goto release;
    }
#ifdef DEBUG
    pdbg("Tokens : ");
    printList(t);
    pdbg("Parsing..");
#endif
    parse(t);
    if(hasErrors){
        perr("Parsing completed with %d errors!", hasErrors);
        perr("Unable to convert to postfix!");
        goto release;
    }
#ifdef DEBUG
    pdbg("Converting to postfix..");
#endif
    c = toPostfix(t);
    poutput("Converted expression : ");
    printList(c);
#ifdef DEBUG
    pdbg("Releasing memory..");
#endif
    freeList(c);
release:
    freeList(t);
#ifdef DEBUG
    pdbg("Execution completed!");
#endif
    printf("\n");
}
