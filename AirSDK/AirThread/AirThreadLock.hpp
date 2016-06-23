//
//  AirThreadLock.hpp
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#ifndef AirThreadLock_hpp
#define AirThreadLock_hpp

#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/semaphore.h>
#include <sys/types.h>

#include "../AirObject/AirObject.h"

namespace AirCpp {
    class AirThreadLock : public AirObject{
    protected:
        
        pthread_mutex_t mutex;
    public:
        int init(){
            return pthread_mutex_init(&mutex, NULL);
        }
        
        int lock(){
            return pthread_mutex_lock(&mutex);
        }
        
        int unlock(){
            return pthread_mutex_unlock(&mutex);
        }
        
        int try_lock(){
            return pthread_mutex_trylock(&mutex);
        }
        
        int try_destroy(){
            return pthread_mutex_destroy(&mutex);
        }
    };
    
    
    class AirThreadSemaphore : public AirObject{
    protected:
        sem_t thread_sem;
    public:
        int init(bool shared){
            this->destroy();
            return sem_init(&thread_sem, shared, 0);
        }
        
        int wait(){
            return sem_wait(&thread_sem);
        }
        
        int post(){
            return sem_post(&thread_sem);
        }
        
        int destroy(){
            return sem_destroy(&thread_sem);
        }
        
        ~AirThreadSemaphore(){
            this->destroy();
        }
    };
    
    
    class AirThreadRWLock : public AirObject{
    protected:
        pthread_rwlock_t rwlock;
    public:
        int init(){
            return pthread_rwlock_init(&rwlock, NULL);
        }
        
        int rdlock(){
            return pthread_rwlock_rdlock(&rwlock);
        }
        
        int wrlock(){
            return pthread_rwlock_wrlock(&rwlock);
        }
        
        int try_rdlock(){
            return pthread_rwlock_tryrdlock(&rwlock);
        }
        
        int try_wrlock(){
            return pthread_rwlock_trywrlock(&rwlock);
        }
        
        int unlock(){
            return pthread_rwlock_unlock(&rwlock);
        }
        
        int destroy(){
            return pthread_rwlock_destroy(&rwlock);
        }
    };
}
#endif /* AirThreadLock_hpp */
