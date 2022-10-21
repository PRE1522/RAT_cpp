#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define SE 1000000

using namespace std;

void* my_thread1(void* arg) 
{
    int time = 0.2*SE;
    while(1) 
    {
        cout << "A \n";
        usleep(time);
    }
    
    return NULL;
}

void* my_thread2(void* arg) 
{
    int time = 0.5*SE;
    while(1) 
    {
        cout << "B \n";
        usleep(time);
    }
    
    return NULL;
}

void* my_thread3(void* arg) 
{
    int time = 1*SE;
    while(1) 
    {
        cout << "C \n" ;
        usleep(time);
    }
    
    return NULL;
}


int main() 
{   
    pthread_t pth1;
    pthread_t pth2;
    pthread_t pth3;

    pthread_create(&pth1, NULL, &my_thread1, NULL);
    pthread_create(&pth2, NULL, &my_thread2, NULL);
    pthread_create(&pth3, NULL, &my_thread3, NULL);

    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);
    pthread_join(pth3, NULL);

    pthread_exit(NULL);

    return 0;
}