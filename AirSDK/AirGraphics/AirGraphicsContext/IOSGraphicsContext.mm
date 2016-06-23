//
//  IOSGraphicsContext.cpp
//  kxmovie
//
//  Created by penghao on 16/1/29.
//
//

#include "IOSGraphicsContext.h"

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

namespace AirCpp {
    
    int IOSGraphicsContext::init(void *_eaglLayer){
        eaglLayer = _eaglLayer;
        CAEAGLLayer *tmp_eaglLayer = (__bridge CAEAGLLayer *)_eaglLayer;
        tmp_eaglLayer.opaque = YES;
        tmp_eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        EAGLContext *tmp_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if (tmp_context) {
            context = (__bridge_retained void *)tmp_context;
            return 0;
        }else{
            return -1;
        }
    }
    
    int IOSGraphicsContext::active(){
        EAGLContext *tmp_context = (__bridge EAGLContext *)context;
        return [EAGLContext setCurrentContext:tmp_context]?0:-1;
    }
    
    void IOSGraphicsContext::display_content(){
        EAGLContext *tmp_context = (__bridge EAGLContext *)context;
        [tmp_context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    int IOSGraphicsContext::bind_to_drawable_storage(){
        EAGLContext *tmp_context = (__bridge EAGLContext *)context;
        CAEAGLLayer *tmp_eaglLayer = (__bridge CAEAGLLayer *)eaglLayer;
        return [tmp_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:tmp_eaglLayer]?0:-1;
    }
}