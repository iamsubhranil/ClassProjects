#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static long hasErrors = 0; // Error marker

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
    return (Token){type, &source[start], pointer-start};
}

static Token identifer(){
    while(isalnum(source[pointer]))
        pointer++;
    return makeToken(TOKEN_IDENTIFIER);
}

static Token constant(){
    int decimal = 0;
    while(isdigit(source[pointer]) && decimal < 2){
        if(source[pointer] == '.')
            decimal++;
        pointer++;
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
            printf("\n[Error] Unrecognized character : '%c'!", source[start]);
            hasErrors++;
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

static void printToken(Token t){
    for(size_t i = 0;i < t.length;i++)
        printf("%c", t.strStart[i]);
    printf(" ");
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
        printf("\n[Error] Unexpected end of input!");
        hasErrors++;
    }
    else{
        printf("\n[Error] Unexpected token : ");
        printToken(list.tokens[listPointer]); 
        hasErrors++;
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
        Token item = orig.tokens[pointer];
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
    return ret;
}

int main(){
    char *line = NULL;
    size_t size = 0;
    printf("\nEnter an expression : ");
    if(getline(&line, &size, stdin) == 1){
        printf("\n[Error]Empty string provided!\n");
        return 1;
    }
    TokenList t = scanTokens(line), c;
    if(hasErrors){
        printf("\n[Error] Scanning completed with %ld errors!", hasErrors);
        printf("\n[Error] Unable to convert to postfix!");
        goto release;
    }
    parse(t);
    if(hasErrors){
        printf("\n[Error] Parsing completed with %ld errors!", hasErrors);
        printf("\n[Error] Unable to convert to postfix!");
        goto release;
    }
    c = toPostfix(t);
    printf("\nConverted expression : ");
    printList(c);
    freeList(c);
release:
    freeList(t);
    printf("\n");
}
