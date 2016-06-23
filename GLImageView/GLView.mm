//
//  GLView.m
//  kxmovie
//
//  Created by Kolyvan on 22.10.12.
//  Copyright (c) 2012 Konstantin Boukreev . All rights reserved.
//
//  https://github.com/kolyvan/kxmovie
//  this file is part of KxMovie
//  KxMovie is licenced under the LGPL v3, see lgpl-3.0.txt

#import "GLView.h"
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "../AirSDK/AirGraphics/AirGraphics.h"
#import "../AirSDK/AirGraphics/AirGraphicsContext/IOSGraphicsContext.h"
#import "../AirSDK/AirGraphics/AirGraphicsRender.h"
#import "../AirSDK/AirGraphics/AirImageRender.hpp"
#import "../AirSDK/AirGraphics/AirGraphicsScene.h"


//////////////////////////////////////////////////////////

#pragma mark - gl view

enum {
	ATTRIBUTE_VERTEX,
   	ATTRIBUTE_TEXCOORD,
};

@implementation GLView {
    AirCpp::IOSGraphicsContext *_context;
    AirCpp::AirGraphics *_graphics;
    AirCpp::AirGraphicsRender *_render;
    AirCpp::AirGraphicsScene *_sence;
}

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

- (void) removeAllImages {
    _render->remove_all();
}

- (void) addImage:(NSString *)imageName frame:(CGRect)imageFrame {
    AirCpp::AirImageRender *pTmpRender = new AirCpp::AirImageRender();
    std::string _vshfilename([NSBundle mainBundle].resourcePath.UTF8String);
    std::string _fshfilename([NSBundle mainBundle].resourcePath.UTF8String);
    _vshfilename+="/AirImageRender.vsh";
    _fshfilename+="/AirImageRender.fsh";
    AGVector agFrame;
    agFrame.v[0] = imageFrame.origin.x;
    agFrame.v[1] = imageFrame.origin.y;
    agFrame.v[2] = imageFrame.size.width;
    agFrame.v[3] = imageFrame.size.height;
    
    NSString *path = imageName;
    pTmpRender->init(_vshfilename.c_str(), _fshfilename.c_str(), agFrame, self.frame.size.width, self.frame.size.height, path.UTF8String);
    _render->add_render(pTmpRender);
    [self layoutSubviews];
}

- (id) initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer*) self.layer;
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
                                        kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
                                        nil];
        
        _context = new AirCpp::IOSGraphicsContext();
        _context->init((__bridge_retained void *)eaglLayer);
        
        _graphics = new AirCpp::AirGraphics();
        _graphics->init(AirCpp::NONE, _context);
        
        AirCpp::AirGraphicsRender *pTmpRender = new AirCpp::AirGraphicsRender();
        _render = pTmpRender;
        std::string _vshfilename([NSBundle mainBundle].resourcePath.UTF8String);
        std::string _fshfilename([NSBundle mainBundle].resourcePath.UTF8String);
        _vshfilename+="/AirImageRender.vsh";
        _fshfilename+="/AirImageRender.fsh";
        pTmpRender->init(_vshfilename, _fshfilename);
        _sence = new AirCpp::AirGraphicsScene();
        _sence->init(_graphics, _render);
        
    }
    
    return self;
}

- (void)dealloc
{
    delete _context;
    _context = nil;
}

- (void)layoutSubviews
{
    _sence->rend(false);
}

@end
