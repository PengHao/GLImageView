//
//  AirThread.h
//  AirCpp
//
//  Created by Penghao on 14-1-17.
//  Copyright (c) 2014年 PengHao.

//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef __AirCpp__AirThread__
#define __AirCpp__AirThread__

#define OSLinux


#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <pthread/pthread.h>
#include <unistd.h>
#include <signal.h>
#include "../AirObject/AirObject.h"
#include "../AirContainer/AirArray.h"
#include "AirOperation.h"
#include <AirThread/AirQueue.hpp>

namespace AirCpp {

#define CANCEL      0x001  //取消
#define HOLDON      0x002  //挂起
#define RECOVER     0x003  //恢复
#define PUASE       0x004  //暂停
#define RESUME      0x005  //继续
#define EXIT        0x006  //退出

    
    class AirThread : public AirObject{
    protected:
        pthread_t p_id;
        pthread_cond_t p_cond;
        pthread_mutex_t p_mutex;
        
        AirQueue *operation_queue;

        static void *_run_loop(void *thread);
        bool _cancel;
        bool _sleep;
        void run_roop();
    public:
        
        typedef enum {
            Main = 0,
            Concurrence = 1,
        } ConcurrenceType;
        
        static AirThread * current_thread();
        
        static void excute_async(AirThread *thread, std::function<void()> _func);
        static void excute_sync(AirThread *thread, std::function<void()> _func);
        static void excute_apply(int concurrence_count, std::function<void(int)> _func);
        static void excute_after(AirThread *thread, std::function<void()> _func, float after_delay);
        static void excute_barrier_async(AirThread *thread, std::function<void()> _func);
        static void excute_barrier_sync(AirThread *thread, std::function<void()> _func);
        
    public:
        
        AirThread() : _cancel(false){ operation_queue = new AirQueue();};
        
        ~AirThread() ;
        
        void push_operation(AirOperation *operation);
        
        /**
         *	初始化线程
         *
         *	@return	初始化失败返回-1 成功返回0
         */
        int init();
        
        /**
         *	取消运行
         *
         */
        void cancel();
        
        /**
         *	等待线程运行结束
         *
         *	@param 	*ret 	运行结果
         */
        void wait_until_done(void **ret);
        
        void keep_going();
    };
    
}

#endif /* defined(__AirCpp__AirThread__) */
