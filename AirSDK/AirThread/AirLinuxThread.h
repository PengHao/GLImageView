//
//  AirLinuxThread.h
//  AirCpp
//
//  Created by Penghao on 14-1-24.
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

#ifndef __AirCpp__AirLinuxThread__
#define __AirCpp__AirLinuxThread__

#include <iostream>
/* example.c*/
#include <stdio.h>
#include <pthread.h>
#include <pthread/pthread.h>
#include <unistd.h>
#include <signal.h>
#include "../AirObject/AirObject.h"
#include "../AirContainer/AirArray.h"
#include "AirOperation.h"

namespace AirCpp {
#define FINISHED 0x001
    
    void sighand(int signo){
        switch (signo) {
            case FINISHED:
                pthread_exit(0);
                break;
                
            default:
                break;
        }
    }
    
    /**
     *	Linux的p_thread多线程实现
     */
    class AirThread : public AirObject{
    protected:
        pthread_t p_id;
    public:
        
        AirThread() {
            struct sigaction        actions;
            memset(&actions, 0, sizeof(actions));
            sigemptyset(&actions.sa_mask); /* 将参数set信号集初始化并清空 */
            actions.sa_flags = 0;
            actions.sa_handler = sighand;
            sigaction(FINISHED, &actions, nullptr);
        }
        
        ~AirThread() {
            pthread_kill(p_id, FINISHED);
        }
        
        /**
         *	初始化线程
         *
         *	@return	初始化失败返回-1 成功返回0
         */
        int init(){
            return 0;
        }
        
        /**
         *	调用操作
         *
         *	@param 	O 	操作对象
         */
        static void *invocate(void *O){
            AirOperation *oper = (AirOperation *)O;
            oper->excute();
            return nullptr;
        }
        
        /**
         *	多线程运行操作
         *
         *	@param 	oper 	操作对象
         */
        int run_operation(AirOperation *oper){
            return pthread_create(&p_id, NULL, invocate, (void *)oper);
        }
        
        /**
         *	取消运行
         *
         */
        void cancel(){
            pthread_cancel(p_id);
        }
        
        /**
         *	等待线程运行结束
         *
         *	@param 	*ret 	运行结果
         */
        void wait_until_done(void **ret){
            pthread_join(p_id, ret);
        }
        
        void keep_going(){
            pthread_detach(p_id);
        }
    };
    
}
#endif /* defined(__AirCpp__AirLinuxThread__) */
