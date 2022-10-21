#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void cpy(const char* x) 
{   
    char y[10] = {0};
    strcpy(y, x);
    // strncpy(y,x,sizeof(y));
    printf("cpy:  %s\n", y);
}

void cpy2(const char* x) 
{   
    int k = strlen(x);
    char y[k];
    strcpy(y, x);
    printf("cpy2:  %s\n", y);
    //=======================
    char s[10] = {0};
    strncpy(s, x, sizeof(s));
    printf("(strncpy) : %s\n", s);
}

int main() 
{
    const char* s = "Nguyen Dinh Phat";
    // cpy(s);
    cpy2(s);
    return 0;
}