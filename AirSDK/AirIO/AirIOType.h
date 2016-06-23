//
//  AirIOType.h
//  AirCpp
//
//  Created by hao peng on 13-9-2.
//  Copyright (c) 2013年 hao peng.

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
#ifndef AirCpp_AirIOType_h
#define AirCpp_AirIOType_h
#include <string.h>
namespace AirCpp {
    /**
    class AirBuffer: public AirObject{
    public:
        size_t size;
        void *data;
        AirBuffer(size_t _size){
            data = calloc((size_t)_size, sizeof(char));
            if (NULL != data) {
                size = _size;
            }else{
                size = 0;
            }
        }
        
        AirBuffer(const void *_data, size_t _size){
            data = calloc(_size, sizeof(char));
            if (NULL != data) {
                size = _size;
                memcpy(data, _data, (size_t)_size);
            }else{
                size = 0;
            }
        }
        
        ~AirBuffer(){
            if (NULL != data) {
                free(data);
            }
            size = 0;
        }
    };
     
     **/
}
#endif
