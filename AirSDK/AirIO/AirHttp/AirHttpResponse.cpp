//
//  AirHttpResponse.cpp
//  AirCpp
//
//  Created by Penghao on 14-3-24.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#include "AirHttpResponse.h"

namespace AirCpp {
    const char *TRUNK_END = "0\r\n\r\n";
    int AirHttpResponse::resived_body(AirString *data){
        content_length+=data->length;
        if (!response_data) {
            response_data = retain(data);
        }else{
            *response_data+=*data;
        }
        
        AirString transfor((char *)"Transfer-Encoding");
        AirString Content((char *)"Content-Length");
        
        const AirString *transfer_encoding = response_header.get_head_feild(&transfor);
        const AirString *content_length_str = response_header.get_head_feild(&Content);

        if (transfer_encoding && (*transfer_encoding)=="chunked") {                                 // chunked
            if ( strnstr((const char *)data->c_str, TRUNK_END, data->length)!=NULL) {
                //end
                return 1;
            }
        }else if (content_length_str){                                                              // content-length
            if (content_length_str->Int16Value() <= content_length) {
                //end
                return 1;
            }
        }
        return  0;
    }
    
}