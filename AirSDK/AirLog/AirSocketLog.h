//
//  AirSocketLog.h
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
#ifndef AirCpp_AirSocketLog_h
#define AirCpp_AirSocketLog_h

#include "../AirIO/AirSocketConnect.h"
namespace AirCpp {
    
struct EnableSocketLog;
typedef AirBSDSocketIO<EnableSocketLog> LogSocket;
    
typedef AirSocketConnect<EnableSocketLog> LogSocketConnect;
class EnableSocketLog {
private:
    LogSocket *socket;
    LogSocketConnect *conn;
public:
    virtual void received_package(LogSocketConnect *conn, AirDataStreamBuffer *package){
//        if (package->method()==200) {
//            AirString str;
//            package->read_string(&str);
//            printf("%s\n",str.c_str);
//        }
    }
    
    virtual void received_buffer_finished(LogSocketConnect *conn){
        
    }
    
    virtual void connected(LogSocketConnect *conn, bool *value){
        
    }
    virtual void recevie_time_out(LogSocketConnect *conn){
        
    }
    
    void receivedBuffer(int *p_socketHandle, AirData *data_copy){
    }
public:
    EnableSocketLog(){
        socket = NULL;
    }
    
    int init(AirString *host, unsigned int port){
        conn = new LogSocketConnect();
        if (conn->init(host, port, this)<0) {
            delete conn;
            conn = NULL;
            return -1;
        }else{
            return 0;
        }
        
        socket = new LogSocket(this);
        socket->init(AF_INET, SOCK_STREAM, 0);
        if (socket->connect_to_host(host, port, this)<0) {
            DebugLog("connect_failed!");
            delete socket;
            socket = NULL;
            return -1;
        }else{
            return 1;
        }
    }
    
    AirSize_t log(AirString *s){
        if (NULL == &socket) {
            return 0;
        }else{
//            AirData data;
//            data.init(s->c_str, s->length+1);
//            conn->send_data(s->data());
            return 0;
        }
        return 0;
    };
    
    void log(AirDataStreamBuffer *package){
        conn->send_data(package);
    }
    
    
};
    
struct DisEnableSocketLog {
    unsigned long log(char *s){
        return 0;
    };
};

}
#endif
