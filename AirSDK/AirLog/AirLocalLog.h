//
//  AirLocalLog.h
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
#ifndef AirCpp_AirLocalLog_h
#define AirCpp_AirLocalLog_h

class EnableLocalLog {
public:
    unsigned long log(char *s){
        DebugLog("%s", s);
        return 0;
    };
};
class DisableLocalLog {
public:
    unsigned long log(char *s){
        return 0;
    };
};

#endif
