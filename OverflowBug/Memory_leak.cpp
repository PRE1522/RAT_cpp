#include <iostream>

using namespace std;

void initz1() 
{
    int *m = new int;
    int *n = (int*) malloc(100*sizeof(int));
    int *p = (int*) calloc(100, sizeof(int));
}

void initz2() 
{
    int *m = new int;
    int *n = (int*) malloc(100*sizeof(int));
    int *p = (int*) calloc(100, sizeof(int));

    delete(m);
    delete(n);
    delete(p);
}

int main()
{
    while(1) 
    {
        //initz1();
        initz2();
    }
    return 0;
}