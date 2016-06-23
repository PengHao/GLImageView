//
//  AirOperation.h
//  AirCpp
//
//  Created by Penghao on 14-2-25.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirOperation__
#define __AirCpp__AirOperation__

#include <iostream>
#include "../AirObject/AirObject.h"

namespace AirCpp{
    /**
     *	多线程的操作，将对象和相应需要进行调用的方法封装到其中
     */
    class AirOperation : public AirObject {
    friend class AirQueue;
    protected:
        int concurrence_index;
        int func_type;
        struct {
            std::function<void()> serial_func;
            std::function<void(int)> concurrence_func;
        };
    public:
        AirOperation() :
        concurrence_index(0),
        func_type(0) {
            serial_func = nullptr;
            concurrence_func = nullptr;
        }
        
        int init(std::function<void()> _func)
        {
            serial_func = _func;
            return 0;
        }
        int init(std::function<void(int)> _func)
        {
            concurrence_func = _func;
            return 0;
        }
        
        void excute() {
            if (concurrence_func) {
                concurrence_func(concurrence_index);
            } else {
                serial_func();
            }
        }
        
        ~ AirOperation() {
            serial_func = nullptr;
            concurrence_func = nullptr;
        }
    };
}

#endif /* defined(__AirCpp__AirOperation__) */