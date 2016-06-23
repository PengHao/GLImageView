//
//  AirHttpHeader.cpp
//  AirCpp
//
//  Created by Penghao on 14-3-24.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#include "AirHttpHeader.h"
namespace AirCpp {
    
    const char * AirHTTP_CRLF = "\r\n";
    const char * AirHTTP_CRLF_CRLF = "\r\n\r\n";
    
    
    const AirString *AirHttpHead::get_head_feild(const AirString *feild){
        const AirString *value = NULL;
        for (it=head_feild_map.begin(); it!=head_feild_map.end(); ++it){
            if (*feild == *it->first) {
                value = it->second;
            }
        }
        return value;
    }
    
    inline int AirHttpHead::set_head_feild(AirString * const key,AirString * const value){
        std::pair<AirString *, AirString *> key_value;
        key_value.first = retain(key);
        key_value.second = retain(value);
        head_feild_map.insert(key_value);
        return 0;
    }
    
    int AirHttpConnectHead::init(const AirString *method, const AirString *file, const AirString *version , const AirString *host){

        AirString space(" ");
        first_line += *method;
        first_line += space;
        first_line += *file;
        first_line += space;
        first_line += *version;
        first_line += AirHTTP_CRLF;
        first_line += "Host:";
        first_line += *host;
        first_line += AirHTTP_CRLF;
        head_length = first_line.length;
        
        return 0;
    }
    
    const AirString *AirHttpConnectHead::get_head(){
        
        AirString *str = new AirString();
        AirString mark(" : ");
        *str = first_line;
        for (it=head_feild_map.begin(); it!=head_feild_map.end(); ++it){
            
            *str += *it->first;
            *str += mark;
            *str += *it->second;
            *str += AirHTTP_CRLF;
        }
        *str += AirHTTP_CRLF;
        return str;
    }
    
    int AirHttpConnectHead::set_head_feild(AirString *const key, AirString *const value){
        AirHttpHead::set_head_feild(key, value);
        head_length += key->length;
        head_length += key->length;
        return 0;
    }
    
    
    inline int AirHttpResponseHead::analsys(AirString *online){
        AirString paramsstr(": ");
        AirMutableArray<AirString> *array = online->split_with_string(paramsstr);
        if (array->count()==1) {
            //第一行
            AirString paramsstr(" ");
            
            
            AirMutableArray<AirString> *paramsarray = (*array)[0]->split_with_characters(paramsstr);
            if (paramsarray->count() >= 3) {
                http_version = retain((*paramsarray)[0]);
                http_status = (*paramsarray)[1]->Int16Value();
                http_msg = retain((*paramsarray)[2]);
            }
            release(paramsarray);
            
        }else{
            set_head_feild((*array)[0], (*array)[1]);
        }
        return 0;
    }
    
    int AirHttpResponseHead::init(AirString * const str){

        AirString crf(AirHTTP_CRLF);
        AirMutableArray<AirString> *array = str->split_with_string(crf);
        for (int i = 0; i < array->count(); ++i) {
            analsys((*array)[i]);
        }
        return 0;
    }
    
}
