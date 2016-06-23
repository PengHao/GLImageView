//
//  AirThread.cpp
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#include "AirThread.h"

#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <pthread/pthread.h>
#include <unistd.h>
#include <signal.h>
#include "../AirObject/AirObject.h"
#include "../AirContainer/AirArray.h"
#include "AirOperation.h"
#include <AirThread/AirThreadPool.hpp>

namespace AirCpp {
    
    void sighand(int signo){
        switch (signo) {
            case EXIT:
                pthread_exit(0);
                break;
                case HOLDON:
                
            default:
                break;
        }
    }
    
    void *AirThread::_run_loop(void *thread) {
        AirThread *_thread = (AirThread *)thread;
        _thread->run_roop();
        return nullptr;
    }
    
    AirThread::~AirThread() {
        release(operation_queue);
        pthread_kill(p_id, EXIT);
    }
    
    void AirThread::run_roop() {
        while (!_cancel) {
            AirOperation *oper = operation_queue->head_operation();
            if (oper) {
                oper->excute();
                operation_queue->remove_operation(oper);
            } else {
                //sleep
                pthread_cond_wait(&p_cond, &p_mutex);
            }
        }
    }
    
    void AirThread::push_operation(AirOperation *operation) {
        operation_queue->pushOperation(operation);
        pthread_cond_signal(&p_cond);
    }
    
    int AirThread::init(){
        struct sigaction        actions;
        memset(&actions, 0, sizeof(actions));
        sigemptyset(&actions.sa_mask); /* 将参数set信号集初始化并清空 */
        actions.sa_flags = 0;
        actions.sa_handler = sighand;
        sigaction(EXIT, &actions, nullptr);
        
        pthread_cond_init(&p_cond, NULL);
        pthread_mutex_init(&p_mutex, NULL);
        return pthread_create(&p_id, NULL, _run_loop, (void *)this);
    }
    
    void AirThread::cancel(){
        _cancel = true;
    }
    
    void AirThread::wait_until_done(void **ret){
        pthread_join(p_id, ret);
    }
    
    void AirThread::keep_going(){
        pthread_detach(p_id);
    }
    
    void AirThread::excute_async(AirThread *thread, std::function<void()> _func) {
        AirOperation* o = new AirOperation();
        o->init(_func);
        thread->push_operation(o);
    }
    
    void AirThread::excute_sync(AirThread *thread, std::function<void()> _func) {
        AirOperation* o = new AirOperation();
        o->init(_func);
        thread->push_operation(o);
        AirThread *c = current_thread();
        pthread_cond_wait(&c->p_cond, &c->p_mutex);
    }
    
    void AirThread::excute_apply(int concurrence_count, std::function<void(int)> _func) {
        
        
    }
    
    void AirThread::excute_after(AirThread *thread, std::function<void()> _func, float after_delay) {
        AirOperation* o = new AirOperation();
        o->init([after_delay]{
            sleep(after_delay);
        });
        thread->push_operation(o);
        release(o);
        o = new AirOperation();
        o->init(_func);
        thread->push_operation(o);
        release(o);
    }
    
    void AirThread::excute_barrier_async(AirThread *thread, std::function<void()> _func) {
        
    }
    
    void AirThread::excute_barrier_sync(AirThread *thread, std::function<void()> _func) {
        
    }
}