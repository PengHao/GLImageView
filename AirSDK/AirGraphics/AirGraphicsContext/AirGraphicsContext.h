//
//  AirGraphicsContext.h
//  AirCpp
//
//  Created by Penghao on 14-3-6.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirGraphicsContext__
#define __AirCpp__AirGraphicsContext__

#include <iostream>
#include "../../AirOSInclude/AirOSInclude.h"


namespace AirCpp {
    class AirGraphicsContext {
    public:
        AirGraphicsContext() { }
        virtual ~AirGraphicsContext() { }
        virtual int init(void *_drawable) = 0;
        virtual int active() = 0;
        virtual void display_content() = 0;
        virtual int bind_to_drawable_storage() = 0;
    };
}

#endif /* defined(__AirCpp__AirGraphicsContext__) */
