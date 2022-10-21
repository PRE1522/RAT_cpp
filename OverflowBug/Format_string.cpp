#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void display1() 
{   
    int k = 40;
    printf("%p\n", k);
    printf("%p\n", &k);

    char s[] = "%x%x%x%x";
    printf(s);
    printf("%p\n", s);
}

void display2() 
{   
    int k = 40;
    printf("%d\n", k);

    char s[] = "%x%x%x%x";
    printf("%s\n", s);
}

int main()
{
    display1();
    display2();

    return 0;
}