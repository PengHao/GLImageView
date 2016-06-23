//
//  AirDefined.h
//  AirCpp
//
//  Created by Penghao on 14-1-8.
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

#ifndef AirCpp_AirDefined_h
#define AirCpp_AirDefined_h
#include <sys/time.h>

    
#ifdef DEBUG

#define AirDebugLogConfig(host, port, file)\
{\
AirCpp::AirSingleton<AirCpp::AirLogAll>::getInstance()->init(host, port, file);\
}

#define AirDebugLog(format, ...)\
{\
char tmp[1000];\
sprintf(tmp, __TIME__" %s %05d: " format "\n", __FILE__, __LINE__,##__VA_ARGS__);\
AirCpp::AirSingleton<AirCpp::AirLogAll>::getInstance()->log(tmp);\
}

#define AirDebugLogFinished()\
{\
AirCpp::AirSingleton<AirCpp::AirLogAll>::destroy();\
}

#define DebugLog(format, ...) printf(__TIME__" %s %05d: " format "\n", __FILE__, __LINE__,##__VA_ARGS__)

#define AirAssert(arg) {assert(arg);}


#else

#define AirDebugLog(format,...)
#define AirDebugLogFinished()

#define DebugLog(format,...)
#define AirAssert(arg)
#endif

#endif