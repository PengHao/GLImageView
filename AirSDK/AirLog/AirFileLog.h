//
//  AirFileLog.h
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
#ifndef AirCpp_AirFileLog_h
#define AirCpp_AirFileLog_h
#include "../AirIO/AirFileIO.h"
namespace AirCpp {
    
class EnableFileLog;
    
class EnableFileLog : public AirFileIO {
private:
    AirFileIO *p_IO;
public:
    EnableFileLog(){
    }
    
    int init(char *file_name){
        p_IO = new AirFileIO();
        if(p_IO->init(file_name, OPENTYPE_EMPTYAPPENDWRITE))
            return 0;
        else{
            delete p_IO;
            p_IO = NULL;
            return -1;
        }
    }
    
    long log(char *s){
        if (p_IO!=NULL) {
            AirData *data = new AirData();
            data->init(s, (AirUInt32)strlen(s));
            p_IO->write_data(data);
            release(data);
            return 0;
        }else{
            return -1;
        }
    };
};
class DisableFileLog {
public:
    DisableFileLog(){
    }
    int init(char *file_name){
        return 0;
    }
    unsigned long log(char *s){
        return 0;
    };
};

}
#endif
