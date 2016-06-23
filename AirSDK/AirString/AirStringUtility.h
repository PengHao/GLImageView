//
//  AirStringUtility.h
//  AirCpp
//
//  Created by hao peng on 13-8-31.
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
//

#ifndef AirCpp_AirStringUtility_h
#define AirCpp_AirStringUtility_h
#include <string.h>
#include <stdlib.h>

extern char *air_str_copy(const char *str);

extern char *air_str_ncpy(const char *str, size_t length);

extern unsigned long strcpymalloc(char **str ,const char *rs_str);

extern unsigned long strncpymalloc(char **str, const char *rs_str, unsigned long length);

#endif
