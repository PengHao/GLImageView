//
//  AirHttpHeader.h
//  AirCpp
//
//  Created by Penghao on 14-3-24.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirHttpHeader__
#define __AirCpp__AirHttpHeader__

#include <iostream>
#include <string.h>
#include "../../AirObject/AirObject.h"
#include "../../AirString/AirStringUtility.h"
#include "../../AirString/AirString.h"
#include "../../AirContainer/AirArray.h"
#include "../../AirIO/AirIOType.h"
#include "../../AirContainer/AirDataStreamBuffer.h"
#include <map>
namespace AirCpp{
    
    extern const char * AirHTTP_CRLF;
    extern const char * AirHTTP_CRLF_CRLF;
    
    class AirHttpHead : public AirObject{
    protected:
        std::map<AirString *, AirString *>head_feild_map;
        std::map<AirString *, AirString *>::iterator it;
    public:
        AirString *http_version;
    public:
        
        void decs(){
            printf("http_version : %s \n", http_version->c_str);
            for (it=head_feild_map.begin(); it!=head_feild_map.end(); ++it){
                printf("%s : %s\n", it->first->c_str, it->second->c_str);
            }
        }
        
        const AirString *get_head_feild(const AirString *feild);
        
        int set_head_feild(AirString *const key, AirString *const value);
        
        virtual ~AirHttpHead(){
            for (it=head_feild_map.begin(); it!=head_feild_map.end(); ++it){
                release(it->first);
                release(it->second);
            }
            release(http_version);
        }
    };
    
    class AirHttpConnectHead: public AirHttpHead{
    protected:
        AirString first_line;
    public:
        unsigned long head_length;
        AirHttpConnectHead():head_length(2){
        }
        
        ~AirHttpConnectHead(){
            
        }
        
        int init(const AirString *method, const AirString *file, const AirString *version, const AirString *host);
        
        const AirString *get_head();
        
        int set_head_feild(AirString *const key, AirString *const value);
    };
    
    
    class AirHttpResponseHead : public AirHttpHead{
    protected:
        int http_status;
        AirString *http_msg;
    public:
        
        int analsys(AirString *str);
        
        int init(AirString * const head_buffers);
        
    public:
        
        ~AirHttpResponseHead(){
            release(http_msg);
        }
        
        AirHttpResponseHead():http_msg(NULL), http_status(0){
            
        }
    };
}
#endif /* defined(__AirCpp__AirHttpHeader__) */
