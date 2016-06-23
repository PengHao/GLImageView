//
//  IOSGraphicsContext.h
//  AirCpp
//
//  Created by Penghao on 14-3-6.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__IOSGraphicsContext__
#define __AirCpp__IOSGraphicsContext__

#include <iostream>
#include "AirGraphicsContext.h"

namespace AirCpp {
    class IOSGraphicsContext : public AirGraphicsContext{
    private:
        void *eaglLayer;
        void *context;
    public:
        IOSGraphicsContext():
        eaglLayer(nullptr),
        context(nullptr),
        AirGraphicsContext() {}
        
        ~IOSGraphicsContext() { }
        
        virtual int init(void *_eaglLayer);
        
        int active();
        
        int bind_to_drawable_storage();
        
        void display_content();
    };
}
#endif /* defined(__AirCpp__IOSGraphicsContext__) */
