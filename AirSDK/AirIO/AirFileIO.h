//
//  AirFileIO.h
//  AirCpp
//
//  Created by  on 12-9-7.
//  Copyright (c) 2012年 hao peng.

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


#ifndef AirCpp_AirFileIO_h
#define AirCpp_AirFileIO_h
#include "AirIOInclude.h"
#include "../AirObject/AirObject.h"
#include "../AirContainer/AirData.h"
#include <fstream>
namespace AirCpp {
    
enum OPENTYPE {
    OPENTYPE_READONLY = 0,              // r
    OPENTYPE_EMPTYWRITEONLY = 1,        // w
    OPENTYPE_APPENDWRITE = 3,           // a
    OPENTYPE_READANDWRITE = 4,          // r+
    OPENTYPE_EMPTYREADANDWRITE = 5,     // w+
    OPENTYPE_EMPTYAPPENDWRITE = 6,      // a+
    };

enum CALL_BACK_TYPE_FILE {
    CALL_BACK_TYPE_FILE_READ = 1,
    CALL_BACK_TYPE_FILE_READEND = 2,
    };

class AirFileIO:AirObject{
private:
    char *file_name;
    OPENTYPE open_type;
    FILE *fp;
public:
    AirFileIO(){
        fp = NULL;
        file_name = NULL;
    }
    
    ~AirFileIO(){
        free(file_name);
        fclose(fp);
    }
    
    int init(const char *filename, OPENTYPE _open_type){
        open_type = _open_type;
        switch (open_type) {
            case OPENTYPE_READONLY:
                fp=fopen(filename, "r");
                break;
            case OPENTYPE_EMPTYWRITEONLY:
                fp=fopen(filename, "w");
                break;
            case OPENTYPE_APPENDWRITE:
                fp=fopen(filename, "a");
                break;
            case OPENTYPE_READANDWRITE:
                fp=fopen(filename, "r+");
                break;
            case OPENTYPE_EMPTYREADANDWRITE:
                fp=fopen(filename, "w+");
                break;
            case OPENTYPE_EMPTYAPPENDWRITE:
                fp=fopen(filename, "a+");
                break;
            default:
                break;
        }
        if(fp==NULL)
        {
            printf("openfile failed!");
            return -1;
        }else{
            strcpymalloc(&file_name, filename);
            return 0;
        }
    }
    
    void read_buffer(AirData &data){
        if ((open_type == OPENTYPE_READONLY || open_type == OPENTYPE_READANDWRITE ||open_type == OPENTYPE_EMPTYREADANDWRITE) &&!feof(fp)) {
            fread(data.c_data, sizeof(char), data.length, fp);
        }
    }
    
    char *read_file_copy(char *file_path){
        char *str;
        FILE *fp;
        if((fp=fopen(file_path,"r"))==NULL)
        {
            return NULL;
        }
        //can not bigger than 2TB
        fseek(fp, 0, SEEK_END);
        long filesize = ftell(fp);
        str = (char *)calloc(filesize, sizeof(char));
        fseek(fp, 0, SEEK_SET);
        fread(str, 1, filesize, fp);
        fclose(fp);
        return str;
    }
    
    void write_data(AirData *buffer){
        fwrite(buffer->c_data, buffer->length, sizeof(char), fp);
    }
};


}
#endif
