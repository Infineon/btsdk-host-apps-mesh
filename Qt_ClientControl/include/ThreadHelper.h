#pragma once
//#ifdef __linux__
#if defined(__linux__) || defined(__mac__)
#include <pthread.h>
#include <memory.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

#define WINAPI
#define INVALID_HANDLE_VALUE (-1)
#define FALSE   0
#define BOOL    bool
#define TRUE    true
typedef void *LPVOID;
typedef unsigned int DWORD;

#define Log(a)
class CAutoLock
{
public:
    CAutoLock(pthread_mutex_t* lock) :
        m_lock(lock)
    {
        pthread_mutex_lock(lock);
    }
    ~CAutoLock()
    {
        pthread_mutex_unlock(m_lock);
    }
private:
    pthread_mutex_t* m_lock;
};

class SyncObjectPosix
{
private:

    bool signalled;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

public:

    SyncObjectPosix()
    {
        signalled = false;
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&cond, NULL);
    }

    ~SyncObjectPosix()
    {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
    }

    bool WaitForSignal(unsigned long timeout)
    {
        struct timespec now;
        memset(&now, 0, sizeof(now));
        clock_gettime(CLOCK_REALTIME, &now);
        now.tv_nsec += (timeout % 1000) * 1000000;

        CAutoLock lock(&mutex);
        while (!signalled)
        {
            int ret = pthread_cond_timedwait(&cond, &mutex, &now);
            if (timeout != 0 && ret == ETIMEDOUT)
            {
                return false;
            }
        }
        signalled = false;
        return TRUE;
    }

    void Signal()
    {
        CAutoLock lock(&mutex);
        signalled = true;
        pthread_cond_signal(&cond);
    }
};
#endif

class ThreadHelper;

typedef struct _param {
    ThreadHelper* pThreadHelper;
    LPVOID pThreadparm;
} ThreadParm;


class ThreadHelper
{
public:
    ThreadHelper();
    virtual ~ThreadHelper();

    BOOL CreateThread(LPVOID threadparm);
    BOOL Close();
protected:
    virtual BOOL Begin();
    virtual BOOL Process();
    virtual BOOL CleanUp();
private:
    static ThreadParm s_ThreadParm;
    static LPVOID ThreadProc(LPVOID lpdwThreadParam);
    DWORD Worker(LPVOID pThreadparam);
    pthread_t m_hThread;
protected:
    SyncObjectPosix m_hShutdown;
    BOOL m_bClosing;
};
