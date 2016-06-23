//
//  AirString.h
//  AirCpp
//
//  Created by Penghao on 14-1-9.
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
//

#ifndef __AirCpp__AirString__
#define __AirCpp__AirString__

#include <iostream>
#include "../AirObject/AirObject.h"
#include "../AirContainer/AirArray.h"
#include "../AirContainer/AirData.h"
#include "AirStringUtility.h"
namespace AirCpp {
    class AirString : public AirObject{
    private:
    public:
        char *c_str;
        AirSize_t length;
        ~AirString(){
            if (c_str != NULL) {
                free(c_str);
            }
        }
        AirString():c_str(NULL), length(0){ }
        
        AirString(const char *str):c_str(str == NULL? NULL:air_str_copy(str)), length((AirSize_t)strlen(str)){
        }
        
        AirString(const char *str, AirSize_t len):c_str(str == NULL? NULL:air_str_ncpy(str, len)), length(len){
        }
        
        AirString(AirData *data):c_str(data == NULL? NULL:air_str_ncpy(data->c_data, data->length)), length(data == NULL? 0:data->length){
            
        }
        
        operator AirData (){
            AirData data;
            data.c_data = c_str;
            data.length = length+1;
            return data;
        }
        
        AirString & operator=(const AirString &t1){
            c_str = air_str_copy(t1.c_str);
            length = t1.length;
            return *this;
        }
        AirString & operator=(const char *t1){
            length = (AirSize_t)strlen(t1);
            c_str = air_str_copy(t1);
            return *this;
        }
        
        AirString operator+(const AirString &t1) const{
            char *str = (char *)calloc(length+t1.length, sizeof(char));
            strcat(str, c_str);
            strcat(str, t1.c_str);
            return AirString(str);
        }
        
        int init (AirSize_t length_){
            c_str = (char *) calloc(length_+1, sizeof(char));
            length = length_;
            return c_str != NULL?1:0;
        }
        
        void desc() const{
            printf("length = %u\n%s\n", length, c_str);
        }
        
        void operator+=(const AirString &t1){
            length += t1.length;
            char *str = (char *)calloc(length+1, sizeof(char));
            AirAssert(str != NULL);
            if (c_str != NULL) {
                strcpy(str, c_str);
                free(c_str);
            }
            strcat(str, t1.c_str);
            c_str = str;
        }
        
        bool operator==(const char *t1){
            if (c_str != NULL && t1 != NULL) {
                return (strcmp (c_str,t1) == 0);
            }else{
                return c_str == t1;
            }
        }
        
        bool operator==(const AirString &t1) const{
            if (c_str != NULL && t1.c_str != NULL) {
                return (strcmp (c_str,t1.c_str) == 0);
            }else{
                return c_str == t1.c_str;
            }
        }
        
        AirData *data() const{
            AirData *tp = new AirData();
            tp->init(c_str, length+1);
            return tp;
        }
        
        AirMutableArray<AirString> *split_with_string(const AirString &split_str) const{
            char *tmp = c_str;
            AirMutableArray<AirString> * result_array = new AirMutableArray<AirString>();;
            char * pch = NULL;
            
            while ((pch = strstr(tmp, split_str.c_str)) != NULL) {
                AirSize_t len = (AirSize_t)(pch - tmp);
                AirString *air_str = new AirString(tmp, len);
                result_array->add_object(air_str);
                release(air_str);
                tmp += len;
                tmp += split_str.length;
            };
            
            AirString *air_str = new AirString(tmp);
            result_array->add_object(air_str);
            release(air_str);
            return result_array;
        }
        
        AirMutableArray<AirString> *split_with_characters(const AirString &characters){
            char *tmp = c_str;
            AirMutableArray<AirString> * result_array = NULL;
            char * pch = NULL;
            pch = strtok (tmp, characters.c_str);
            while (pch != NULL)
            {
                AirString *air_str = new AirString(pch);
                
                if (result_array == NULL) {
                    result_array =  new AirMutableArray<AirString>();
                }
                result_array->add_object(air_str);
                release(air_str);
                pch = strtok (NULL, characters.c_str);
            }
            return result_array;
        }
        
        AirString *trim_left_with_string(const AirString *string) const{
            char * pch = strstr(c_str, string->c_str);
            if (pch != c_str) {
                return NULL;
            }else{
                AirString *air_str = new AirString(c_str + string->length);
                return air_str;
            }
        }
        
        AirString *trim_left_with_caracters(const AirString *characters){
            AirSize_t i = 0;
            while (i < length && strchr(characters->c_str, *(c_str+i))!= NULL) {
                ++i;
            }
            AirSize_t left = length - i;
            if (left == 0) {
                //all is '\0'
                return NULL;
            }else{
                AirString *air_str = new AirString(c_str + i);
                return air_str;
            }
        }
        
        AirString *trim_right_with_caracters(const AirString *characters){
            AirSize_t i = 0;
            while (i < length  && strchr(characters->c_str, *(c_str + length - i))!= NULL) {
                ++i;
            }
            
            AirSize_t left = length - i;
            if (left == 0) {
                //all is '\0'
                return NULL;
            }else{
                AirString *air_str = new AirString(c_str, left);
                return air_str;
            }
        }
        
        AirString *trim_with_caracters(AirString *result_str, const AirString *characters){
            // left
            AirSize_t i = 0;
            while (i < length && strchr(characters->c_str, *(c_str+i))!= NULL) {
                ++i;
            }
            if (i == length) {
                // all is
                return NULL;
            }else{
                AirSize_t left = i;
                i = 0;
                while (i < length  && strchr(characters->c_str, *(c_str + length - i))!= NULL) {
                    ++i;
                }
                
                AirString *air_str = new AirString(c_str + left, length - left - i);
                return air_str;
            }
        }
        
        AirInt16 Int16Value() const{
            return atoi(c_str);
        };
        
    };
}
#endif /* defined(__AirCpp__AirString__) */
