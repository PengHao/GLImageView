//
//  AirLog.h
//  AirCpp
//
//  Created by Penghao on 14-1-7.
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
#ifndef __AirCpp__AirLog__
#define __AirCpp__AirLog__



#include <iostream>
#include "../AirObject/AirObject.h"
#include "AirSocketLog.h"
#include "AirFileLog.h"
#include "AirLocalLog.h"
namespace AirCpp {
    

template <class SocketLog, class FileLog, class LocalLog>
class AirLog : public AirObject{
private:
    SocketLog *p_s_log;
    FileLog *p_f_log;
    LocalLog *p_l_log;
public:
    AirLog(){
        p_s_log = NULL;
        p_f_log = NULL;
        p_l_log = NULL;
    }
    virtual ~AirLog(void){
        delete p_s_log;
        delete p_f_log;
        delete p_l_log;
    }
    int init(char *socket_host, unsigned int socket_port, char *file_name){
        p_s_log = new SocketLog();
        p_f_log = new FileLog();
        p_l_log = new LocalLog();
        if(p_s_log->init(socket_host, socket_port)<0){
            DebugLog("init socket failed!");
            delete p_s_log;
            p_s_log = NULL;
            return -1;
        };
        
        if (p_f_log->init(file_name)<0) {
            DebugLog("init file handle failed!");
            delete p_f_log;
            p_f_log = NULL;
            return -1;
        }
        return 0;
    }
    unsigned long log(char *s);
};

template <class SocketLog, class FileLog, class LocalLog>
unsigned long AirLog<SocketLog, FileLog, LocalLog>::log(char *s_log) {
    p_l_log->log(s_log);
    p_f_log->log(s_log);
    p_s_log->log(s_log);
    return 0;
};


typedef AirLog<EnableSocketLog, DisableFileLog, EnableLocalLog> AirLogAll;
}
#endif /* defined(__AirCpp__AirLog__) */
