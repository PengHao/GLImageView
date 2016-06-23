//
//  AirHttpIO.h
//  AirCpp
//
//  Created by  on 12-9-10.
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

#ifndef AirCpp_AirHttpIO_h
#define AirCpp_AirHttpIO_h

#include "../AirIO.h"
#include "../../AirString/AirStringUtility.h"
#include "../../AirObject/AirObject.h"
#include "../../AirContainer/AirDictionary.h"
#include "../../AirContainer/AirData.h"
#include "../AirSocket.h"
#include "AirHttpHeader.h"
#include "AirHttpResponse.h"
#include "../../AirOSInclude/AirOSInclude.h"
#include <string.h>
#include <stdlib.h>
#include <map>
namespace AirCpp{
    
    static const char AirHttpVersion1_0[] = "HTTP/1.0";
    static const char AirHttpVersion1_1[] = "HTTP/1.1";
    
    enum HTTPMethod {
        HTTPMethodGET = 0,
        HTTPMethodPOST = 1
    };
    
    template <class CallBackClass>
    class AirHttpConnect: public AirObject {
#ifdef OSLinux
        typedef AirBSDSocketIO<AirHttpConnect> AirOSSocketIO;
#elif defined OSWindows
#endif
    private:
        bool is_active;
        AirString *http_hostname;
        CallBackClass *callback_class;
        AirOSSocketIO *netIO;
        bool had_get_head_finished;
        const void *context;
        
        AirHttpConnectHead *http_head;
        AirData *http_body;
        
        AirString reseived_data;
        
        void *start_reseive(void *){
            return NULL;
        }
        
    public:
        AirHttpResponse *http_response;
        
        AirHttpConnect():netIO(NULL), callback_class(NULL), had_get_head_finished(false), http_body(NULL), http_head(NULL){
        }
        
        ~AirHttpConnect(){
            release(http_hostname);
            release(http_head);
            release(http_body);
            release(http_response);
            
            release(netIO);
        }
        
        int init(const AirString *_url, const AirString *http_method, const AirString *http_version, const void *_content){
            context = _content;
            AirString http_start("http://");
            AirString *tmpurl = _url->trim_left_with_string(&http_start);
            
            AirString http_file_fliter("/");
            AirMutableArray<AirString> *url_array = tmpurl->split_with_string(http_file_fliter);
            if (url_array&&url_array->count()>0) {
                http_hostname = retain((*url_array)[0]);
            }
            
            AirString *http_file = tmpurl->trim_left_with_string(http_hostname);
            
            
            http_head = new AirHttpConnectHead();
            http_head->init(http_method, http_file, http_version, http_hostname);
            
            release(tmpurl);
            release(url_array);
            release(http_file);
            return 0;
        }
        
        
        int init(int *_socket_handle, CallBackClass *callback_){
            netIO = new AirOSSocketIO(this);
            netIO->link_to_handle(*_socket_handle, this);
            if (*_socket_handle<0) {
                delete netIO;
                netIO = NULL;
                return -1;
            }else{
                callback_class = callback_;
            }
            return 0;
        }
        
        
        void active(){
            is_active = true;
            start_reseive(NULL);
        }
        
        void set_callback(CallBackClass *_callback){
            callback_class = _callback;
        }
        
        void set_head_feild( AirString * const key, AirString * const value){
            http_head->set_head_feild(key, value);
        }
        
        void set_body(AirData *body){
            http_body = retain(body);
            char len[10];
            sprintf(len, "%u", body->length);
            AirString *length_key = new AirString("Content-Length");
            AirString *length_val = new AirString(len);
            set_head_feild(length_key, length_val);
        }
        
        void connect(){
            netIO = new AirOSSocketIO(this);
            netIO->init(AF_INET, SOCK_STREAM, 0, 0);
            netIO->connect_to_host(http_hostname, 80, this);
            const AirString *head_str = http_head->get_head();
            AirSize_t totallength = NULL != http_body?http_body->length:0;
            totallength+= head_str->length;
            totallength+=http_body->length;
            totallength+=3;
            
            AirDataStreamBuffer *buffer = AirDataStreamBuffer::creat_instream_http_buffer(totallength);
            buffer->append_c_data(head_str->c_str, head_str->length);
            buffer->append_c_data(http_body->c_data, http_body->length);
            buffer->append_c_data((AirBit8 *)AirHTTP_CRLF, (AirSize_t)strlen(AirHTTP_CRLF));
            
            printf("connect:%s", buffer->get_c_data());
            
            netIO->write_data(buffer->get_c_data(), totallength);
            netIO->reseive();
        }
        
        
        //call back
        
        void connected(AirSocket<AirHttpConnect> *socket, bool *b_successed){
            
        }
        
        void received_buffer(AirSocket<AirHttpConnect> *socket, AirString *data_copy){
            if (http_response == NULL) {
                http_response = new AirHttpResponse();
            }
            
            if (http_response->resived_data(data_copy) == 1) {
                //end
                received_buffer_finished(socket);
            };
        };
        
        void received_buffer_finished(AirSocket<AirHttpConnect> *socket){
            socket->close_connect();
            if (NULL != callback_class) {
                callback_class->recevied_finished(this, context);
                callback_class = NULL;
            }
        }
        
        void sentdata(AirSocket<AirHttpConnect> *socket, bool *b_successed){
            if (NULL != callback_class) {
            }
        }
        
        void recevie_time_out(AirSocket<AirHttpConnect> *socket){
            
        };
    };
    
}
#endif
