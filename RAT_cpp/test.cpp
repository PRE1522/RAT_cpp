#include <iostream>
#include <arpa/inet.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x = 12576;
    string y = to_string(x);
    // cout << y << endl;
    // int k = atoi(y.c_str());
    // cout << k << endl;
    // char* s = (char*)y.c_str();
    // cout << s << endl;
    // int u = atoi(s);
    // cout << u << endl;

    // x = htonl(x);
    // cout << x << " " << sizeof(x) <<  endl;

    // x = ntohl(x);
    // cout << x << " " << sizeof(x) <<  endl;
    y  = y + x;
    cout << y <<endl;
    return 0;
}