#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int add(int a, int b) 
{
    int res = a+b;
    return res;
}

long long add2(int a, int b) 
{   
    long long res = (long long)a + b;
    return res;
}

int main() 
{
    int a = 1234;
    int b = INT32_MAX;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "Overflow: a + b = " << add(a,b) << endl;
    cout << "Fix: a + b = " << add2(a,b) << endl;
    // cout << INT32_MAX << endl;

    return 0;
}