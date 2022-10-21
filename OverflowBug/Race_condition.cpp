#include <iostream>
#include <pthread.h>
#include <string.h>

using namespace std;

int t;
pthread_mutex_t mt;

void* thread(void *) 
{
    for (int i = 0; i < 5000; ++i) 
    {
        t++;
    }
    return NULL;
}

void* thread2(void *) 
{
    pthread_mutex_lock(&mt);
    for (int i = 0; i < 5000; ++i) 
    {
        t++;
    }
    pthread_mutex_unlock(&mt);
    return NULL;
}

void asynchro() 
{
    t = 0;
    pthread_t pth1, pth2;

    pthread_create(&pth1, NULL, &thread, NULL);
    pthread_create(&pth2, NULL, &thread, NULL);

    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);

    cout << "t after run asynchronous : " << t << endl;

    // pthread_exit(NULL);
}

void synchro() 
{
    t = 0;
    pthread_t pth1, pth2;

    pthread_mutex_init(&mt, NULL);

    pthread_create(&pth1, NULL, &thread2, NULL);
    pthread_create(&pth2, NULL, &thread2, NULL);

    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);

    pthread_mutex_destroy(&mt);

    cout << "t after run synchronous : " << t << endl;

    // pthread_exit(NULL);
}

using namespace std;

int main()
{
    asynchro();

    synchro();

    pthread_exit(NULL);
    return 0;
}