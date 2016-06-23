//
//  AirStringUtility.c
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
//

#include <stdio.h>
#include <cassert>
#include "AirStringUtility.h"
char *air_str_copy(const char *str){
    char *tmp = (char *)calloc(strlen(str)+1, sizeof(char));
    if (tmp!=NULL) {
        strcpy(tmp, str);
    }
    return tmp;
}

char *air_str_ncpy(const char *str, size_t length){
    char *tmp = (char *)calloc(length+1, sizeof(char));
    if (tmp!=NULL) {
        strncpy(tmp, str, length);
    }
    return tmp;
};


unsigned long strcpymalloc(char **str ,const char *rs_str){
    unsigned long length = strlen(rs_str);
    char *copied_str = (char *)calloc(length, sizeof(char));
    strcpy(copied_str, rs_str);
    *str = copied_str;
    return length;
}

unsigned long strncpymalloc(char **str, const char *rs_str, unsigned long length){
    assert(strlen(rs_str)>= length);
    
    *str = (char *)calloc(length, sizeof(char));
    strncpy(*str, rs_str, length);
    
    return length;
}