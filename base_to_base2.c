#include <stdio.h>
#include <math.h>
#include <string.h>

// ===================================================
//                  Bookkeeping methods
// ===================================================

// Returns the decimal value of a character
int get_cval(char c, int ib){
    if(c >= '0' && c <= '9') // It is a numeric digit
        return c - '0';
    if(c >= 'a' && c <= 'a' + (ib - 11)) // It is something between a - f
        return c - 'a' + 10;
    if(c >= 'A' && c <= 'A' + (ib - 11)) // It is something between A - F
        return c - 'A' + 10;
    return -1; // It is impossible to have a digit like this in present base!
}

// ======================================================
//                  Conversion methods
// ======================================================

static short hasBadChar = 0; // Flag to denote if received string has an invalid character

// Convert a number in a base > 10 to base 10
long int con_gt10(char hex[20], long int ib){
    long int len, val, dec = 0, i = 0;
    len = strlen(hex) - 1;
    for(i=0; hex[i]!='\0'; i++){
        val = get_cval(hex[i], ib);
        if(val == -1){
            printf("\n[Error] Bad character %c for input base %ld!", hex[i], ib);
            hasBadChar = 1;
        }
        dec += val * pow(ib, len);
        len--;
    }
    return dec;
}

// Convert a number in a base < 10 to base 10
long int con_lt10(long int n, long int ib){
    long int b[20], i=0, s=0, p;
    while(n >= 1){
        b[i] = n%10;
        n = n/10;
        p = i;
        i++;
    }
    for (i=0; i<=p; i++){
        s += (b[i] * pow(ib,i));
    }
    return s;
}

// =====================================================
//                       Driver
// =====================================================

int main(){
    char ch = 'Y';
    do{
        long int n, a[20], ib, ob, i = 1, p, c;
        char hex[20]; // String to store if the input base is > 10

        printf("\n[Input] Enter the input base : ");
        scanf("%ld",&ib);
        if(ib < 2 || ib > 16){ // Hey man, behave yourself!
            printf("\n[Error] Input base must be fall in the range [2,16]!");
            return 1;
        }

        if (ib < 11){ // Thank god! The input is going to be pure decimal
            printf("\n[Input] Enter the number : ");
            scanf("%ld",&n);
        }
        else { // There is going to be some nasty chars in it
            printf("[Input] Enter the number : ");
            scanf("%s", hex);
        }

        printf("\n[Input] Enter the output base : ");
        scanf("%ld",&ob);

        if(ob < 2 || ob > 16){ // Whoops!
            printf("\n[Error] Output base must fall in the range [2,16]!");
        }

        if(ib != 10){ // We can't really convert a decimal to decimal, can we?
            if(ib < 10)
                c = con_lt10(n, ib);// A function to convert all < 10 bases to decimal
            else{
                c = con_gt10(hex, ib); // A function to convert all > 10 bases to decimal

                if(hasBadChar == 1) // Don't play dumb with me!
                    return 1;
            }
        }
        else
            c = n; 

        if(ob == 10){ // We have the converted decimal by now
            printf("\n[Output] Converted number : %ld",c);
        }
        else { // Converting to the output base, when will this day end?

            // You know this, right?
            while(c >= 1){
                a[i] = c%ob;
                c = c/ob;
                p = i;
                i++;
            }

            printf("\n[Output] Converted number : ");

            for (i=p;i>=1;i--){ // Let's desugar it
                if(a[i] > 9) // Duh! I can handle it too!
                    printf("%c", (char)(a[i] + 87));
                else
                    printf("%ld",a[i]);
            }

        }

        printf("\n[Input] Do you want to continue (y/n) ? ");
        scanf(" %c",&ch);

    } while(ch=='y' || ch=='Y'); // I can keep it up, can you?
    return 0;
}
