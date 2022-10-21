#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void get_char_by_index1(char x[], int len) 
{
    printf("%d\n", strlen(x));
    printf("Output 1: ");
    for (int i = 0; i < strlen(x); ++i) 
    {
        printf("%c", x[i]);
    }
    printf("\n");
}

void get_char_by_index2(char x[], int len) 
{
    printf("Output 2: ");
    for (int i = 0; i < len; ++i) 
    {
        printf("%c", x[i]);
    }
    printf("\n");
}

int main() 
{
    char x[17] = "Nguyen Dinh Phat";
    int n = strlen(x);
    x[n] = 'o';
    get_char_by_index1(x, n);
    get_char_by_index2(x, n);   
    return 0;
}