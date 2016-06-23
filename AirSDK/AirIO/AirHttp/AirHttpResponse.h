//
//  AirHttpResponse.h
//  AirCpp
//
//  Created by Penghao on 14-3-24.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirHttpResponse__
#define __AirCpp__AirHttpResponse__
#include "AirHttpHeader.h"
#include <string.h>
namespace AirCpp{
    extern const char *TRUNK_END;
    class AirHttpResponse : public AirObject{
    protected:
        AirSize_t content_length;
        AirString *header_string;
        bool had_get_head_finished;
        
        int resived_body(AirString *buffer);
    public:
        AirHttpResponseHead response_header;
        AirString *response_data;
        
    public:
        ~AirHttpResponse(){
            release(header_string);
        }
        
        AirHttpResponse():content_length(0), had_get_head_finished(false){
            
        }

        int resived_data(AirString *data){
            int rs = 0;
            if (!had_get_head_finished) {
                if (header_string == NULL) {
                    header_string = retain(data);
                }else{
                    *header_string+=*data;
                }
                AirMutableArray<AirString> *array = header_string->split_with_string(AirHTTP_CRLF_CRLF);
                if (array->count()>1) {
                    //已经返回了完整的http头
                    had_get_head_finished = true;
                    header_string = retain((*array)[0]);
                    response_header.init(header_string);
                    for (int i = 1; i < array->count(); ++i) {
                        rs = resived_body((*array)[i]);
                    }
                    return rs;
                }
            }else{
                rs = resived_body(data);
            }
            return rs;
        }
    };
    
}


#include <iostream>

#endif /* defined(__AirCpp__AirHttpResponse__) */
