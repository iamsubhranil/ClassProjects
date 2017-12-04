#include <stdio.h>
#include <string.h>
#include <stdint.h>

char closing(char open){
    return open == '(' ? ')' : open == '[' ? ']' : '}'; 
}

char opening(char closing){
    return closing == ')' ? '(' : closing == '}' ? '{' : '[';
}

void error(size_t pos, char recieved, char expected){
    size_t i = 0;
    printf("[Error]");
    while(i < (pos + 16)){
        printf(" ");
        i++;
    }
    printf("^");
    printf("\n[Error] Bracket mismatch at character %zd : Expected '%c', Received '%c'!\n", (pos+1), 
                             expected, recieved );

}

int main(){
    char expr[100];
    printf("\nEnter the expression : ");
    fgets(expr, 98, stdin);
    size_t len = strlen(expr), i = 0;
    char stack[len];
    uint64_t sp = 0;
    while(i < len){
        switch(expr[i]){
            case '(':
            case '{':
            case '[':
                stack[sp++] = expr[i];
                break;
            case ')':
            case '}':
            case ']':
                if(sp == 0){
                    printf("[Error] Unexpected openning brace : '%c'\n", expr[i]);
                    return 1;
                }
                if(stack[sp - 1] != opening(expr[i])){
                    error(i, expr[i], closing(stack[sp - 1]));
                    return 1;
                }
                else
                    sp--;
        }
        i++;
    }
    if(sp == 0) 
        printf("The expression is valid in terms of paranthesis!\n");
    else
        printf("[Error] One or more unterminated paranthesis found!\n");
    return 0;
}
